#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
#include <vector>
class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login() {
        string UserName, Password;
		short LoginAttempts = 0;
        do {
            UserName = clsInputValidate::ReadString("Please Enter Your User Name: ");
            Password = clsInputValidate::ReadString("Please Enter Your Password: ");
            CurrentUser = clsUser::Find(UserName, Password);
            cout << "Found: " << !CurrentUser.IsEmpty() << endl;
            if (CurrentUser.IsEmpty()) {
                LoginAttempts++;
                cout << "Invalid Username/Password, try again.\n";
                cout << "Login Attempts: " << LoginAttempts << "/3\n";
                cout << "Login Attempts Remaining: " << (3 - LoginAttempts) << "\n";
            }
        } while (CurrentUser.IsEmpty() && LoginAttempts < 3);
        if (CurrentUser.IsEmpty()) {
            cout << "Too many failed login attempts. Exiting...\n";
            return false;
        }
        else {
			CurrentUser.RegisterLogin();
            clsMainScreen::Show();
			return true;
        }
    }
public:
    static bool Show() {
        ClearScreen();
        ShowScreen("Login Screen");
        return _Login();
    }
};

