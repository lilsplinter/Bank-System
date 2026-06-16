#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsFindClientScreen : protected clsScreen
{
private:
	static void _FindClient() {
		char FindMore = 'y';
		ClearScreen();
		do {
			clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number: "));
			if (!client.IsEmpty()) {
				client.Print();
			}
			else {
				cout << "Client Wasn't Found!" << endl;
			}
			cout << "do you want to find another client? (y/n)";
			cin >> FindMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (FindMore == 'y' || FindMore == 'Y');
	}
public: 
	static void Show() {
		if (!CheckAccessRights(clsUser::pFindClient)) {
			return;
		}
		ClearScreen();
		ShowScreen("Find Client Screen");
		_FindClient();
		Pause();
	}
};

