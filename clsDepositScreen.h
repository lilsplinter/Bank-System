#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsDepositScreen : protected clsScreen
{
private:
	static void _PerformDeposit(clsBankClient& client, const double& DepositAmount) {
		char MakeSure;
		cout << "Are you sure to perform this transaction? (y/n)?";
		cin >> MakeSure;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (MakeSure == 'y' || MakeSure == 'Y') {
			client.AccountBalance += DepositAmount;
			client.Save();
			cout << "Transaction completed successfully." << endl;
		}
		else {
			return;
		}
	}
	static void _Deposit() {
		clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		while (client.IsEmpty()) {
			cout << "Client not found, try again." << endl;
			client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		}
		client.Print();
		double DepositAmount = clsInputValidate::ReadDblNumber("Please Enter Deposit Amount? ");
		_PerformDeposit(client, DepositAmount);
	}
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Deposit Screen");
		_Deposit();
		Pause();	
	}
};

