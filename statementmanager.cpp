#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "datahandler.h"
#include "statementmanager.h"
#include "utils.h"
using namespace std;

//Must be run in a loop. Remember to close stream!
TransactionInfo getSingleTransInfos(ifstream &infile){
    TransactionInfo transInfoData;

    infile.ignore(1000, ':');
    char name[100];
    infile.ignore(1000, '\n');
    infile.get(name, 100, ';');
    transInfoData.name = name;

    infile.ignore(1000, ';');
    char credited[100];
    infile.ignore(1000, '\n');
    infile.get(credited, 100, ';');
    transInfoData.amountCredited = strtof(credited, NULL);

    infile.ignore(1000, ';');
    char debited[100];
    infile.ignore(1000, '\n');
    infile.get(debited, 100, ';');
    transInfoData.amountDebited = strtof(debited, NULL);

    infile.ignore(1000, ';');
    char dateOfTrans[100];
    infile.ignore(1000, '\n');
    infile.get(dateOfTrans, 100, ';');
    transInfoData.dateOfTrans = dateOfTrans;

    infile.ignore(1000, ';');
    char remarks[100];
    infile.ignore(1000, '\n');
    infile.get(remarks, 100, ';');
    transInfoData.remarks = remarks;

    return transInfoData;
}

StatementManager::StatementManager(){

}

void StatementManager::createStatementFile(string acctNum){
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

void StatementManager::addTransactionInfo(string acctNum, TransactionInfo transInfo){
    ofstream outfile;
    string fileName = RECORDS_DIR + acctNum + ".lst";
    outfile.open(fileName.data(), ios::app);
    if (outfile.is_open()){
        ostringstream credited;
        ostringstream debited;
        credited << transInfo.amountCredited;
        debited << transInfo.amountDebited;
        string info =
                string("\n") +
                string("*TransInfo:\n") +
                transInfo.name + string(";\n") +
                credited.str() + string(";\n") +
                debited.str() + string(";\n") +
                getCurrentTime() + string(";\n") +
                transInfo.remarks + string(";\n");
        outfile << info;
    } else {
        cerr << "unable to open file";
        exit(1);
    }
    outfile.close();
}

void StatementManager::printBankStatement(string acctNum){
    string exitStr = "";
    string fileName = RECORDS_DIR + acctNum + ".lst";
    AcctInfo acctInfo = getMatchedAccount(acctNum);
    cout << fixed << setprecision(2);
    cout << "\t\t\t----------TYBANK----------" << endl;
    cout << "\t\t\t      BANK STATEMENT" << endl;
    cout << endl;
    cout << "Name : " << acctInfo.name << endl;
    cout << "Address : " << acctInfo.address<< endl;
    cout << "Balance : P " << acctInfo.balance << endl;
    cout << "Account Number : " << acctInfo.acctNum << endl;
    cout << endl;
    cout << "\t\t\t-----List of Transactions-----" << endl;

    cout << left
         << setw(20) << "Transaction Name"
         << setw(15) << "Credits(P)"
         << setw(15) << "Debits(P)"
         << setw(15) << "Date"
         << setw(5) << "Remarks"
         << endl;
    ifstream infile;
    infile.open(fileName.data(), ios::in);
    if (infile.is_open()){
        while (1){
            TransactionInfo transInfos = getSingleTransInfos(infile);
            if (transInfos.name != "")
                cout << left
                     << setw(20) << transInfos.name
                     << setw(15) << transInfos.amountCredited
                     << setw(15) << transInfos.amountDebited
                     << setw(15) << transInfos.dateOfTrans
                     << setw(5) << transInfos.remarks
                     << endl;
            if (infile.eof()) break;
        }
    }
    else {
        exit(1);
    }
    infile.close();

    cout << endl;
    cout << endl;
    do {
        cout << "Type E to exit."<< endl;
        cin >> exitStr;
        if (exitStr == "E" || exitStr == "e") break;
        cout << ERR_MSG_INPUT << endl;
    } while (1);
}

void StatementManager::acquireBankStatement(){
    AcctInfo acctInfo;
    string acctNumber;
    cout << TITLE_B_STATEMENT << endl;
    cout << MSG_TYPE_IN << endl;
    do {
        cout << endl;
        cout << "Account Number: ";
        cin >> acctNumber;
        acctInfo = getMatchedAccount(acctNumber);
        if (acctInfo.name == "") cout << "Invalid Account Number!";
        else break;
    } while (1);
    clearScreen();
    printBankStatement(acctNumber);
    clearScreen();
    setBHState(OUT);
}

