#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;
    
    struct stTransferRegisterRecord; // Forward Declaration

    static stTransferRegisterRecord _ConvertTransferLogLineToRecord(string& TranferLogLine, string Seperator = "#//#")
    {
        vector<string> vTransferLogData;
        vTransferLogData = clsString::Split(TranferLogLine, Seperator);

        stTransferRegisterRecord TransferRecord;
        TransferRecord.DateTime = vTransferLogData[0];
        TransferRecord.SourceAccountNumber = vTransferLogData[1];
        TransferRecord.DestinationAccountNumber = vTransferLogData[2];
        TransferRecord.TransferAmount = stod(vTransferLogData[3]);
        TransferRecord.SourceBalanceAfterTransfer = stod(vTransferLogData[4]);
        TransferRecord.DestinationBalanceAfterTransfer = stod(vTransferLogData[5]);
        TransferRecord.PerformedByUserName = vTransferLogData[6];

        return TransferRecord;
    }

    string _PrepareTranferRecord(clsBankClient DestinationClient, float TransferAmount,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(TransferAmount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;

        return TransferLogRecord;
    }

    void _RegisterTransfer(clsBankClient DestinationClient, float TransferAmount, string UserName)
    {
        string sTransferRecord = _PrepareTranferRecord(DestinationClient, TransferAmount, UserName);

        fstream MyFile;
        MyFile.open("TransferRegister.txt", ios::out | ios::app); // append mode

        if (MyFile.is_open())
        {
            MyFile << sTransferRecord << endl;

            MyFile.close();
        }
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDelete() == false)
                {
                    //we only write records that are not marked for delete.
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);//append mode

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    bool _DeleteClient()
    {
        vector<clsBankClient> _vClientsData;
        _vClientsData = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClientsData)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClientsData);

        *this = _GetEmptyClientObject();

        return true;
    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    static clsBankClient _GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    struct stTransferRegisterRecord
    {
        string DateTime = "";
        string SourceAccountNumber = "";
        string DestinationAccountNumber = "";
        double TransferAmount = 0;
        double SourceBalanceAfterTransfer = 0;
        double DestinationBalanceAfterTransfer = 0;
        string PerformedByUserName = "";
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    // No UI Related code inside object.
    /*void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }

        }

    }

    bool Delete()
    {
        return _DeleteClient();
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetClientsTotalBalances()
    {
        vector <clsBankClient> vClients = GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient& Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
        }
        
        return TotalBalances;
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient AddNewClientObject(string AccountNumber)
    {
        return _GetAddNewClientObject(AccountNumber);
    }
    
    

    bool Deposit(float DepositAmount)
    {
        if (DepositAmount <= 0)
            return false;
        else
        {
            this->_AccountBalance += DepositAmount;
            Save();
            return true;
        }
    }

    bool Withdraw(float WithdrawAmount)
    {
        if (WithdrawAmount > GetAccountBalance() || WithdrawAmount <= 0)
            return false;
        else
        {
            _AccountBalance -= WithdrawAmount;
            Save();
            return true;
        }
    }

    bool Transfer(clsBankClient& DestinationClient, float TransferAmount, string UserName)
    {
        if (AccountNumber() == DestinationClient.AccountNumber())
            return false;

        if (!Withdraw(TransferAmount)) // Source Account
            return false;

        if (!DestinationClient.Deposit(TransferAmount))
        {
            Deposit(TransferAmount); // Rollback to Source Account
            return false;
        }

        _RegisterTransfer(DestinationClient, TransferAmount, UserName);
        return true;
        
    }

    static vector<stTransferRegisterRecord> GetTransfersLogList()
    {
        vector<stTransferRegisterRecord> vTrafersRegisterLine;

        fstream MyFile;
        MyFile.open("TransferRegister.txt", ios::in); // read mode

        if (MyFile.is_open())
        {
            string sLine = "";
            stTransferRegisterRecord TransferRegisterRecord;

            while (getline(MyFile, sLine))
            {
                TransferRegisterRecord = _ConvertTransferLogLineToRecord(sLine);
                vTrafersRegisterLine.push_back(TransferRegisterRecord);
            }

            MyFile.close();
        }

        return vTrafersRegisterLine;
    }



};