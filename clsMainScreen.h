#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>

#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenueScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchange.h"
#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueOptions {
		eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eShowTransactions = 6, eManageUser = 7, eLoginRegister = 8,
		eCurrencyExchange = 9, eExit = 10
	};

	static short _ReadMenuOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 10]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 10);
		return Choice;
	}
	
	static void _ShowClientsListScreen()
	{
		//cout << "Client List Screen will be hier...";
		clsClientsListScreen::ShowClientsList();

	}

	static void _ShowAddNewClientsScreen()
	{
		// cout << "\nAdd New Client Screnn will be hier...";
		clsAddNewClientScreen::ShowAddNewClientScreen();

	}

	static void _ShowDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen will be hier.";
		clsDeleteClientScreen::ShowDeleteClientScreen();

	}

	static void _ShowUpdateClientScreen()
	{
		//cout << "\nUpdate Client Screen will be hier.";
		clsUpdateClientScreen::ShowUpdateClientScreen();

	}

	static void _ShowFindClientScreen()
	{
		//cout << "\nFind Client Screen will be hier.";
		clsFindClientScreen::ShowFindClientScreen();

	}

	static void _ShowTransactionsMenueScreen()
	{
		//cout << "\nTransactions Menue Screen will be hier.";
		clsTransactionsMenueScreen::ShowTransactionsMenueScreen();
	
	}

	static void _ShowManageUserScreen()
	{
		//cout << "\nManage User Screen will be hier.";
		clsManageUsersScreen::ShowManageUsersMenue();

	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();

	}
	
	static void _ShowCurrencyExchangeMenueScreen()
	{
		//cout << "\nCurrencyCalculatorScreen will be hier..." << endl;
		clsCurrencyExchange::ShowCurrencyExchangeMainMenue();

	}

	/*static void _ShowEndScreen()
	{
		cout << "\nLogout screen will be hier...";
	}*/

	static void _Logout()
	{
		//CurrentUser = clsUser::Find("", "");
		CurrentUser.ClearObject();
		
		
		// then it will go back to main function :-)
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\n\tPress any key to go back to main menue...";
		
		system("pause>0");
		ShowMainMenue();
	}

	static void _PerformMainMenueOptions(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eShowClientsList:
		{
			system("cls"); //reset screen
			_ShowClientsListScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eAddNewClient:
		{
			system("cls"); // reset screen
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eDeleteClient:
		{
			system("cls"); //reset screen
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eUpdateClient:
		{
			system("cls"); // reset screen
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eFindClient:
		{
			system("cls"); // reset screen
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eShowTransactions:
		{
			system("cls"); // reset screen
			_ShowTransactionsMenueScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eManageUser:
		{
			system("cls"); // reset screen
			_ShowManageUserScreen();
			_GoBackToMainMenue();
			break;
		}
		
		case enMainMenueOptions::eLoginRegister:
		{
			system("cls"); // reset screen
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		}
		
		case enMainMenueOptions::eCurrencyExchange:
		{
			system("cls"); // reset screen
			_ShowCurrencyExchangeMenueScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eExit:
		{
			system("cls"); // reset screen
			_Logout();
			//_GoBackToMainMenue();
			break;
		}
		}
	}

public:

	static void ShowMainMenue()
	{
		system("cls"); // reset screen
		_DrawScreenHeader("\t\tMain Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Clients List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout\n";
		cout << setw(37) << left << "" << "===========================================" << endl;

		_PerformMainMenueOptions((enMainMenueOptions)_ReadMenuOptions());
	}
};

