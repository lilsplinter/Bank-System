#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static float _ReadAmount() {
        return clsInputValidate::ReadDblNumber("Enter Amount to Exchange: ");
    }
    static clsCurrency _GetCurrency(string Message) {
        clsCurrency Currency = clsCurrency::FindByCode(
            clsInputValidate::ReadString(Message));
        while (Currency.IsEmpty()) {
            cout << "Currency not found, try again.\n";
            Currency = clsCurrency::FindByCode(
                clsInputValidate::ReadString(Message));
        }
        return Currency;
    }
    static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country;
        cout << "\nCode       : " << Currency.CurrencyCode;
        cout << "\nName       : " << Currency.CurrencyName;
        cout << "\nRate(1$) = : " << Currency.Rate;
        cout << "\n_____________________________\n\n";
    }
    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2) {
        _PrintCurrencyCard(Currency1, "Convert From:");
        float AmountInUSD = Currency1.ConvertToUSD(Amount);
        cout << Amount << " " << Currency1.CurrencyCode
            << " = " << AmountInUSD << " USD\n";
        if (Currency2.CurrencyCode == "USD")
            return;
        cout << "\nConverting from USD to:\n";
        _PrintCurrencyCard(Currency2, "To:");
        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
        cout << Amount << " " << Currency1.CurrencyCode
            << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode;
    }
    static void _Calculate() {
        char Continue = 'y';
        do {
            ClearScreen();
            ShowScreen("Currency Calculator");
            clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 Code: ");
            float Amount = _ReadAmount();
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
            cout << "\n\nDo you want to perform another calculation? (y/n): ";
            cin >> Continue;
            cin.ignore();
        } while (Continue == 'y' || Continue == 'Y');
    }
public:
    static void Show() {
        ClearScreen();
        ShowScreen("Currency Calculator");
        _Calculate();
        Pause();
    }
};