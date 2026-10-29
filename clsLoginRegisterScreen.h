#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterData(clsUser::stLoginRegisterRecord LoginRegisterLine)
	{
		cout << setw(8) << left << "" << "| " << left << setw(35) << LoginRegisterLine.DateTime;
		cout << "| " << left << setw(20) << LoginRegisterLine.UserName;
		cout << "| " << left << setw(20) << LoginRegisterLine.Password;
		cout << "| " << left << setw(10) << LoginRegisterLine.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{

		if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return; // this will exit the function and will not continue.
		}

		vector<clsUser::stLoginRegisterRecord> vRegisterDate = clsUser::GetLoginRegisterList();
		
		string Title = "\tLoggin Register List Screen";
		string SubTitle = "\t    (" + to_string(vRegisterDate.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "User Name";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vRegisterDate.size() == 0)
			cout << "\n\t\t\t\tNo Available Register In The System.";
		else
			for (clsUser::stLoginRegisterRecord& RegisterRecord : vRegisterDate)
			{
				_PrintLoginRegisterData(RegisterRecord);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

