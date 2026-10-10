#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsCurrency.h"
#include <iomanip>
class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void _PrintCurrenciesListHeader(const size_t& ListNumbers) {
        cout << "________________________________________________________________________________________________________________________" << endl;
        cout << "\n\t\t\t\t\t\t Currencies List:\n \t\t\t\t\t\t There are " << ListNumbers << " Currency(s).\t\t\t\t\t" << endl;
        cout << "________________________________________________________________________________________________________________________" << endl << endl;
    }
    static void _PrintTableDecoration() {
        cout << left << setw(20) << "Country" << "| ";
        cout << left << setw(15) << "Currency Code" << "| ";
        cout << left << setw(40) << "Currency Name" << "| ";
        cout << left << setw(20) << "Rate" << endl;
        cout << "________________________________________________________________________________________________________________________";
    }
    static void _PrintCurrencyInTheList(const clsCurrency& currency) {
        cout << endl;
        cout << left << setw(20) << currency.Country << "| ";
        cout << left << setw(15) << currency.CurrencyCode << "| ";
        cout << left << setw(40) << currency.CurrencyName << "| ";
        cout << left << setw(20) << fixed << setprecision(2) << currency.Rate;
    }
    static void _ShowCurrenciesList() {
        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
        _PrintCurrenciesListHeader(vCurrencies.size());
        if (vCurrencies.size() > 0) {
            _PrintTableDecoration();
            for (const clsCurrency& currency : vCurrencies) {
                _PrintCurrencyInTheList(currency);
            }
        }
        else {
            cout << "\n\t\t\t\t\t\t No Currencies Available.\t\t\t\t\t" << endl;
        }
        _PrintFooter();
    }
public:
    static void Show() {
        ClearScreen();
        ShowScreen("Currencies List Screen");
        _ShowCurrenciesList();
        Pause();
    }
};