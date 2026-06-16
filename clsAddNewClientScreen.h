#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsAddNewClientScreen : protected clsScreen
{
private:
	static clsBankClient _ReadClientData(const string& AccountNumber) {
		clsBankClient client = clsBankClient::GetAddNewClientObject(AccountNumber);
		client.FirstName = clsInputValidate::ReadString("Enter First Name: ");
		client.LastName = clsInputValidate::ReadString("Enter Last Name: ");
		client.PinCode = clsInputValidate::ReadString("Please Enter The PIN Code: ");
		client.Phone = clsInputValidate::ReadString("Please Enter The Phone Number: ");
		client.AccountBalance = clsInputValidate::ReadDblNumber("Please Enter The Account Balance: ");
		return client;
	}
	static void _AddClient() {
		char AddMore;
		ClearScreen();
		do {
			string AccountNumber = clsInputValidate::ReadString("Please Enter the Account Number: ");
			
			if (!clsBankClient::IsClientExist(AccountNumber)) {
				clsBankClient client = _ReadClientData(AccountNumber);
				if (client.Save() == clsBankClient::svSucceeded) {
					cout << "Client Added Successfully!" << endl;
				}
				else {
					cout << "Client Wasn't Added!";
				}
				cout << "Do you want to Add Another Client? (y/n)";
				cin >> AddMore;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else {
				cout << "Client with Account Number " << AccountNumber << " already exists!" << endl;
				cout << "Do you want to try again? (y/n)";
				cin >> AddMore;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		} while (AddMore == 'y' || AddMore == 'Y');
	}
public:
	static void Show() {
		if (!CheckAccessRights(clsUser::pAddNewClient)) {
			return;
		}
		clsScreen::ClearScreen();
		ShowScreen("Add New Client Screen");
		_AddClient();
		clsScreen::Pause();
	}
};

