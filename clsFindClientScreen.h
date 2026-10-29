#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{

protected:

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

	static void ShowFindClientScreen()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return; // this will exit the function and it will not continue
		};

		_DrawScreenHeader("\t   Find Client Screen");

		string AccountNumber = "";

		cout << "\nEnter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose anthor one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
	}
};

