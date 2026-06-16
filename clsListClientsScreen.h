#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>

class clsListClientsScreen : protected clsScreen
{
private:
	static void _PrintUsersListHeader(const size_t& ListNumbers) {
		cout << "________________________________________________________________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\t\t Users List:\n \t\t\t\t\t\t There are " << ListNumbers << " User(s).\t\t\t\t\t" << endl;
		cout << "________________________________________________________________________________________________________________________" << endl << endl;
	}
	static void _PrintTableDecoration() {
		cout << left << setw(20) << "Account Number" << "| ";
		cout << left << setw(15) << "Pin Code" << "| ";
		cout << left << setw(40) << "Name" << "| ";
		cout << left << setw(20) << "Phone" << "| ";
		cout << left << setw(20) << "Account Balance" << endl;
		cout << "________________________________________________________________________________________________________________________";
	}
	static void _PrintClientInTheList(const clsBankClient& client) {
		cout << endl;
		cout << left << setw(20) << client.AccountNumber << "| ";
		cout << left << setw(15) << client.PinCode << "| ";
		cout << left << setw(40) << client.FullName << "| ";
		cout << left << setw(20) << client.Phone << "| ";
		cout << left << setw(20) << fixed << setprecision(2) << client.AccountBalance;
	}
	static void _ShowClientsList() {
		vector<clsBankClient> _vAllClients = clsBankClient::GetClientsList();
		_PrintUsersListHeader(_vAllClients.size());
		if (_vAllClients.size() > 0) {
			_PrintTableDecoration();
			for (clsBankClient& client : _vAllClients) {
				_PrintClientInTheList(client);
			}
		} else {
			cout << "\n\t\t\t\t\t\t No Clients Available.\t\t\t\t\t" << endl;
		}
		_PrintFooter();
	}
public:
	static void Show() {
		if (!CheckAccessRights(clsUser::pListClients)) {
			return;
		}
		ShowScreen("List Clients Screen");
		_ShowClientsList();
	}
};

