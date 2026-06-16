#pragma once
#include <iostream>
#include <limits>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;
class clsScreen
{
protected:
    static void ShowScreen(const string& ScreenName, const string& SubTitle = "") {
        cout << "========================================================================================================================\n";
        cout << "\n\t\t\t\t\t\t " << ScreenName << " \n";
        clsDate today;
        cout << "\t\t\t\t\t\t " << today.DateToString() << " \n";
		cout << "\t\t\t\t\t\t Logged in as: " << CurrentUser.FullName << " \n";
        if (SubTitle != "")
            cout << "\t\t\t\t\t\t " << SubTitle << "\n";
        cout << "========================================================================================================================\n\n";
    }
    static void _PrintSeparator() {
        cout << "________________________________________________________________________________________________________________________\n";
    }
    static void _PrintFooter() {
        cout << "\n________________________________________________________________________________________________________________________\n";
    }
    static void _GoBackMessage() {
        cout << "\n\tPress any key to go back...\n";
        system("pause>0");
    }
    static void Pause() {
        cout << "\n\nPress ENTER to continue...";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    static bool CheckAccessRights(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "========================================================================================================================\n";
            cout << "\n\t\t\t\t\t\t Access Denied! Contact your Admin.\n";
            cout << "========================================================================================================================\n\n";
            return false;
        }
        return true;
    }
    static void ClearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};