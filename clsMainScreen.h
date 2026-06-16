#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLogoutScreen.h"
#include "clsExitScreen.h"
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
using namespace std;
class clsMainScreen :protected clsScreen
{
private:
    static void _Logout() {
        CurrentUser = clsUser::Find("", "");
    }
	enum enMainMenuOptions {
		eListClients = 1,
		eAddNewClient = 2,
		eDeleteClient = 3,
		eUpdateClientInfo = 4,
		eFindClient = 5,
		eTransactions = 6,
		eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eLogout = 10,
        eExit = 11
	}; 
	static void ShowMainMenuScreen() {
		cout << "========================================================================================================================" << endl;
		cout << "\n\t\t\t\t\t\t  Main Menu \t\t\t\t\t\n\n";
        clsDate today;
        cout << "\t\t\t\t\t\t " << today.DateToString() << " \n";
        cout << "\t\t\t\t\t\t Logged in as: " << CurrentUser.FullName << " \n"; 
		cout << "========================================================================================================================" << endl;
		cout << "\t\t [1] Show Client List.\n";
		cout << "\t\t [2] Add New Client.\n";
		cout << "\t\t [3] Delete Client.\n";
		cout << "\t\t [4] Update Client Info.\n";
		cout << "\t\t [5] Find Client.\n";
		cout << "\t\t [6] Transactions.\n";
		cout << "\t\t [7] Manage Users.\n";
		cout << "\t\t [8] Login Register.\n";
        cout << "\t\t [9] Currency Exchange.\n";
        cout << "\t\t [10] Logout.\n";
        cout << "\t\t [11] Exit.\n\n";
	}
    static void _PerformMainMenuOption(enMainMenuOptions Option) {
        switch (Option) {
        case eListClients:
            system("cls");
            clsListClientsScreen::Show();
            Show();
            break;
        case eAddNewClient:
            system("cls");
            clsAddNewClientScreen::Show();
            Show();
            break;
        case eDeleteClient:
            system("cls");
            clsDeleteClientScreen::Show();
            Show();
            break;
        case eUpdateClientInfo:
            system("cls");
            clsUpdateClientScreen::Show();
            Show();
            break;
        case eFindClient:
            system("cls");
            clsFindClientScreen::Show();
            Show();
            break;
        case eTransactions:
            system("cls");
            clsTransactionsScreen::Show();
            Show();
            break;
        case eManageUsers:
            system("cls");
            clsManageUsersScreen::Show();
            Show();
            break;
        case eLoginRegister:
            system("cls");
            clsLoginRegisterScreen::Show();
            Show();
            break;
        case eCurrencyExchange:
            clsCurrencyExchangeMainScreen::Show();
            Show();
            break;  
        case eLogout:
            ClearScreen();
            _Logout();
            return;
            break;
        case eExit:
            system("cls");
            exit(0);
            break;
        }
    }
    static short _ReadMainMenuOption() {
        cout << "Choose [1-9]: ";
        return clsInputValidate::ReadIntNumberBetween("Enter number between 1 to 11: ", 1, 11);
    }
public:
    static void Show() {
        system("cls");
        ShowMainMenuScreen();
        _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
    }
};

