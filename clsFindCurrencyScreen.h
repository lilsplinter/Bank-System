#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"
class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrency(const clsCurrency& Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country;
        cout << "\nCode       : " << Currency.CurrencyCode;
        cout << "\nName       : " << Currency.CurrencyName;
        cout << "\nRate(1$) = : " << Currency.Rate;

        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }
    static void _FindCurrency()
    {
        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;
        cin >> Answer;
        if (Answer == 1)
        {
            clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString("\nPlease Enter CurrencyCode: "));
            _ShowResults(Currency);
        }
        else
        {
            clsCurrency Currency = clsCurrency::FindByCountry(clsInputValidate::ReadString("\nPlease Enter Country Name: "));
            _ShowResults(Currency);
        }
    }
public:
    static void Show() {
        ClearScreen();
        ShowScreen("Find Currency");
        _FindCurrency();
        Pause();
    }
};

