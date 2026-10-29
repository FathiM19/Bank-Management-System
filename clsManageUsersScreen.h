#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsAddNewUserScreen.h"
#include "clsListUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:
	enum _enManageUsersMenueOptions {
		eShowUsersList = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFind = 5, eMainMenue = 6
	};

	static short _ReadUsersMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 - 6]? ";
		short Choose = clsInputValidate::ReadShortNumberBetween(1, 6);
		return Choose;
	}

	static void _ShowUsersListScreen()
	{
		//cout << "\nUsers List Screen will be hier...";
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen will be hier...";
		clsAddNewUserScreen::ShowAddNewUserScreen();



	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\nDelete User Screen will be hier...";
		clsDeleteUserScreen::ShowDeleteUserScreen();

	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "\nUpdate User Screen will be hier...";
		clsUpdateUserScreen::ShowUpdateUserScreen();

	}
	
	static void _ShowFindUserScreen()
	{
		//cout << "\nFind User Screen will be hier...";
		clsFindUserScreen::ShowFindUserScreen();

	}

	static void _GoBackToUsersMenue()
	{
		cout << "\n\n\tPress any key to go back to Users Menue...\n" << endl;
		system("pause>0");

		ShowManageUsersMenue();
	}

	static void _PerformManageUsersMenueOptions(_enManageUsersMenueOptions enUsersMenueOptions)
	{
		switch (enUsersMenueOptions)
		{
		case _enManageUsersMenueOptions::eShowUsersList:
		{
			system("cls"); // reset screen
			_ShowUsersListScreen();
			_GoBackToUsersMenue();
			break;
		}

		case _enManageUsersMenueOptions::eAddNewUser:
		{
			system("cls"); // reset screen
			_ShowAddNewUserScreen();
			_GoBackToUsersMenue();
			break;
		}

		case _enManageUsersMenueOptions::eDeleteUser:
		{
			system("cls"); // reset screen
			_ShowDeleteUserScreen();
			_GoBackToUsersMenue();
			break;
		}
		
		case _enManageUsersMenueOptions::eUpdateUser:
		{
			system("cls"); // reset screen
			_ShowUpdateUserScreen();
			_GoBackToUsersMenue();
			break;
		}
		
		case _enManageUsersMenueOptions::eFind:
		{
			system("cls"); // reset screen
			_ShowFindUserScreen();
			_GoBackToUsersMenue();
			break;
		}
		
		case _enManageUsersMenueOptions::eMainMenue:
		{
			
			//do nothing here the main screen will handle it :-) ;

		}
		}
	}

public:

	static void ShowManageUsersMenue()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return; // this will exit the function and it will not continue
		}


		system("cls"); // reset screen
		_DrawScreenHeader("\t  Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Users List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue\n";
		cout << setw(37) << left << "" << "===========================================" << endl;

		_PerformManageUsersMenueOptions((_enManageUsersMenueOptions)_ReadUsersMenueOptions());
	}
};

