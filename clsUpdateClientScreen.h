#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _UpdateClientData(clsBankClient& client) {
		cout << "Please Enter the new data: " << endl;
		client.PinCode = clsInputValidate::ReadString("Please Enter The PIN Code: ");
		client.FirstName = clsInputValidate::ReadString("Please Enter The First Name: ");
		client.LastName = clsInputValidate::ReadString("Please Enter The Last Name: ");
		client.Phone = clsInputValidate::ReadString("Please Enter The Phone Number: ");
		client.AccountBalance = clsInputValidate::ReadDblNumber("Please Enter The Account Balance: ");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	static void _UpdateClientInfo() {
		char UpdateMore = 'y';
		ClearScreen();
		do {
			clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number: "));
			if (!client.IsEmpty()) {
				_UpdateClientData(client);
				client.Save();
				cout << "Client Updated Successfully!" << endl;
			}
			else {
				cout << "Client Wasn't Found!" << endl;
			}
			cout << "Do you want to update another client info? (y/n)";
			cin >> UpdateMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (UpdateMore == 'y' || UpdateMore == 'Y');
	}
public: 
	static void Show() {
		if (!CheckAccessRights(clsUser::pUpdateClients)) {
			return;
		}
		ClearScreen();
		ShowScreen("Update Client Screen");
		_UpdateClientInfo();	
		Pause();
	}
};

