#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsWithdrawScreen : protected clsScreen
{
private:
	static bool _CheckWithdraw(clsBankClient& client, const double& WithdrawAmount) {
		return client.AccountBalance >= WithdrawAmount;
	}
	static void _PerformWithdraw(clsBankClient& client, const double& WithdrawAmount) {
		char MakeSure;
		cout << "Are you sure to perform this transaction? (y/n)?";
		cin >> MakeSure;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (MakeSure == 'y' || MakeSure == 'Y') {
			client.AccountBalance -= WithdrawAmount;
			client.Save();
			cout << "Transaction completed successfully." << endl;
		}
		else {
			return;
		}
	}
	static void _Withdraw() {
		clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		while (client.IsEmpty()) {
			cout << "Client not found, try again." << endl;
			client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		}
		client.Print();
		double WithdrawAmount = clsInputValidate::ReadDblNumber("Please Enter Withdraw Amount? ");
		while (!_CheckWithdraw(client, WithdrawAmount)) {
			cout << "Amount Exceeds The balance, you can Withdraw up to " << fixed << setprecision(2) << (client.AccountBalance) << endl;
			WithdrawAmount = clsInputValidate::ReadDblNumber("Please Enter Withdraw Amount? ");
		}
		_PerformWithdraw(client, WithdrawAmount);
	}
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Withdraw Screen");
		_Withdraw();
		Pause();
	}
};

