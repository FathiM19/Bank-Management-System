#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsMoneyTransferScreen.h"
#include "clsTransfersLogScreen.h"

using namespace std;
class clsTransactionsMenueScreen : protected clsScreen
{

private:

	enum _enTransactionsMenue {
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3,
		eTransferFromTo = 4, eListTransferLogScreen = 5, eMainMenue = 6
	};

	static short _ReadTransactionsMenue()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]: ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen will be hier..." << endl;
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen will be hier..." << endl;
		clsWithdrawScreen::ShowWithdrawScreen();

	}

	static void _ShowTotalBalancesScreen()
	{
		//cout << "\nTotal Balances Screen will be hier..." << endl;
		clsTotalBalancesScreen::ShowTotalBalancesScreen();

	}

	static void _ShowTransferAmountScreen()
	{
		//cout << "\nTransfer Amount Screen will be hier..." << endl;
		clsMoneyTransferScreen::ShowMoneyTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransfersLogScreen::ShowTranfersLogScreen();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\tPress any key to go back to Transactions Menue...";
		system("pause>0");

		ShowTransactionsMenueScreen();
	}

	static void _PerformTransactionsMenue(_enTransactionsMenue TransactionsMenue)
	{
		switch(TransactionsMenue)
		{
		
		case _enTransactionsMenue::eDeposit:
		{
			system("cls"); //reset screen
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case _enTransactionsMenue::eWithdraw:
		{
			system("cls"); // reset screen
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case _enTransactionsMenue::eTotalBalances:
		{
			system("cls"); //reset screen
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		
		case _enTransactionsMenue::eTransferFromTo:
		{
			system("cls"); //reset screen
			_ShowTransferAmountScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		
		case _enTransactionsMenue::eListTransferLogScreen:
		{
			system("cls"); //reset screen
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case _enTransactionsMenue::eMainMenue:
		{

			//do nothing here the main screen will handle it :-) ;
		}
		}
	}

public:

	static void ShowTransactionsMenueScreen()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return; // this will exit the function and it will not continue
		}

		system("cls"); //reset screen
		_DrawScreenHeader("\t   Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t   Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(32) << left << "" << "\t[1] Deposit\n";
		cout << setw(32) << left << "" << "\t[2] Withdraw\n";
		cout << setw(32) << left << "" << "\t[3] Total Balances\n";
		cout << setw(32) << left << "" << "\t[4] Transfer\n";
		cout << setw(32) << left << "" << "\t[5] Transfer Log List.\n";
		cout << setw(32) << left << "" << "\t[6] Main Menue\n";
		cout << setw(37) << left << "" << "==========================================" << endl;

		_PerformTransactionsMenue((_enTransactionsMenue)_ReadTransactionsMenue());

	}
};

