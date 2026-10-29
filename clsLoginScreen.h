#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;
 
class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short LoginFaildCount = 0;

		string UserName = "", Password = "";
		do
		{

			if (LoginFaild)
			{
				LoginFaildCount++;
				cout << "\nInvalid UserName/Password.";
				cout << "\nYou have [" << (3 - LoginFaildCount) << "] Trial(s) to login.\n" << endl;
			}

			if (LoginFaildCount == 3)
			{
				cout << "\n Your are Locked after 3 faild trails \n\n";
				return false;
			}

			cout << "\nEnter username: ";
			cin >> UserName;

			cout << "\nEnter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls"); //reset screen
		_DrawScreenHeader("\t    Login Screen");
		return _Login();
	}

};

