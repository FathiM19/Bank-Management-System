#pragma once
#include <iostream>
#include "clsScreen.h"
#include <string>
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{

private:

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

	static void ShowDeleteClientScreen()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return; // this will exit the function and it will not continue
		}

		_DrawScreenHeader("\t   Delete Client Screen");

		string AccountNumber = "";

		cout << "\nEnter Client Account Number to Delete: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not exist. Enter another one to delete: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientToDelete = clsBankClient::Find(AccountNumber);
		_PrintClient(ClientToDelete);

		char Answer = clsInputValidate::ReadAnswer("Are you sure, you want to delete this client? [Y/N]: ");

		if (toupper(Answer) == 'Y')
		{
			if (ClientToDelete.Delete())
			{
				cout << "\nClient Deleted successfully :-)" << endl;
				_PrintClient(ClientToDelete);
			}
			else
				cout << "\nError! Client is not deleted." << endl;
		}
		else
			cout << "\nOperation was cancelled." << endl;
	}
};

