#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionOptions {
		eDeposit = 1,
		eWithdraw = 2,
		eTotalBalances = 3,
		eTransfer = 4,
		eTransferLog = 5,
		eExit = 6
	};
	static void _TransactionsMenu() {
		enTransactionOptions number = (enTransactionOptions)clsInputValidate::ReadIntNumberBetween("Choose What do you want to do? [1 to 6]?", 1, 6);
		switch (number) {
		case eDeposit:
			clsDepositScreen::Show();
			Show();
			break;
		case eWithdraw:
			clsWithdrawScreen::Show();
			Show();
			break;
		case eTotalBalances:
			clsTotalBalancesScreen::Show();
			Show();
			break;
		case eTransfer:
			clsTransferScreen::Show();
			Show();
			break;
		case eTransferLog:
			clsTransferLogScreen::Show();
			Show();
			break;
		case eExit:
			return;
			break;
		}
	}
	static void _ShowTransactionsMenu() {
		cout << "\t\t [1] Deposit.\n";
		cout << "\t\t [2] Withdraw.\n";
		cout << "\t\t [3] Total Balances.\n";
		cout << "\t\t [4] Transfer.\n";
		cout << "\t\t [5] Transfer Log.\n";
		cout << "\t\t [6] Back to Main Menu.\n\n";
	}

public:
	static void Show() {
		if (!CheckAccessRights(clsUser::pTranactions)) {
			return;
		}
		ClearScreen();
		ShowScreen("Transactions Screen");
		_ShowTransactionsMenu();
		_TransactionsMenu();
		Pause();
	}
};

