#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include <iomanip>
using namespace std;

class clsClientsListScreen : protected clsScreen
{

protected:

    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ") << left << setw(15) << Client.AccountNumber();
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ") << left << setw(20) << Client.FullName();
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ") << left << setw(12) << Client.Phone;
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ") << left << setw(20) << Client.Email;
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ") << left << setw(10) << Client.PinCode;
        cout << clsUtil::GetColoredText(clsUtil::eCyan, "| ");
        cout << clsUtil::GetColoredText(clsUtil::eGreen, "$ ") << left << setw(12) << to_string(Client.AccountBalance);
    }

public:

    static void ShowClientsList()
    {

        if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return; // this will exit the function and it will not continue 
        }

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Client List Screen";
        string SubTitle = "\t    " + to_string(vClients.size()) + " Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        string CyanColor = clsUtil::GetColoredText(clsUtil::eCyan, "| ");

        cout << clsUtil::GetColoredText(clsUtil::eYellow, "\n_______________________________________________________");
        cout << clsUtil::GetColoredText(clsUtil::eYellow, "_________________________________________\n\n");

        cout << CyanColor << left << setw(15) << "Account Number";
        cout << CyanColor << left << setw(20) << "Client Name";
        cout << CyanColor << left << setw(12) << "Phone";
        cout << CyanColor << left << setw(20) << "Email";
        cout << CyanColor << left << setw(10) << "Pin Code";
        cout << CyanColor << left << setw(12) << "Balance";

        cout << clsUtil::GetColoredText(clsUtil::eYellow, "\n_______________________________________________________");
        cout << clsUtil::GetColoredText(clsUtil::eYellow, "_________________________________________\n") << endl;

        if (vClients.size() == 0)
            cout << "\n\t\t\t\tNo Clients Available In The System!" << endl;
        else

            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
                cout << endl;
            }


        cout << clsUtil::GetColoredText(clsUtil::enColors::eYellow, "\n_______________________________________________________");
        cout << clsUtil::GetColoredText(clsUtil::enColors::eYellow, "_________________________________________\n") << endl;
    }

};

