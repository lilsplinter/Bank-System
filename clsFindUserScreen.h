#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <vector>
class clsFindUserScreen : protected clsScreen
{
private:
	static void _FindUser() {
		char FindMore = 'y';
		ClearScreen();
		do {
			clsUser client = clsUser::Find(clsInputValidate::ReadString("Please Enter the User Name: "));
			if (!client.IsEmpty()) {
				client.Print();
			}
			else {
				cout << "User Wasn't Found!" << endl;
			}
			cout << "do you want to find another user? (y/n)";
			cin >> FindMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (FindMore == 'y' || FindMore == 'Y');
	}
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Find User Screen");
		_FindUser();
		Pause();
	}
};

