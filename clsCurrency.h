#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode = EmptyMode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
	bool _MarkedForDelete = false;
	static clsCurrency _CreateEmptyCurrency() {
		return clsCurrency(EmptyMode, "", "", "", 0);
	}
	static vector<string> _LoadCurrenciesDataFromFile(const string& filename = "Currencies.txt") {
		vector<string> vCurrenciesData;
		fstream MyFile(filename, ios::in);
		if (!MyFile.is_open()) {
			cerr << "Error: Could not open file: " << filename << endl;
			return vCurrenciesData;
		}
		string line;
		while (getline(MyFile, line)) {
			vCurrenciesData.push_back(line);
		}
		MyFile.close();
		return vCurrenciesData;
	}
	static void _SettingEachCurrencyDataToObject(clsCurrency& currency, const vector <string>& vCurrenciesData) {
		currency._Mode = UpdateMode;
		currency._Country = vCurrenciesData[0];
		currency._CurrencyCode = vCurrenciesData[1];
		currency._CurrencyName = vCurrenciesData[2];
		currency._Rate = stof(vCurrenciesData[3]);
	}
	static vector <string> _SeparateEachLineInfo(const string& line, const string& separator = "#//#") {
		vector <string> currency;
		string temp = line;
		size_t pos = temp.find(separator);
		size_t sepLength = separator.length();
		while (pos != string::npos) {
			currency.push_back(temp.substr(0, pos));
			temp = temp.substr(pos + sepLength);
			pos = temp.find(separator);
		}
		currency.push_back(temp);
		return currency;
	}
	static vector <clsCurrency> _ConvertCurrencyDataToVectorOfObjects(const vector <string>& vLines) {
		vector <clsCurrency> vAllCurrencies;
		for (const string& line : vLines) {
			vector<string> vCurrencyData = _SeparateEachLineInfo(line);
			if (vCurrencyData.size() == 4) {
				clsCurrency currency = _CreateEmptyCurrency();
				_SettingEachCurrencyDataToObject(currency, vCurrencyData);
				vAllCurrencies.push_back(currency);
			}
		}
		return vAllCurrencies;
	}
	static string _ConvertCurrencyToLine(const clsCurrency& currency) {
		string line;
		line += currency._Country + "#//#";
		line += currency._CurrencyCode + "#//#";
		line += currency._CurrencyName + "#//#";
		line += to_string(currency._Rate);
		return line;
	}
	static vector <clsCurrency> _GetAllCurrencies() {
		vector <string> vLines = _LoadCurrenciesDataFromFile();
		return _ConvertCurrencyDataToVectorOfObjects(vLines);
	}
	static void _Save(const vector<clsCurrency>& vCurrenciesData) {
		vector<clsCurrency> _vAllCurrencies = _GetAllCurrencies();
		fstream MyFile("Currencies.txt", ios::out);
		if (!MyFile.is_open()) {
			cerr << "Error: Could not open file for writing." << endl;
			return;
		}
		for (const clsCurrency& currency : vCurrenciesData) {
			if (!currency._MarkedForDelete) {
				MyFile << _ConvertCurrencyToLine(currency) << endl;
			}
		}
		MyFile.close();

	}
	static void _AddDataLineToFile(const string& line) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}
		MyFile.close();
	}
	void _Update() {
		vector<clsCurrency> _vAllCurrencies = _GetAllCurrencies();
		for (clsCurrency& currency : _vAllCurrencies) {
			if (currency._CurrencyCode == _CurrencyCode) {
				currency = *this;
				break;
			}
		}
		_Save(_vAllCurrencies);
	}
	static string _ToUpper(string str)
	{
		transform(str.begin(),
			str.end(),
			str.begin(),
			::toupper);

		return str;
	}
public:
	clsCurrency(enMode Mode, const string& Country, const string& CurrencyCode, const string& CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}
	static clsCurrency FindByCode(string CurrencyCode) {
		vector<clsCurrency> _vAllCurrencies = _GetAllCurrencies();
		CurrencyCode = _ToUpper(CurrencyCode);
		for (const clsCurrency& currency : _vAllCurrencies) {
			if (_ToUpper(currency._CurrencyCode) == CurrencyCode) {
				return currency;
			}
		}
		return _CreateEmptyCurrency();
	}
	static clsCurrency FindByCountry(string Country) {
		vector<clsCurrency> _vAllCurrencies = _GetAllCurrencies();
		Country = _ToUpper(Country);
		for (const clsCurrency& currency : _vAllCurrencies) {
			if (_ToUpper(currency._Country) == Country) {
				return currency;
			}
		}
		return _CreateEmptyCurrency();
	}
	static bool IsCurrencyExist(string CurrencyCode) {
		return !FindByCode(CurrencyCode).IsEmpty();
	}
	static vector<clsCurrency> GetCurrenciesList() {
		return _GetAllCurrencies();
	}
	static vector<float> GetAllUSDRates() {
		vector<clsCurrency> _vAllCurrencies = _GetAllCurrencies();
		vector <float> vAllUSDRates;
		for (const clsCurrency& currency : _vAllCurrencies) {
			vAllUSDRates.push_back(currency._Rate);
		}
		return vAllUSDRates;
	}
	float ConvertToUSD(float Amount)
	{
		if (abs(_Rate) < 0.00001) {
			return 0;
		}
		return Amount / _Rate;
	}
	float ConvertFromUSD(float Amount)
	{
		return Amount * _Rate;
	}
	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		return Currency2.ConvertFromUSD(AmountInUSD);
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
	string GetCountry() const {
		return _Country;
	}
	string GetCurrencyCode() const
	{
		return _CurrencyCode;
	}
	string GetCurrencyName() const
	{
		return _CurrencyName;
	}
	float GetRate() const
	{
		return _Rate;
	}
	__declspec(property(get = GetCountry)) string Country;
	__declspec(property(get = GetCurrencyCode)) string CurrencyCode;
	__declspec(property(get = GetCurrencyName)) string CurrencyName;
	__declspec(property(get = GetRate)) float Rate;
};
