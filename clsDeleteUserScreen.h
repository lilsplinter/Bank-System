#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <vector>
class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _DeleteUser() {
		char DeleteMore;
		ClearScreen();
		do {
			clsUser user = clsUser::Find(clsInputValidate::ReadString("Please Enter the User name: "));
			if (!user.IsEmpty()) {
				cout << "User Found:\n";
				user.Print();
				cout << "\n\nAre you sure you want to delete this user? (y/n)";
				char confirmDelete;
				cin >> confirmDelete;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (confirmDelete == 'y' || confirmDelete == 'Y') {
					user.Delete();
					cout << "User Deleted Successfully!" << endl;
				}
				else {
					cout << "User Deletion Cancelled!" << endl;
				}
			}
			else {
				cout << "User Not Found!" << endl;
			}
			cout << "Do you want to Delete Another User? (y/n)";
			cin >> DeleteMore;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (DeleteMore == 'y' || DeleteMore == 'Y');
	}
public: 
	static void Show() {
		ClearScreen();
		ShowScreen("Delete User Screen");
		_DeleteUser();
		Pause();
	}
};

