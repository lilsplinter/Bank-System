#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"
using namespace std;
class clsPerson : public InterfaceCommunication
{
private: 	
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;
public: 
	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}
	void SetFirstName(string FirstName) {
		_FirstName = FirstName; 
	}
	void SetLastName(string LastName) {
		_LastName = LastName; 
	}
	void SetEmail(string Email) { 
		_Email = Email; 
	}
	void SetPhone(string Phone) {
		_Phone = Phone; 
	}
	string GetFirstName() const {
		return _FirstName; 
	}
	string GetLastName() const {
		return _LastName; 
	}
	string GetFullName() const {
		return _FirstName + " " + _LastName;
	}
	string GetEmail() const {
		return _Email; 
	}
	string GetPhone() const {
		return _Phone; 
	}
	void Print() {
		cout << "\nFirst Name: " << GetFirstName();
		cout << "\nLast Name: " << GetLastName();
		cout << "\nFull Name: " << GetFullName();
		cout << "\nEmail: " << GetEmail();
		cout << "\nPhone: " << GetPhone();
	}
	void SendEmail(string Title, string Body)
	{

	}

	void SendFax(string Title, string Body)
	{

	}

	void SendSMS(string Title, string Body)
	{

	}
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;
	__declspec(property(get = GetFullName)) string FullName;
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;
};

