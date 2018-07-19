#include<iostream>
#include<stdlib.h>
#include<string>
#include <sstream>
#include <fstream>
#include<time.h>
#include "utils.h"
#include "datahandler.h"
#include "statementmanager.h"
#include "accountmanager.h"
using namespace std;

void createStatementFile(string acctNum){
    ofstream outfile;
    string fileName = RECORDS_DIR + acctNum + ".lst";
    outfile.open(fileName.data(), ios::out);
    if (outfile.is_open()){

    } else {
        cerr << "unable to open file";
        exit(1);
    }
    outfile.close();
}

AccountManager::AccountManager(){

}

void AccountManager::displayAccountCreation(){
    cout << TITLE_C_ACCOUNT << endl;
    cout << MSG_TYPE_IN << endl;
    acquireData();
}

void AccountManager::flushInfo(string name, string address, string acctNum, float balance, string pin){
    string filename = ACCT_FILE;
    ofstream outfile;
    outfile.open(filename.data(), ios::app);
    if (outfile.is_open()){
        outfile << endl;
        outfile << "*AcctInfo:" << endl;
        outfile << name + ";" << endl;
        outfile << address + ";" << endl;
        outfile << acctNum + ";" << endl;
        outfile << balance << ";" << endl;
        outfile << pin + ";" << endl;
    } else {
        cerr << "unable to open the file";
        exit(1);
    }
    outfile.close();
}

string AccountManager::generateAcctNumber(){
    srand(unsigned(time(0)));
    long random;
    string numStr = "";
    do {
        for (int i = 0; i < 12; i++){
            stringstream strstream;
            string strRand;
            random = rand() % 10;
            strstream << random;
            strstream >> strRand;
            numStr += strRand;
        }
    } while (checkSameAcctNum(numStr));
    return numStr;
}

void AccountManager::acquireData(){

    int addNewOrExisting = 0;

    cout << "1 - New Person" << endl;
    cout << "2 - Existing Person" << endl;
    cout << "Type number:";

    cin >> addNewOrExisting;

    if (addNewOrExisting == 1) {
        char firstName[100] = {0}, middleName[100] = {0}, lastName[100] = {0}, address[100];
        float amountDeposit;
        int acctType;

        do {
            cin.ignore();
            cout << "First Name: ";
            cin.getline(firstName, 100);
            cout << "Middle Name: ";
            cin.getline(middleName, 100);
            cout << "Last Name: ";
            cin.getline(lastName, 100);

            if (!checkForDuplicates(firstName, middleName, lastName)) break;
            else cout << "Account already exists! Press enter again." << endl;
        } while(1);
        cout << "Address: ";
        cin.getline(address, 100, '\n');
        cout << "1 - SAVINGS Account" << endl;
        cout << "2 - CURRENT Account" << endl;
        cout << "3 - PERSONAL Account" << endl;
        cout << "Select account type: ";
        cin >> acctType;
        cout << "Amount to Deposit: ";
        cin >> amountDeposit;

        string accountNumber = generateAcctNumber();
        string strPinNum = "";
        long random;
        for (int i = 0; i < 6; i++){
            stringstream strstream;
            string strRand;
            random = rand() % 10;
            strstream << random;
            strstream >> strRand;
            strPinNum += strRand;
        }

        string fullName = string(firstName) + " " + string(middleName) + " " + string(lastName);
        flushInfo(fullName, address, accountNumber, amountDeposit, strPinNum);
        createStatementFile(accountNumber);


        QSqlQuery query;

        query.clear();
        query.prepare("INSERT INTO personal_info (firstname, middlename, lastname, address) VALUES (:FIRSTNAME, :MIDDLENAME, "
                      ":LASTNAME, :ADDRESS)");
        query.bindValue(":FIRSTNAME", QString::fromStdString(firstName));
        query.bindValue(":MIDDLENAME", QString::fromStdString(middleName));
        query.bindValue(":LASTNAME", QString::fromStdString(lastName));
        query.bindValue(":ADDRESS", QString::fromStdString(address));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO user_account (personal_info_id, account_type_id, account_no, pin_num) VALUES ((SELECT idpersonal_info FROM "
                      "personal_info WHERE firstname=:FIRSTNAME AND middlename=:MIDDLENAME AND lastname=:LASTNAME AND address=:ADDRESS), :ACCT_TYPE, :ACCT_NO, :PIN_NO)");
        query.bindValue(":FIRSTNAME", QString::fromStdString(firstName));
        query.bindValue(":MIDDLENAME", QString::fromStdString(middleName));
        query.bindValue(":LASTNAME", QString::fromStdString(lastName));
        query.bindValue(":ADDRESS", QString::fromStdString(address));
        query.bindValue(":ACCT_TYPE", acctType);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.bindValue(":PIN_NO", QString::fromStdString(strPinNum));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO amount (currency, amount, accountno) VALUES (:CURRENCY, :AMOUNT, :ACCT_NO)");
        query.bindValue(":CURRENCY", "PHP");
        query.bindValue(":AMOUNT", amountDeposit);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO transaction (credit, debit, account_no, trans_post_id, datetime_post, recipient_num, trans_balance) VALUES (:CREDIT, 0, :ACCT_NO, 7, NOW(), '0', :BALANCE)");
        query.bindValue(":CREDIT", amountDeposit);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.bindValue(":BALANCE", amountDeposit);
        query.exec();

        cout << "Congratulations! You have successfully created an account." << endl;
        cout << "Your account number : " << accountNumber << endl;
        cout << "Your pin number : " << strPinNum << endl;
        cout << endl;
        cout << "---Type E To Exit---" << endl;

        setBHState(OUT);
        string proceed = "";
        do  {
            cin >> proceed;
        } while (!(proceed != "E" || proceed != "e"));
    }
    else if (addNewOrExisting = 2) {
        cout << "---New Bank Account for Existing User---" << endl;
        char firstName[100] = {0}, middleName[100] = {0}, lastName[100] = {0}, address[100];
        float amountDeposit;
        int acctType;

        cin.ignore();
        cout << "First Name: ";
        cin.getline(firstName, 100);
        cout << "Middle Name: ";
        cin.getline(middleName, 100);
        cout << "Last Name: ";
        cin.getline(lastName, 100);
        cout << "Address: ";
        cin.getline(address, 100, '\n');

        cout << "1 - SAVINGS Account" << endl;
        cout << "2 - CURRENT Account" << endl;
        cout << "3 - PERSONAL Account" << endl;
        cout << "Select account type: ";
        cin >> acctType;
        cout << "Amount to Deposit: ";
        cin >> amountDeposit;

        string accountNumber = generateAcctNumber();
        string strPinNum = "";
        long random;
        for (int i = 0; i < 6; i++){
            stringstream strstream;
            string strRand;
            random = rand() % 10;
            strstream << random;
            strstream >> strRand;
            strPinNum += strRand;
        }

        string fullName = string(firstName) + " " + string(middleName) + " " + string(lastName);
        flushInfo(fullName, address, accountNumber, amountDeposit, strPinNum);
        createStatementFile(accountNumber);



        QSqlQuery query;

        query.clear();
        query.prepare("INSERT INTO user_account (personal_info_id, account_type_id, account_no, pin_num) VALUES ((SELECT idpersonal_info FROM "
                      "personal_info WHERE firstname=:FIRSTNAME AND middlename=:MIDDLENAME AND lastname=:LASTNAME AND address=:ADDRESS), :ACCT_TYPE, :ACCT_NO, :PIN_NO)");
        query.bindValue(":FIRSTNAME", QString::fromStdString(firstName));
        query.bindValue(":MIDDLENAME", QString::fromStdString(middleName));
        query.bindValue(":LASTNAME", QString::fromStdString(lastName));
        query.bindValue(":ADDRESS", QString::fromStdString(address));
        query.bindValue(":ACCT_TYPE", acctType);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.bindValue(":PIN_NO", QString::fromStdString(strPinNum));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO amount (currency, amount, accountno) VALUES (:CURRENCY, :AMOUNT, :ACCT_NO)");
        query.bindValue(":CURRENCY", "PHP");
        query.bindValue(":AMOUNT", amountDeposit);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.exec();

        query.clear();
        query.prepare("INSERT INTO transaction (credit, debit, account_no, trans_post_id, datetime_post, recipient_num, trans_balance) VALUES (:CREDIT, 0, :ACCT_NO, 7, NOW(), '0', :BALANCE)");
        query.bindValue(":CREDIT", amountDeposit);
        query.bindValue(":ACCT_NO", QString::fromStdString(accountNumber));
        query.bindValue(":BALANCE", amountDeposit);
        query.exec();

        cout << "Congratulations! You have successfully created an account." << endl;
        cout << "Your account number : " << accountNumber << endl;
        cout << "Your pin number : " << strPinNum << endl;
        cout << endl;
        cout << "---Type E To Exit---" << endl;

        setBHState(OUT);
        string proceed = "";
        do  {
            cin >> proceed;
        } while (!(proceed != "E" || proceed != "e"));
    }


}

bool AccountManager::checkForDuplicates(string firstName, string middleName, string lastName){
    return checkSameName(firstName + " " + middleName + " " + lastName);
}

