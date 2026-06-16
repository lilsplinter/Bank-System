#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <vector>
class clsAddNewUserScreen : protected clsScreen
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
	static void _AddUser() {
		string Username = clsInputValidate::ReadString("Enter Username: ");
		while (clsUser::IsUserExist(Username)) {
			cout << "Username already exists, try another.\n";
			Username = clsInputValidate::ReadString("Enter Username: ");
		}
		clsUser user = clsUser::GetAddNewUserObject(Username);
		user.FirstName = clsInputValidate::ReadString("First Name: ");
		user.LastName = clsInputValidate::ReadString("Last Name: ");
		user.Email = clsInputValidate::ReadString("Email: ");
		user.Phone = clsInputValidate::ReadString("Phone: ");
		user.Password = clsInputValidate::ReadString("Password: ");
		user.Permissions = _ReadEachAccess();
		if (user.Save() == clsUser::svSucceeded)
			cout << "User Added Successfully!\n";
		else
			cout << "User Was Not Added!\n";
	}
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Add New User");
		_AddUser();
		Pause();
	}
};

