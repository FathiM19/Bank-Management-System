#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
using namespace std;

class clsListCurrenciesScreen : protected clsScreen
{
private:
	static void _PrintCurrencyLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << left << setw(28) << Currency.Country();
		cout << "| " << left << setw(10) << Currency.CurrencyCode();
		cout << "| " << left << setw(42) << Currency.CurrencyName();
		cout << "| " << left << setw(10) << Currency.Rate();
	}

public:

	static void ShowListCurrenciesScreen()
	{
		vector<clsCurrency> vCurrenciesData;
		vCurrenciesData = clsCurrency::GetAllCurrencies();

		string Title = "\tCurrencies List Screen";
		string SubTitle = "\t   (" + to_string(vCurrenciesData.size()) + ") currency.";
		
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(28) << "Country";
		cout << "| " << left << setw(10) << "Code";
		cout << "| " << left << setw(42) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vCurrenciesData.size() == 0)
			cout << "\t\t\t\t\tNo Currencies Available In The System!" << endl;
		else

			for (clsCurrency& Currency : vCurrenciesData)
			{
				_PrintCurrencyLine(Currency);
				cout << endl;
			}


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

