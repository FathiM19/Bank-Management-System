#pragma once
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;
class clsTotalBalancesScreen :protected clsScreen
{

private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(18) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(40) << Client.FullName();
        cout << "| " << left << setw(12) << to_string(Client.AccountBalance);
    }

public:

	static void ShowTotalBalancesScreen()
	{

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(18) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalances = clsBankClient::GetClientsTotalBalances();

        if (vClients.size() == 0)
            cout << "\n\t\t\t\t\t" << "No Available Clients In The System!" << endl;
        else

            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }


        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << "\n" << clsUtil::Tabs(5) << "Total Balances = " << TotalBalances;
        cout << "\n" << clsUtil::Tabs(5) << "( " << clsUtil::NumberToText(TotalBalances) << " )" << endl;

	}
};

