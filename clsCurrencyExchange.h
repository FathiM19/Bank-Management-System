#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsCurrency.h" 
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculator.h"

using namespace std;
class clsCurrencyExchange : protected clsScreen
{
private:
	enum _enPerformExchangeMenue {
		eListCurrenies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenue = 5
	};

	static short _ReadExchangeMenue()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choose = clsInputValidate::ReadShortNumberBetween(1, 5);
		return Choose;
	}

	static void _ShowCurrenciesList()
	{
		//cout << "\nCurrencies List Screen will be hier...";
		clsListCurrenciesScreen::ShowListCurrenciesScreen();

	}
	
	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen will be hier...";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();

	}
	
	static void _ShowUpdateRateScreen()
	{
		//cout << "\nUpdate Rate Screen will be hier...";
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}
	
	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen will be hier...";
		clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrencyExchangeMenue()
	{
		cout << setw(37) << left << "\n\n\tPress any key to go back to Exchange Menue..." << endl;
		system("pause>0");

		ShowCurrencyExchangeMainMenue();
	}

	static void _PerformExchangeMainMenue(_enPerformExchangeMenue PerformExchangeMenue)
	{
		switch (PerformExchangeMenue)
		{
		case _enPerformExchangeMenue::eListCurrenies:
		{
			system("cls"); // reset screen
			_ShowCurrenciesList();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		
		case _enPerformExchangeMenue::eFindCurrency:
		{
			system("cls"); // reset screen
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		
		case _enPerformExchangeMenue::eUpdateRate:
		{
			system("cls"); // reset screen
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		
		case _enPerformExchangeMenue::eCurrencyCalculator:
		{
			system("cls"); // reset screen
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		
		case _enPerformExchangeMenue::eMainMenue:
		{
			// do nothing hier main menue will handle it :-)
			break;
		}
		}
	}

public:

	static void ShowCurrencyExchangeMainMenue()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
		{
			return; // this will exit the function and it will not continue
		}

		system("cls"); // reset screen
		_DrawScreenHeader("\tCurrency Exchange Main Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformExchangeMainMenue((_enPerformExchangeMenue)_ReadExchangeMenue());
	}
};

