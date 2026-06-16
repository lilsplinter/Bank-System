#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include <vector>
class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void _ShowTotalBalancesScreen(const size_t& ListNumbers) {
		cout << "________________________________________________________________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\t\t Balances List:\n \t\t\t\t\t\t There are " << ListNumbers << " Client(s).\t\t\t\t\t" << endl;
		cout << "________________________________________________________________________________________________________________________" << endl << endl;
		cout << left << setw(20) << "Account Number" << "| ";
		cout << left << setw(40) << "Name" << "| ";
		cout << left << setw(40) << "Account Balance" << endl;
		cout << "________________________________________________________________________________________________________________________";
	}
	static void _PrintClientsBalances(const clsBankClient& client) {
		cout << endl;
		cout << left << setw(20) << client.AccountNumber << "| ";
		cout << left << setw(40) << client.FullName << "| ";
		cout << left << setw(40) << fixed << setprecision(2) << client.AccountBalance;
	}
	static void _TotalBalances(const vector<clsBankClient>& vClients) {
		double AllBalances = 0;
		for (const clsBankClient& client : vClients) {
			cout << endl;	
			_PrintClientsBalances(client);
			AllBalances += client.AccountBalance;
		}
		_PrintFooter();
		cout << "\n\t\t\t\tTotal Balances = " << AllBalances;
	}
public:
	static void Show() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		ClearScreen();
		ShowScreen("Total Balances");
		_ShowTotalBalancesScreen(vClients.size());
		_TotalBalances(vClients);
		Pause();
	}
};

