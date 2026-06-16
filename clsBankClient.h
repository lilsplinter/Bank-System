#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsDate.h"
using namespace std;
class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;
	clsBankClient() : clsPerson("", "", "", ""), _AccountNumber(""), _PinCode(""), _AccountBalance(0.0f) { _Mode = EmptyMode; }
	static clsBankClient _CreateEmptyClient() {
		return clsBankClient();
	}
	static vector<string> _LoadClientsDataFromFile(const string& filename = "Clients.txt") {
		vector<string> vClientData;
		fstream MyFile(filename, ios::in);
		if (!MyFile.is_open()) {
			cerr << "Error: Could not open file: " << filename << endl;
			return vClientData;
		}
		string line;
		while (getline(MyFile, line)) {
			vClientData.push_back(line);
		}
		MyFile.close();
		return vClientData;
	}
	static void _SettingEachClientDataToObject(clsBankClient& Client, const vector <string>& vClientData) {
		Client._Mode = UpdateMode;
		Client._AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.AccountBalance = stof(vClientData[2]);
		Client.FirstName = vClientData[3];
		Client.LastName = vClientData[4];
		Client.Email = vClientData[5];
		Client.Phone = vClientData[6];
	}
	static vector <string> _SeperateEachLineInfo(const string& line, const string& separator = "#//#") {
		vector <string> client;
		string temp = line;
		size_t pos = temp.find(separator);
		size_t sepLength = separator.length();
		while (pos != string::npos) {
			client.push_back(temp.substr(0, pos));
			temp = temp.substr(pos + sepLength);
			pos = temp.find(separator);
		}
		if (!temp.empty()) {
			client.push_back(temp);
		}
		return client;
	}
	static vector <clsBankClient> _ConvertClientDataToVectorOfObjects(const vector <string>& vLines) {
		vector <clsBankClient> vClients;
		for (string line : vLines) {
			vector <string> vClientData = _SeperateEachLineInfo(line);
			if (vClientData.size() == 7) {
				clsBankClient Client = _CreateEmptyClient();
				_SettingEachClientDataToObject(Client, vClientData);
				vClients.push_back(Client);
			}
		}
		return vClients;
	}
	static string _ConvertClientToLine(const clsBankClient& Client) {
		string line;
		line += Client.AccountNumber + "#//#";
		line += Client.PinCode + "#//#";
		line += to_string(Client.AccountBalance) + "#//#";
		line += Client.FirstName + "#//#";
		line += Client.LastName + "#//#";
		line += Client.Email + "#//#";
		line += Client.Phone;
		return line;
	}
	static vector <clsBankClient> _GetAllClients() {
		vector <string> vLines = _LoadClientsDataFromFile();
		return _ConvertClientDataToVectorOfObjects(vLines);
	}
	static void _Save(const vector<clsBankClient>& vAllClients) {
		fstream MyFile("Clients.txt", ios::out);
		if (!MyFile.is_open()) {
			cerr << "Error: Could not open file for writing." << endl;
			return;
		}
		for (const clsBankClient& client : vAllClients) {
			if (!client._MarkedForDelete) {
				MyFile << _ConvertClientToLine(client) << endl;
			}
		}
		MyFile.close();
	}
	static void _AddDataLineToFile(const string& line) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}
		MyFile.close();
	}
	void _AddNew() {
		_AddDataLineToFile(_ConvertClientToLine(*this));
	}
	void _Update() {
		vector<clsBankClient> _vAllClients = _GetAllClients();
		for (clsBankClient& client : _vAllClients) {
			if (client.AccountNumber == _AccountNumber) {
				client = *this;
				break;
			}
		}
		_Save(_vAllClients);
	}
	string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#") {
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += _AccountNumber + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(_AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}
	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName) {
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << _PrepareTransferLogRecord(Amount, DestinationClient, UserName) << endl;
			MyFile.close();
		}
	}
public:
	struct stTransferLogRecord {
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double TransferAmount;
		double SourceAccountBalanceAfterTransfer;
		double DestinationAccountBalanceAfterTransfer;
		string UserName;
	};
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone),
		_AccountNumber(AccountNumber),
		_PinCode(PinCode),
		_AccountBalance(AccountBalance),
		_Mode(Mode)
	{
	}
	bool IsEmpty() {
		return _Mode == EmptyMode;
	}
	static bool IsClientExist(const clsBankClient& client) {
		return !Find(client.AccountNumber).IsEmpty();
	}
	static bool IsClientExist(const string& AccountNumber) {
		return !Find(AccountNumber).IsEmpty();
	}
	bool IsClientExist() const {
		return IsClientExist(*this);
	}
	static clsBankClient Find(const string& AccountNumber) {
		vector<clsBankClient> _vAllClients = _GetAllClients();
		for (const clsBankClient& Client : _vAllClients) {
			if (Client.AccountNumber == AccountNumber) {
				return Client;
			}
		}
		return _CreateEmptyClient();
	}
	clsBankClient Find() {
		return Find(AccountNumber);
	}
	static clsBankClient Find(const string& AccountNumber, const string& Pin) {
		vector<clsBankClient> _vAllClients = _GetAllClients();
		for (const clsBankClient& Client : _vAllClients) {
			if (Client.AccountNumber == AccountNumber && Client.PinCode == Pin) {
				return Client;
			}
		}
		return _CreateEmptyClient();
	}
	enSaveResults Save() {
		switch (_Mode) {
		case EmptyMode:
			return svFaildEmptyObject;

		case UpdateMode:
			_Update();
			return svSucceeded;

		case AddNewMode:
			if (IsClientExist(*this))
				return svFaildAccountNumberExists;
			else {
				_AddNew();
				_Mode = UpdateMode;
				return svSucceeded;
			}
		default: 
			return svFaildEmptyObject;
		}
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	void Delete() {
		vector<clsBankClient> _vAllClients = _GetAllClients();
		for (clsBankClient& client : _vAllClients) {
			if (client.AccountNumber == _AccountNumber) {
				client._MarkedForDelete = true;
				break;
			}
		}
		_Save(_vAllClients);
		*this = _CreateEmptyClient();
	}
	static size_t GetClientsCount() {
		vector<clsBankClient> vClients = _GetAllClients();
		 return vClients.size();
	}
	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	string GetAccountNumber() const {
		return _AccountNumber;
	}
	string GetPinCode() const {
		return _PinCode;
	}
	float GetAccountBalance() const {
		return _AccountBalance;
	}
	bool MarkedForDeleted() {
		return _MarkedForDelete;
	}
	static vector <clsBankClient> GetClientsList() {
		return _GetAllClients();
	}
	static float GetTotalBalances() {
		vector<clsBankClient> vClients = _GetAllClients();
		float TotalBalances = 0;
		for (clsBankClient& client : vClients) {
			TotalBalances += client.AccountBalance;
		}
		return TotalBalances;
	}
	static vector<stTransferLogRecord> GetTransfersLogList() {
		vector<stTransferLogRecord> vTransferLogRecords;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				vector<string> vRecordData = _SeperateEachLineInfo(Line);
				if (vRecordData.size() == 7) {
					stTransferLogRecord Record;
					Record.DateTime = vRecordData[0];
					Record.SourceAccountNumber = vRecordData[1];
					Record.DestinationAccountNumber = vRecordData[2];
					Record.TransferAmount = stod(vRecordData[3]);
					Record.SourceAccountBalanceAfterTransfer = stod(vRecordData[4]);
					Record.DestinationAccountBalanceAfterTransfer = stod(vRecordData[5]);
					Record.UserName = vRecordData[6];
					vTransferLogRecords.push_back(Record);
				}
			}
			MyFile.close();
		}
		return vTransferLogRecords;
	}
	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;
		_AccountBalance -= Amount;
		Save();
		return true;
	}
	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName) {
		if (Amount > _AccountBalance)
			return false;
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}
	__declspec(property(get = GetAccountNumber)) string AccountNumber;
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	void Print()
	{
		clsPerson::Print();
		cout << "\nAccount Number: " << GetAccountNumber();
		cout << "\nPin Code: " << GetPinCode();
		cout << "\nAccount Balance: " << GetAccountBalance();
	}
};