#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadDblNumber("PLease Enter the new rate:");
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country;
        cout << "\nCode       : " << Currency.CurrencyCode;
        cout << "\nName       : " << Currency.CurrencyName;
        cout << "\nRate(1$) = : " << Currency.Rate;

        cout << "\n_____________________________\n";

    }
    static void _FindCurrency() {
        clsCurrency Currency = clsCurrency::FindByCode(
            clsInputValidate::ReadString("Please Enter Currency Code: "));

        while (Currency.IsEmpty()) {
            cout << "Currency not found, try again.\n";
            Currency = clsCurrency::FindByCode(
                clsInputValidate::ReadString("Please Enter Currency Code: "));
        }

        _PrintCurrency(Currency);

        char Answer;
        cout << "\nAre you sure you want to update the rate? (y/n): ";
        cin >> Answer;
        cin.ignore();

        if (Answer == 'y' || Answer == 'Y') {
            Currency.UpdateRate(_ReadRate());
            cout << "\nRate Updated Successfully!\n";
            _PrintCurrency(Currency);
        }
    }
public:
	static void Show() {
		ClearScreen();
		ShowScreen("Update Currency Rate");
        _FindCurrency();
		Pause();
	}
};

