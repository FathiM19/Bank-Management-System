#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyCalculator : protected clsScreen

{
private:

	static clsCurrency _GetCurrency(string Message)
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

		return clsCurrency::FindByCode(CurrencyCode); 
	}

	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		return clsInputValidate::ReadFloatNumber();
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
	{
		cout << "\n" << Title;
		cout << "\n_______________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_______________________________\n" << endl;

	}

	static void _PrintCalculationResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom, "Convert From");

		float AmounInUSD = CurrencyFrom.ConvertToUSD(Amount);

		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() <<
		" = " << AmounInUSD << " USD" << endl;

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return; 
		}
		
		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(CurrencyTo, "To");

		float AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

		cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode() <<
			" = " << AmountInCurrency2 << " " << CurrencyTo.CurrencyCode() << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{

		float Amount = 0;
		char Continue = 'y';
		
		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls"); // reset screen
			_DrawScreenHeader("\t Currency Calculator Screen");

			clsCurrency SourceCurrency = _GetCurrency("Please Enter Currency1 Code: ");
			clsCurrency DestinationCurrency = _GetCurrency("Please Enter Currency2 Code: ");

			Amount = _ReadAmount();

			_PrintCalculationResults(Amount, SourceCurrency, DestinationCurrency);

			cout << "\nDo you want to perform another calculation? y/n? ";
			cin >> Continue;
		};
		

	}
};

