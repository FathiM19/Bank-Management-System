#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    struct stLoginRegisterRecord;   // Forward Declaration
    
    string _PrepareLogInRecord(string Seperator = "#//#")
    {

        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += UserName + Seperator;
        //here we encrypt store the encrypted Password not the real one.
        LoginRecord += clsUtil::EncryptText(Password) + Seperator;
        LoginRecord += to_string(Permissions);

        return LoginRecord;

    }

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string LoginRegisterLine, string Separator = "#//#")
    {
        vector<string> vLoginRegisterData;
        vLoginRegisterData = clsString::Split(LoginRegisterLine, Separator);

        stLoginRegisterRecord LoginRegisterRecord;
        LoginRegisterRecord.DateTime = vLoginRegisterData[0];
        LoginRegisterRecord.UserName = vLoginRegisterData[1];
        LoginRegisterRecord.Password = vLoginRegisterData[2];
        LoginRegisterRecord.Permissions = stoi(vLoginRegisterData[3]);

        return LoginRegisterRecord;
    }


    static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string stUserRecord = "";
        stUserRecord += User.FirstName + Seperator;
        stUserRecord += User.LastName + Seperator;
        stUserRecord += User.Email + Seperator;
        stUserRecord += User.Phone + Seperator;
        stUserRecord += User.UserName + Seperator;
        //here we encrypt store the encrypted Password not the real one.
        stUserRecord += clsUtil::EncryptText(User.Password) + Seperator;
        stUserRecord += to_string(User.Permissions);

        return stUserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line = "";


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLineToUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUserDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine = "";

        if (MyFile.is_open())
        {

            for (clsUser& U : vUsers)
            {
                if (U.MarkedForDelete() == false)
                {
                    //we only write records that are not marked for delete.
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);//append mode

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    bool _DeleteUser()
    {
        vector<clsUser> _vUsersData;
        _vUsersData = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsersData)
        {
            if (U.GetUserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUserDataToFile(_vUsersData);

        *this = _GetEmptyUserObject();

        return true;
    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.GetUserName() == GetUserName())
            {
                U = *this;
                break;
            }

        }

        _SaveUserDataToFile(_vUsers);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    static clsUser _GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions {
        pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, 
        pLoginRegister = 128, pCurrencyExchange = 256
    };

    struct stLoginRegisterRecord
    {
        string DateTime = "";
        string UserName = "";
        string Password = "";
        int Permissions = 0;
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;

    }


    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    int GetPermissions()
    {
        return _Permissions;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;

    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {


        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.GetUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {



        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                
                if (User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };
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
            if (clsUser::IsUserExist(_UserName))
            {
                return svFaildUserNameExists;
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
        return _DeleteUser();
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    
    static bool IsUserExist(string UserName)
    {

        clsUser Client1 = clsUser::Find(UserName);
        return (!Client1.IsEmpty());
    }

    static clsUser AddNewUserObject(string UserName)
    {
        return _GetAddNewUserObject(UserName);
    }


    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::pAll)
            return true;

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;
    }

    
    void ClearObject()
    {
        *this = _GetEmptyUserObject();
    }

    void RegisterLogIn()
    {
        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);//append mode

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> _vLoginRegisterData;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in); // read mode

        if (MyFile.is_open())
        {
            string DataLine = "";
            stLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, DataLine))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(DataLine);

                _vLoginRegisterData.push_back(LoginRegisterRecord);

            }

            MyFile.close();
        }

        return _vLoginRegisterData;
    }
};

