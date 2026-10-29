#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
using namespace std;

class clsUpdateRateScreen : protected clsScreen
{
protected:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n\tCurrency Info:";
		cout << "\n_______________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nRate          : " << Currency.Rate();
		cout << "\n_______________________________\n" << endl;
	}

	static string ReadCurrencyCode(string Message)
	{
		string CurrencyCode = "";

		cout << "\n" << Message;
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency code ["
				<< clsUtil::GetColoredText(clsUtil::enColors::eCyan, CurrencyCode)
				<< "] does not exist. Enter another code: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		return CurrencyCode;
	}

	static float _ReadNewRate()
	{
		cout << "\nEnter the new exchange rate: ";
		return clsInputValidate::ReadFloatNumber();
	}

public:

	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\t Update Currency Rate Screen");

		string CurrencyCode = ReadCurrencyCode("Enter the currency Code: ");

		clsCurrency RateToUpdate = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(RateToUpdate);

		float NewRate = _ReadNewRate();

		char Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to update the Rate? y/n? ");

		if (tolower(Answer) == 'y')
		{
			cout << "\nExchange rate updated successfully." << endl;
			RateToUpdate.UpdateRate(NewRate);
			cout << "\nNew Rate Info:" << endl;
			_PrintCurrency(RateToUpdate);
		}
		else
			cout << "\nOperation was cancelled" << endl;
			
	}
};

