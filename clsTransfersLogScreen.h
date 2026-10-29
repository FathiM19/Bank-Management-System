#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h";
#include "clsUtil.h"
using namespace std;
class clsTransfersLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogInfo(clsBankClient::stTransferRegisterRecord TransferRegisterRecord)
	{
		cout << setw(4) << left << "" << "| " << left << setw(18) << TransferRegisterRecord.DateTime;
		cout << "| " << left << setw(13) << TransferRegisterRecord.SourceAccountNumber;
		cout << "| " << left << setw(13) << TransferRegisterRecord.DestinationAccountNumber;
		cout << "| " << left << setw(10) << TransferRegisterRecord.TransferAmount;
		cout << "| " << left << setw(18) << TransferRegisterRecord.SourceBalanceAfterTransfer;
		cout << "| " << left << setw(18) << TransferRegisterRecord.DestinationBalanceAfterTransfer;
		cout << "| " << left << setw(10) << clsUtil::GetColoredText(clsUtil::enColors::eBlue, TransferRegisterRecord.PerformedByUserName);
	}

public:

	static void ShowTranfersLogScreen()
	{
		vector<clsBankClient::stTransferRegisterRecord> vTranferLogData = clsBankClient::GetTransfersLogList();

		string Title = "\t List Transfers Log Screen";
		string SubTitle = "\t    (" + to_string(vTranferLogData.size()) + ") Tranfer(s).";

		_DrawScreenHeader(Title, SubTitle);

		
		cout << "\n" << setw(4) << left << "" << 
			clsUtil::GetColoredText(clsUtil::enColors::eCyan, "_______________________________________________________");
		cout << clsUtil::GetColoredText(clsUtil::enColors::eYellow, "_______________________________________________________\n") << endl;

		cout << setw(4) << left << "" << "| " << left << setw(18) << "Date/Time"; 
		cout << "| " << left << setw(13) << "Source Acc";
		cout << "| " << left << setw(13) << "Destin Acc";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(18) << "Sour. Balance";
		cout << "| " << left << setw(18) << "Dest. Balance";
		cout << "| " << left << setw(10) << "User";
		
		cout << "\n" << setw(4) << left << "" <<
			clsUtil::GetColoredText(clsUtil::enColors::eCyan, "_______________________________________________________");
		cout << clsUtil::GetColoredText(clsUtil::enColors::eYellow, "_______________________________________________________\n") << endl;


		if (vTranferLogData.size() == 0)
			cout << "\n\t\t\t\t\tNo Available Tranfer Log In The System!" << endl;
		else
			for (clsBankClient::stTransferRegisterRecord& sTransfer : vTranferLogData)
			{
				_PrintTransferLogInfo(sTransfer);
				cout << endl;
			}
			

		cout << "\n" << setw(4) << left << "" <<
			clsUtil::GetColoredText(clsUtil::enColors::eCyan, "_______________________________________________________");
		cout << clsUtil::GetColoredText(clsUtil::enColors::eYellow, "_______________________________________________________\n") << endl;


	}
};

