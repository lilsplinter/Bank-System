#pragma once
#include "clsUser.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintUsersListHeader(const size_t& ListNumbers) {
        cout << "________________________________________________________________________________________________________________________" << endl;
        cout << "\n\t\t\t\t\t\t Users Login Register List:\n \t\t\t\t\t\t There are " << ListNumbers << " User(s).\t\t\t\t\t" << endl;
        cout << "________________________________________________________________________________________________________________________" << endl << endl;
    }
    static void _PrintUsersTableDecoration() {
        cout << left << setw(25) << "Date/Time" << "| ";
        cout << left << setw(20) << "User Name" << "| ";
        cout << left << setw(20) << "Password" << "| ";
        cout << left << setw(12) << "Permissions" << endl;
        cout << "________________________________________________________________________________________________________________________";
    }
    static void _PrintUserInTheList(const clsUser::stLoginRegisterRecord& Record) {
        cout << endl;
        cout << left << setw(25) << Record.DateTime << "| ";
        cout << left << setw(20) << Record.Username << "| ";
        cout << left << setw(20) << Record.Password << "| ";
        cout << left << setw(12) << Record.Permissions;
    }
    static void _ShowUsersList(const vector<clsUser::stLoginRegisterRecord>& vUsers) {
        _PrintUsersListHeader(vUsers.size());
        _PrintUsersTableDecoration();

        if (vUsers.size() == 0) {
            cout << "\n\t\t\t\tNo Users Logins Available In the System!\n";
        }
        else {
            for (const clsUser::stLoginRegisterRecord& Record : vUsers) {
                _PrintUserInTheList(Record);
            }
            cout << endl;
        }
        cout << "________________________________________________________________________________________________________________________" << endl;
    }
public:
    static void Show() {
        ClearScreen();
        if (!CheckAccessRights(clsUser::pShowLogInRegister)) {
            return;
		}
		ShowScreen("Login Register Screen");
        vector<clsUser::stLoginRegisterRecord> vRecords = clsUser::GetLoginRegisterList();
        _ShowUsersList(vRecords);
        Pause();
    }
};