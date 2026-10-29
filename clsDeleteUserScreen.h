#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUsername    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");

		string UserName = "";

		cout << "\nEnter Client Username to Delete: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUsername is not exist. Enter another one to delete: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser UserToDelete = clsUser::Find(UserName);
		_PrintUser(UserToDelete);

		char Answer = clsInputValidate::ReadAnswer("\nAre you sure, you want to delete this user? [Y/N]: ");

		if (toupper(Answer) == 'Y')
		{
			if (UserToDelete.Delete())
			{
				cout << "\nUser Deleted successfully :-)" << endl;
				_PrintUser(UserToDelete);
			}
			else
				cout << "\nError! User is not deleted." << endl;
		}
		else
			cout << "\nOperation was cancelled." << endl;
	}

};

