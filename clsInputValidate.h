#pragma once
#include <iostream>
#include "clsDate.h"
class clsInputValidate
{

public:
	template <typename T>
	static bool IsNumberBetween(T number, T from, T to) {
		return number >= from && number <= to;
	}
	static bool ReadCharOption(const string& validoptions, const string& message) {
		char option;
		while (true) {
			cout << message;
			cin >> option;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (validoptions.find(option) != string::npos) {
				if (option == 'y' || option == 'Y') {
					return true;
				}
				else {
					return false;
				}
			}
			cout << "Invalid option. Try again.\n";
		}
	}
	static string ReadString(const string& message) {
		cout << message;
		string input;
		if (cin.peek() == '\n') cin.ignore();
		getline(cin, input);
		return input;
	}
	static bool IsDateBetween(const clsDate& date ,const  clsDate& from ,const clsDate& to) {
		clsDate fromCopy = from;
		clsDate toCopy = to;
		if (clsDate::IsDate1BeforeDate2(toCopy, fromCopy)) {
			clsDate::SwapDates(fromCopy, toCopy);
		}
		bool isDateBeforeTo = clsDate::IsDate1BeforeDate2(date, toCopy) || clsDate::IsDate1EqualDate2(date, toCopy);
		bool isDateAfterFrom = clsDate::IsDate1BeforeDate2(fromCopy, date) || clsDate::IsDate1EqualDate2(date, fromCopy);
		return isDateAfterFrom && isDateBeforeTo;
	}
	static int ReadIntNumber(const string& message) {
		cout << message;
		int number;
		while (true) {
			cin >> number;
			if (!cin.fail()) {
				return number;
			}
			else {
				cout << "Invalid number, please try again: " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
	static int ReadIntNumberBetween(const string& message , int from, int to) {
		if (from > to) {
			swap(from, to);
		}
		int number = ReadIntNumber(message);
		while (!IsNumberBetween(number, from, to)) {
			cout << "Invalid number, please try again: " << endl;
			number = ReadIntNumber(message);
		}
		return number;
	}
	static double ReadDblNumber(const string& message) {
		cout << message;
		double number;
		while (true) {
			cin >> number;
			if (!cin.fail()) {
				return number;
			}
			else {
				cout << "Invalid number, please try again: " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
	static double ReadDblNumberBetween (const string& message, double from, double to) {
		if (from > to) {
			swap(from, to);
		}
		double number = ReadDblNumber(message);
		while (!IsNumberBetween(number, from, to)) {
			cout << "Invalid number, please try again: " << endl;
			number = ReadDblNumber(message);
		}
		return number;
	}
	static bool IsValidDate(const clsDate& date = clsDate()) {
		return clsDate::IsValidDate(date);
	}
};

