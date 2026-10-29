#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"
using namespace std;

class clsMoneyTransferScreen : protected clsScreen
{

private:

	static string _ReadClientAccountNumber(string Message)
	{
		string AccountNumber = "";

		cout << "\n" << Message;
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(string Message)
	{
		double Amount = 0;
		cout << Message;
		Amount = clsInputValidate::ReadDblNumber();
		return Amount;
	}

	static bool _IsValidTransferAmount(clsBankClient Client, double TransferAmount)
	{
		if (TransferAmount > Client.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance. " << endl;
			return false;
		}

		if (TransferAmount <= 0)
		{
			cout << "\nInvalid! Transfer amount must be greater than 0." << endl;
			return false;
		}

		return true;
	}

	static bool _IsSameAccount(clsBankClient SourceClient, clsBankClient DestinationClient)
	{
		return (SourceClient.AccountNumber() == DestinationClient.AccountNumber());
	}

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n________________________\n";
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n________________________" << endl;
	}

public:

	static void ShowMoneyTransferScreen()
	{
		_DrawScreenHeader("\t   Money Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadClientAccountNumber("Please Enter Account Number to Transfer From: "));
		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadClientAccountNumber("Please Enter Account Number to Transfer To: "));
		_PrintClientCard(DestinationClient);

		if (_IsSameAccount(SourceClient, DestinationClient))
		{
			cout << "\nInvalid! You cannot transfer money to the same account." << endl;
			return; // this will exit the function and will not continue.
		}

		double TransferAmount = _ReadAmount("\nEnter Transfer Amount: ");

		while (!_IsValidTransferAmount(SourceClient, TransferAmount))
		{
			TransferAmount = _ReadAmount("\nEnter another Amount? ");
		};

		char Answer = 'N';
		Answer = clsInputValidate::ReadAnswer("\nAre you sure, that you want to transfer this amount? ");

		if (tolower(Answer) == 'y')
		{
			if (SourceClient.Transfer(DestinationClient, TransferAmount, CurrentUser.UserName))
			{
				cout << "\nAmount transferred successfully :-)\n";
				cout << "\nYour account balance is: " << SourceClient.GetAccountBalance() << endl;
			}
			else
				cout << "\nError! Transfer failed." << endl;
		}
		else
			cout << "\nOperation was cancelled." << endl;
		
		_PrintClientCard(SourceClient);
		_PrintClientCard(DestinationClient);
	}
};

