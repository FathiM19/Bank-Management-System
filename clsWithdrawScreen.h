#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsWithdrawScreen : protected clsScreen
{

private:

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nEnter account number to withdraw: ";
		AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}

	static double _ReadWithdrawAmount()
	{
		double WithdrawAmount = 0;

		cout << "\nPlease enter Withdraw amount? ";
		WithdrawAmount = clsInputValidate::ReadDblNumber();
		while (WithdrawAmount <= 0)
		{
			cout << "\nInvalid Amount. Enter a valid amount: ";
			WithdrawAmount = clsInputValidate::ReadDblNumber();
		}

		return WithdrawAmount;
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.GetPinCode();
		cout << "\nBalance     : " << Client.GetAccountBalance();
		cout << "\n___________________\n";

	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen"); 
		
		string AccountNumber = _ReadAccountNumber();
		
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist. Enter another one: ";
			AccountNumber = _ReadAccountNumber();
		};

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double WithdrawAmount = _ReadWithdrawAmount();

		char Answer = 'N';
		Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to perform this transction? [Y/N]? ");

		if (tolower(Answer) == 'y')
		{
			if (Client.Withdraw(WithdrawAmount))
			{
				cout << "\nAmount Withdrawed successfully :-)\n";
				cout << "\nYour amount is: " << Client.GetAccountBalance() << endl;
			}
			else
			{
				cout << "\nError! Amount cannot be withdrawn. Insufficient balance.";
				cout << "\nAmount to Withdraw is: " << WithdrawAmount;
				cout << "\nYour Balance is: " << Client.GetAccountBalance() << endl;
			}
		}
		else
			cout << "\nOperation was cancelled." << endl;

	}
};

