#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <vector>
class clsListUsersScreen : protected clsScreen
{
private:
	static void _PrintUsersListHeader(const size_t& ListNumbers) {
		cout << "________________________________________________________________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\t\t Users List:\n \t\t\t\t\t\t There are " << ListNumbers << " User(s).\t\t\t\t\t" << endl;
		cout << "________________________________________________________________________________________________________________________" << endl << endl;
	}
	static void _PrintUsersTableDecoration() {
		cout << left << setw(20) << "User Name" << "| ";
		cout << left << setw(30) << "Full Name" << "| ";
		cout << left << setw(25) << "Email" << "| ";
		cout << left << setw(15) << "Phone" << "| ";
		cout << left << setw(20) << "Password" << "| ";
		cout << left << setw(12) << "Permissions" << endl;
		cout << "________________________________________________________________________________________________________________________";
	}

	static void _PrintUserInTheList(const clsUser& user) {
		cout << endl;
		cout << left << setw(20) << user.Username << "| ";
		cout << left << setw(30) << user.FullName << "| ";
		cout << left << setw(25) << user.Email << "| ";
		cout << left << setw(15) << user.Phone << "| ";
		cout << left << setw(20) << user.Password << "| ";
		cout << left << setw(12) << user.Permissions;
	}
	static void _ShowUsersList(const vector <clsUser>& vUsers) {
		_PrintUsersListHeader(vUsers.size());
		_PrintUsersTableDecoration();
		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!\n";
		else {
			for (const clsUser& user : vUsers) {
				cout << endl;
				_PrintUserInTheList(user);
			}
		}
		_PrintFooter();
	}
public:
	static void Show() {
		vector <clsUser> vUsers = clsUser::GetUsersList();
		ClearScreen();
		ShowScreen("List Users Screen");
		_ShowUsersList(vUsers);
		Pause();
	}
};

