#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
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

    static void _PrintUser(clsUser Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nUsername    : " << Client.GetUserName();
        cout << "\nPassword    : " << Client.GetPassword();
        cout << "\nPermissions : " << Client.GetPermissions();
        cout << "\n___________________\n";

    }

    

public:

	static void ShowAddNewUserScreen()
	{
        _DrawScreenHeader("\t   Add New User Screen");

        string UserName = "";

        cout << "\nEnter New Username: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUsername Is Already Used, Choose anther one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::AddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult)
        {

        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nClient Added Successfully :-)" << endl;
            _PrintUser(NewUser);
            break;
        }

        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nEmpty Object could not be saved." << endl;
            break;
        }
        }
	}
};

