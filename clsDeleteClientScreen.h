#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen
{
private: 
	static void _DeleteClient() {
		char DeleteMore;
		ClearScreen();
		do {
			clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number: "));
			if (!client.IsEmpty()) {
				cout << "Client Found:\n";
				client.Print();
				cout << "\n\nAre you sure you want to delete this client? (y/n)";
				char confirmDelete;
				cin >> confirmDelete;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (confirmDelete == 'y' || confirmDelete == 'Y') {
					client.Delete();
					cout << "Client Deleted Successfully!" << endl;
				}
				else {
					cout << "Client Deletion Cancelled!" << endl;
				}
			}
			else {
				cout << "Client Not Found!" << endl;
			}
			cout << "Do you want to Delete Another Client? (y/n)";
			cin >> DeleteMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (DeleteMore == 'y' || DeleteMore == 'Y');
	}
public:
	static void Show() {
		if (!CheckAccessRights(clsUser::pDeleteClient)) {
			return;
		}
		ClearScreen();
		ShowScreen("Delete Client Screen");
		_DeleteClient();
		Pause();
	}
};

