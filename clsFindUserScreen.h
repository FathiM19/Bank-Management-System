#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
protected:

	static void _PrintUser(clsUser User)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUsername    : " << User.GetUserName();
		cout << "\nPassword    : " << User.GetPassword();
		cout << "\nPermissions : " << User.GetPermissions();
		cout << "\n___________________\n";

	}

public:

	static void ShowFindUserScreen()
	{

		_DrawScreenHeader("\t   Find User Screen");

		string UserName = "";

		cout << "\nEnter Username: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUsername with [" << UserName << "] is not found, choose anthor one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
	}
};

