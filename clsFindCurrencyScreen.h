#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(const clsCurrency& Currency)
	{
		cout << "\n\tCurrency Info:";
		cout << "\n_______________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nExchange Rate : " << Currency.Rate();
		cout << "\n_______________________________\n" << endl;
	}

	static short _ReadFindOption()
	{
		cout << setw(37) << left << "" << "\nFind By: [1] Code or [2] Country ? ";
		return clsInputValidate::ReadShortNumberBetween(1, 2);
	}

	static string _ReadCurrencyBy(const string& Message)
	{
		string SearchValue = "";
		cout << "\n" << Message;
		SearchValue = clsInputValidate::ReadString();
		return SearchValue;
	}

	static clsCurrency FindCurrencyBy(clsCurrency::enFindOptions FindOption)
	{
		if (FindOption == clsCurrency::enFindOptions::eFindByCode) 
			return clsCurrency::FindByCode(_ReadCurrencyBy("Enter the currency code: "));
		else
			return clsCurrency::FindByCountry(_ReadCurrencyBy("Enter the country name: "));	
	}

	static void _ShowResult(const clsCurrency& Currency)
	{
		if (!Currency.IsEmpty())
		{
			_PrintCurrency(Currency);
			cout << endl;
		}
		else
			cout << clsUtil::GetColoredText(clsUtil::enColors::eRed, "\nCurrency was not found.") << endl;
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");

		clsCurrency Currency = FindCurrencyBy((clsCurrency::enFindOptions)_ReadFindOption());
		_ShowResult(Currency);

	}
};

