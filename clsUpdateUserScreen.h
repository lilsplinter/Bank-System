#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <vector>
class clsUpdateUserScreen : protected clsScreen
{
private:
	static int _ReadEachAccess() {
		int permissions = 0;
		cout << "Do you want to give the user Access to:" << endl;
		if (clsInputValidate::ReadCharOption("yYnN", "Show Client List? (y/n)")) {
			permissions |= clsUser::pListClients;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Add New Client? (y/n)")) {
			permissions |= clsUser::pAddNewClient;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Delete Client? (y/n)")) {
			permissions |= clsUser::pDeleteClient;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Update Client Info? (y/n)")) {
			permissions |= clsUser::pUpdateClients;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Find Client? (y/n)")) {
			permissions |= clsUser::pFindClient;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Transactoins? (y/n)")) {
			permissions |= clsUser::pTranactions;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Manage Users? (y/n)")) {
			permissions |= clsUser::pManageUsers;
		}
		if (clsInputValidate::ReadCharOption("yYnN", "Show Login Register? (y/n)")) {
			permissions |= clsUser::pShowLogInRegister;
		}
		return permissions;
	}
	static void _UpdateUserData(clsUser& user) {
		cout << "Please Enter the new data: " << endl;
		user.Password = clsInputValidate::ReadString("Please Enter The Password: ");
		user.FirstName = clsInputValidate::ReadString("Please Enter The First Name: ");
		user.LastName = clsInputValidate::ReadString("Please Enter The Last Name: ");
		user.Phone = clsInputValidate::ReadString("Please Enter The Phone Number: ");
		bool IsAdmin = clsInputValidate::ReadCharOption("yYnN", "Give full access? (y/n)");
		if (IsAdmin) {
			user.Permissions = -1;
		}
		else {
			user.Permissions = _ReadEachAccess();
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	static void _UpdateUserInfo() {
		char UpdateMore = 'y';
		ClearScreen();
		do {
			clsUser user = clsUser::Find(clsInputValidate::ReadString("Please Enter the User name: "));
			if (!user.IsEmpty()) {
				_UpdateUserData(user);
				user.Save();
				cout << "User Updated Successfully!" << endl;
			}
			else {
				cout << "User Wasn't Found!" << endl;
			}
			cout << "Do you want to update another user info? (y/n)";
			cin >> UpdateMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (UpdateMore == 'y' || UpdateMore == 'Y');
	}
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Update User Screen");
		_UpdateUserInfo();
		Pause();
	}
};

