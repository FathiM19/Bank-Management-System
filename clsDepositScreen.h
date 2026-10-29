#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsDepositScreen : protected clsScreen
{

private:

	static double _ReadDepositAmount()
	{
		double DepositAmount = 0;

		cout << "Enter Amount that you want to deposit: ";
		DepositAmount = clsInputValidate::ReadDblNumber();
		while (DepositAmount <= 0)
		{
			cout << "\nInvalid Amount. Enter a valid amount: ";
			DepositAmount = clsInputValidate::ReadDblNumber();
		}

		return DepositAmount;
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t  Deposit Screen");

		string AccountNumber = "";

		cout << "\nEnter account number to deposit: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist. Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double DepositeAmount = _ReadDepositAmount();

		char Answer = 'N';
		Answer = clsInputValidate::ReadAnswer("\nAre you sure that you want to deposit this amount? [Y/N]? ");
		
		if (tolower(Answer) == 'y')
		{
			if (Client.Deposit(DepositeAmount))
			{
				cout << "\nAmount Deposit successfully :-)\n";
				cout << "\nYour amount is: " << Client.GetAccountBalance() << endl;
			}
			else
				cout << "\nError, amount could not be deposit." << endl;
		}
		else
			cout << "\nOperation was cancelled." << endl;

	}

};

