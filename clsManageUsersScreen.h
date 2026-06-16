#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersOptions {
		eListUsers = 1,
		eAddNewUser = 2,
		eDeleteUser = 3,
		eUpdateUserInfo = 4,
		eFindUser = 5,
		eExit = 6
	};
	static void _ShowManageUsersScreen() {
		cout << "========================================================================================================================" << endl;
		cout << "\n\t\t\t\t\t\t  Main Menu \t\t\t\t\t\n\n";
		clsDate today;
		cout << "\t\t\t\t\t\t " << today.DateToString() << " \n";
		cout << "\t\t\t\t\t\t Logged in as: " << CurrentUser.FullName << " \n";
		cout << "========================================================================================================================" << endl;
		cout << "\t\t [1] List Users\n";
		cout << "\t\t [2] Add New User.\n";
		cout << "\t\t [3] Delete User.\n";
		cout << "\t\t [4] Update User.\n";
		cout << "\t\t [5] Find User.\n";
		cout << "\t\t [6] Main Menu.\n";
	}
	static void _PerformManageUsersOption(enManageUsersOptions Option) {
		switch (Option) {
		case eListUsers:
			clsListUsersScreen::Show();
			Show();
			break;
		case eAddNewUser:
			clsAddNewUserScreen::Show();
			Show();
			break;
		case eDeleteUser:
			clsDeleteUserScreen::Show();
			Show();
			break;
		case eUpdateUserInfo:
			clsUpdateUserScreen::Show();
			Show();
			break;
		case eFindUser:
			clsFindUserScreen::Show();
			Show();
			break;
		case eExit:
			return;
		}
	}
public: 
	static void Show() {
		if (!CheckAccessRights(clsUser::pManageUsers)) {
			return;
		}
		ClearScreen();
		ShowScreen("Manage Users Screen");
		_ShowManageUsersScreen();
		_PerformManageUsersOption((enManageUsersOptions)clsInputValidate::ReadIntNumberBetween("Choose What do you want to do? [1 to 6]?", 1, 6));
	}
};

