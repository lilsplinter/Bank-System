#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
    enum enCurrenciesMainMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4, eExit = 5
    };
    static void _ShowCurrenciesMenu() {
        cout << "\t\t [1] List Currencies.\n";
        cout << "\t\t [2] Find Currency.\n";
        cout << "\t\t [3] Update Rate.\n";
        cout << "\t\t [4] Currency Calculator.\n";
        cout << "\t\t [5] Main Menu.\n\n";
    }
    static void _ShowCurrenciesListScreen() {
        clsCurrenciesListScreen::Show();
    }
    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::Show();
    }
    static void _ShowUpdateCurrencyRateScreen() {
        clsUpdateCurrencyRateScreen::Show();
    }
    static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculatorScreen::Show();
    }
    static void _PerformCurrenciesMenuOption(enCurrenciesMainMenueOptions Option) {
        switch (Option) {
        case eListCurrencies:
            _ShowCurrenciesListScreen();
            Show();
            break;
        case eFindCurrency:
            _ShowFindCurrencyScreen();
            Show();
            break;
        case eUpdateCurrencyRate:
            _ShowUpdateCurrencyRateScreen();
            Show();
            break;
        case eCurrencyCalculator:
            _ShowCurrencyCalculatorScreen();
            Show();
            break;
        case eExit:
            return;
        }
    }
public:
    static void Show() {
        ClearScreen();
        ShowScreen("Currency Exchange Main Screen");
        _ShowCurrenciesMenu();
        _PerformCurrenciesMenuOption(
            (enCurrenciesMainMenueOptions)clsInputValidate::ReadIntNumberBetween("Choose [1-5]: ", 1, 5));
    }
};