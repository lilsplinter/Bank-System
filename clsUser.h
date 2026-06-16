#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtility.h"
using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _Username;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;
    clsUser() : clsPerson("", "", "", ""), _Username(""), _Password(""), _Permissions(0) { _Mode = EmptyMode; }
    static clsUser _CreateEmptyUser() {
        return clsUser();
    }
    static void _AddLogInRecordToFile(const string& Line) {
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::app);
        if (MyFile.is_open()) {
            MyFile << Line << endl;
            MyFile.close();
        }
    }
    static vector<string> _LoadUsersDataFromFile(const string& filename = "Users.txt") {
        vector<string> vUserData;
        fstream MyFile(filename, ios::in);
        if (!MyFile.is_open()) {
            cerr << "Error: Could not open file: " << filename << endl;
            return vUserData;
        }
        string line;
        while (getline(MyFile, line)) {
            vUserData.push_back(line);
        }
        MyFile.close();
        return vUserData;
    }
    static vector<string> _SeperateEachLineInfo(const string& line, const string& separator = "#//#") {
        vector<string> user;
        string temp = line;
        size_t pos = temp.find(separator);
        size_t sepLength = separator.length();
        while (pos != string::npos) {
            user.push_back(temp.substr(0, pos));
            temp = temp.substr(pos + sepLength);
            pos = temp.find(separator);
        }
        if (!temp.empty()) {
            user.push_back(temp);
        }
        return user;
    }
    static void _SettingEachUserDataToObject(clsUser& user, const vector<string>& vUserData) {
        user._Mode = UpdateMode;
        user.FirstName = vUserData[0];
        user.LastName = vUserData[1];
        user.Email = vUserData[2];
        user.Phone = vUserData[3];
        user._Username = vUserData[4];
        user._Password = clsUtility::DecryptText(vUserData[5],3);
        user._Permissions = stoi(vUserData[6]);
    }
    static vector<clsUser> _ConvertUserDataToVectorOfObjects(const vector<string>& vLines) {
        vector<clsUser> vUsers;
        for (string line : vLines) {
            vector<string> vUserData = _SeperateEachLineInfo(line);
            if (vUserData.size() == 7) {
                clsUser User = _CreateEmptyUser();
                _SettingEachUserDataToObject(User, vUserData);
                vUsers.push_back(User);
            }
        }
        return vUsers;
    }
    static string _ConvertUserToLine(const clsUser& User) {
        string line;
        line += User.FirstName + "#//#";
        line += User.LastName + "#//#";
        line += User.Email + "#//#";
        line += User.Phone + "#//#";
        line += User._Username + "#//#";
        line += clsUtility::EncryptText(User._Password , 3) + "#//#";
        line += to_string(User._Permissions);
        return line;
    }
    static vector<clsUser> _GetAllUsers() {
        vector<string> vLines = _LoadUsersDataFromFile();
        return _ConvertUserDataToVectorOfObjects(vLines);
    }
    static void _Save(const vector<clsUser>& vAllUsers) {
        fstream MyFile("Users.txt", ios::out);
        if (!MyFile.is_open()) {
            cerr << "Error: Could not open file for writing." << endl;
            return;
        }
        for (const clsUser& user : vAllUsers) {
            if (!user._MarkedForDelete) {
                MyFile << _ConvertUserToLine(user) << endl;
            }
        }
        MyFile.close();
    }
    static void _AddDataLineToFile(const string& line) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::app);
        if (MyFile.is_open()) {
            MyFile << line << endl;
            MyFile.close();
        }
    }
    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _Username + Seperator;
        LoginRecord += _Password + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;
    }
    void _AddNew() {
        _AddDataLineToFile(_ConvertUserToLine(*this));
    }
    void _Update() {
        vector<clsUser> vAllUsers = _GetAllUsers();
        for (clsUser& user : vAllUsers) {
            if (user._Username == _Username) {
                user = *this;
                break;
            }
        }
        _Save(vAllUsers);
    }
public:
    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserExists = 2 };
    enum enPermissions {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pShowLogInRegister = 128
    };
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string Username, string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone),
        _Username(Username), _Password(Password), _Permissions(Permissions), _Mode(Mode) {
    }
    bool IsEmpty() {
        return _Mode == EmptyMode;
    }
    bool MarkedForDeleted() {
        return _MarkedForDelete;
    }
    string GetUsername() const { return _Username; }
    void SetUsername(string Username) { _Username = Username; }
    string GetPassword() const { return _Password; }
    void SetPassword(string Password) { _Password = Password; }
    int GetPermissions() const { return _Permissions; }
    void SetPermissions(int Permissions) { _Permissions = Permissions; }
    static clsUser Find(const string& Username) {
        vector<clsUser> vAllUsers = _GetAllUsers();
        for (const clsUser& user : vAllUsers) {
            if (user._Username == Username)
                return user;
        }
        return _CreateEmptyUser();
    }
    static clsUser Find(const string& Username, const string& Password) {
        vector<clsUser> vAllUsers = _GetAllUsers();
        for (const clsUser& user : vAllUsers) {
            if (user._Username == Username && user._Password == Password)
                return user;
        }
        return _CreateEmptyUser();
    }
    static bool IsUserExist(const string& Username) {
        return !Find(Username).IsEmpty();
    }
    enSaveResults Save() {
        switch (_Mode) {
        case EmptyMode:
            return svFailedEmptyObject;
        case UpdateMode:
            _Update();
            return svSucceeded;
        case AddNewMode:
            if (IsUserExist(_Username))
                return svFailedUserExists;
            else {
                _AddNew();
                _Mode = UpdateMode;
                return svSucceeded;
            }
        default:
            return svFailedEmptyObject;
        }
    }
    bool Delete() {
        vector<clsUser> vAllUsers = _GetAllUsers();
        for (clsUser& user : vAllUsers) {
            if (user._Username == _Username) {
                user._MarkedForDelete = true;
                break;
            }
        }
        _Save(vAllUsers);
        *this = _CreateEmptyUser();
        return true;
    }
    bool CheckAccessPermission(enPermissions Permission) {
        if (this->Permissions == enPermissions::eAll)
            return true;
        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;
    }
    static clsUser GetEmptyUserObject() {
        return _CreateEmptyUser();
    }
    void RegisterLogin() {
        string stDataLine = _PrepareLogInRecord();
        _AddLogInRecordToFile(stDataLine);
    }
    struct stLoginRegisterRecord {
        string DateTime;
        string Username;
        string Password;
        int Permissions;
    };
    static vector<stLoginRegisterRecord> GetLoginRegisterList() {
        vector<stLoginRegisterRecord> vLoginRegisterRecords;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                vector<string> vRecordData = _SeperateEachLineInfo(Line);
                if (vRecordData.size() == 4) {
                    stLoginRegisterRecord Record;
                    Record.DateTime = vRecordData[0];
                    Record.Username = vRecordData[1];
                    Record.Password = vRecordData[2];
                    Record.Permissions = stoi(vRecordData[3]);
                    vLoginRegisterRecords.push_back(Record);
                }
            }
            MyFile.close();
        }
        return vLoginRegisterRecords;
    }
    static clsUser GetAddNewUserObject(const string& Username) {
        return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
    }
    static vector<clsUser> GetUsersList() {
        return _GetAllUsers();
    }
    void Print() {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nUsername    : " << _Username;
        cout << "\nPassword    : " << _Password;
        cout << "\nPermissions : " << _Permissions;
        cout << "\n___________________\n";
    }
    __declspec(property(get = GetUsername, put = SetUsername)) string Username;
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
};