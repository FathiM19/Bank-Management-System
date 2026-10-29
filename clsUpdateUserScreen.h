#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{

private:
    static int _ReadUserPermissions()
    {
        int Permission = 0;
        char Answer = 'N';


        Answer = clsInputValidate::ReadAnswer("\nDo you want to give full access? y/n? ");
        if (tolower(Answer) == 'y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to :\n";

        Answer = clsInputValidate::ReadAnswer("\nShow Client List? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pListClients;

        Answer = clsInputValidate::ReadAnswer("\nAdd New Client? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pAddNewClient;

        Answer = clsInputValidate::ReadAnswer("\nDelete Client y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pDeleteClient;

        Answer = clsInputValidate::ReadAnswer("\nUpdate Client? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pUpdateClient;

        Answer = clsInputValidate::ReadAnswer("\nFind Client y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pFindClient;

        Answer = clsInputValidate::ReadAnswer("\nTransactions? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pTransactions;

        Answer = clsInputValidate::ReadAnswer("\nManage Users? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pManageUsers;
        
        Answer = clsInputValidate::ReadAnswer("\nLogin Register? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pLoginRegister;

        Answer = clsInputValidate::ReadAnswer("\nCurrency Exchange? y/n? ");
        if (tolower(Answer) == 'y')
            Permission += clsUser::enPermissions::pCurrencyExchange;


        return Permission;

    }

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permissions: ";
        User.Permissions = _ReadUserPermissions();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
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

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t   Update User Screen");

		string UserName = "";

		cout << "\nEnter Username to Update: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUsername with [" << UserName << "] is not exist.Enter another one to update: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser UserToUpdate = clsUser::Find(UserName);
        _PrintUser(UserToUpdate);

        char Answer = 'N';
        Answer = clsInputValidate::ReadAnswer("\nAre you sure you want to update this User? y/n? ");

        if (tolower(Answer) == 'y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(UserToUpdate);

            clsUser::enSaveResults SaveResult;
            SaveResult = UserToUpdate.Save();

            switch (SaveResult)
            {

            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)" << endl;
                _PrintUser(UserToUpdate);
                break;
            }

            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty" << endl;
                break;
            }

            }
        }
        else
            cout << "\nOperation was cancelled." << endl;
	}
};

