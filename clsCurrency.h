#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enCurrencyMode { eEmptyMode = 0, eUpdateMode = 1 };
	enCurrencyMode _Mode;

	string _Country = "";
	string _CurrencyCode = "";
	string _CurrencyName = "";
	float _Rate = 0;

	static clsCurrency _ConvertCurrencyLineToObject(const string& CurrencyLine, const string& Seperator = "#//#")
	{
		vector<string> _vCurrencyData;
		_vCurrencyData = clsString::Split(CurrencyLine, Seperator);

		return clsCurrency(enCurrencyMode::eUpdateMode, _vCurrencyData[0],
			_vCurrencyData[1], _vCurrencyData[2], stof(_vCurrencyData[3]));
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector<clsCurrency> _vCurrenciesData;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string sLine = "";
			while (getline(MyFile, sLine))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(sLine);
				_vCurrenciesData.push_back(Currency);
			}
			MyFile.close();
		}

		return _vCurrenciesData;
	}

	string _ConvertCurrencyObjectToLine(const clsCurrency& Currency, const string& Seperator = "#//#")
	{

		string sCurrencyLine = "";
		sCurrencyLine += Currency.Country() + Seperator;
		sCurrencyLine += Currency.CurrencyCode() + Seperator;
		sCurrencyLine += Currency.CurrencyName() + Seperator;
		sCurrencyLine += to_string(Currency.Rate());

		return sCurrencyLine;
	}

	void _SaveCurrencyLineToFile(vector<clsCurrency> _vCurrenciesData)
	{ 
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out); // write mode


		if (MyFile.is_open())
		{
			string Line = "";
			
			for(clsCurrency& C1 : _vCurrenciesData)
			{
				Line = _ConvertCurrencyObjectToLine(C1);
				MyFile << Line << endl;
			}
			MyFile.close();
		}
	}

	void _UpdateRate()
	{
		vector<clsCurrency> _vCurrenciesData;
		_vCurrenciesData = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C1 : _vCurrenciesData)
		{
			if (C1.CurrencyCode() == CurrencyCode())
			{
				C1 = *this;
				break;
			}
		}

		_SaveCurrencyLineToFile(_vCurrenciesData);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enCurrencyMode::eEmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enCurrencyMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector<clsCurrency> GetAllCurrencies()
	{
		return _LoadCurrenciesDataFromFile();
	}

	string Country() const
	{
		return _Country;
	}

	string CurrencyCode() const
	{
		return _CurrencyCode;
	}

	string CurrencyName() const
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_UpdateRate();
	}

	float Rate() const
	{
		return _Rate;
	}

	bool IsEmpty() const
	{
		return (_Mode == enCurrencyMode::eEmptyMode);
	}
	enum enFindOptions { eFindByCode = 1, eFindByCountry = 2 };

	static clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string Line = "";

			while(getline(MyFile, Line))
			{
				clsCurrency C1 = _ConvertCurrencyLineToObject(Line);

				if (C1.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return C1;
				}
				
			}
			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string sLine = "";
			while (getline(MyFile, sLine))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(sLine);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());
	}
	
};

