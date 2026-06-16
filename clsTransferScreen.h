#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "Global.h"
class clsTransferScreen : protected clsScreen
{
private:
	static void _Transfer() {
		clsBankClient client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		while (client.IsEmpty()) {
			cout << "Client not found, try again." << endl;
			client = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number? "));
		}
		client.Print();
		cout << "\nPlease Enter the Account Number to transfer to? ";
		clsBankClient targetClient = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number to transfer to? "));
		while (targetClient.IsEmpty()) {
			cout << "Client not found, try again." << endl;
			targetClient = clsBankClient::Find(clsInputValidate::ReadString("Please Enter the Account Number to transfer to? "));
		}
		targetClient.Print();
		double TransferAmount = clsInputValidate::ReadDblNumber("Please Enter Transfer Amount? ");
		
		if (TransferAmount > client.AccountBalance) {
			cout << "Insufficient balance, try again." << endl;
			return;
		}

		char MakeSure;
		cout << "Are you sure to perform this transaction? (y/n)?";
		cin >> MakeSure;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (MakeSure == 'y' || MakeSure == 'Y') {
			if (client.Transfer(TransferAmount, targetClient, CurrentUser.Username))
				cout << "Transaction completed successfully." << endl;
			else
				cout << "Transfer failed!" << endl;
		}
		else {
			return;
		}

	}
public:
	static void Show() {
		ClearScreen();
		if (!CheckAccessRights(clsUser::pTranactions)) {
			return;
		}
		ShowScreen("Transfer Screen");
		_Transfer();
		Pause();
	}
};

