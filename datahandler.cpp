#include<iostream>
#include<fstream>
#include<cstdlib>
#include <sstream>
#include<string>
#include <iomanip>
#include "datahandler.h"
using namespace std;

DataHandler::DataHandler()
{

}

//Must be run in a loop. Remember to close stream!
AcctInfo DataHandler::getSingleInfos(ifstream &infile){
    AcctInfo acctInfoData;

    infile.ignore(1000, ':');
    char name[100];
    infile.ignore(1000, '\n');
    infile.get(name, 100, ';');
    acctInfoData.name = name;

    infile.ignore(1000, ';');
    char address[100];
    infile.ignore(1000, '\n');
    infile.get(address, 100, ';');
    acctInfoData.address = address;

    infile.ignore(1000, ';');
    char acctNum[100];
    infile.ignore(1000, '\n');
    infile.get(acctNum, 100, ';');
    acctInfoData.acctNum = acctNum;

    infile.ignore(1000, ';');
    char balance[100];
    infile.ignore(1000, '\n');
    infile.get(balance, 100, ';');
    acctInfoData.balance = strtof(balance, NULL);

    infile.ignore(1000, ';');
    char pin[100];
    infile.ignore(1000, '\n');
    infile.get(pin, 100, ';');
    acctInfoData.pin = pin;

    return acctInfoData;
}

AcctInfo DataHandler::getMatchedAccount(string acctNumber){
    AcctInfo acctInfo;
    acctInfo.name == "";
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            AcctInfo infoExtracted = getSingleInfos(infile);
            if (infoExtracted.acctNum == acctNumber){

                QSqlQuery query;
                query.clear();
                query.exec("SELECT amount FROM amount WHERE accountno='" + QString::fromStdString(acctNumber) + "'");
                while (query.next()) {
                    infoExtracted.balance = query.value(0).toFloat();
                    acctInfo.balance = query.value(0).toFloat();
                }

                acctInfo = infoExtracted;
                break;
            }
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return acctInfo;
}


bool fileExists(string name){
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

void createFile(string filename){
    ofstream ofs;
    ofs.open(filename.data(), std::ofstream::out);
    ofs.close();
}

bool DataHandler::checkSameName(string name){
    string filename = ACCT_FILE;
    if (!fileExists(filename)) createFile(filename);
    bool sameName = false;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            AcctInfo infoExtracted = getSingleInfos(infile);
            if (infoExtracted.name == name){
                sameName = true;
                break;
            }
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return sameName;
}

bool DataHandler::checkSameAcctNum(string acctNum){
    bool sameAcctNum = false;
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            AcctInfo infoExtracted = getSingleInfos(infile);
            if (infoExtracted.acctNum == acctNum){
                sameAcctNum = true;
                break;
            }
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return sameAcctNum;
}

void DataHandler::getFileInfo(){
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        //        infile >> customer.firstName >> customer.middleInitial >> customer.lastName >> customer.accountNumber >> customer.balance;
        AcctInfo infoExtracted = getSingleInfos(infile);
        cout << infoExtracted.pin << endl;
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();
}

int DataHandler::getTotalAccounts(){
    int totalAccounts = 0;
    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        while (1){
            getSingleInfos(infile);
            if (infile.eof()) break;
            totalAccounts++;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    return totalAccounts;
}

void clearFileContents(string filename){
    ofstream ofs;
    ofs.open(filename.data(), std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void writeStringToFile(string filename, string data){
    ofstream outfile;
    outfile.open(filename.data(), ios::app);
    if (outfile.is_open()){
        outfile << data;
    } else {
        cerr << "unable to open file";
        exit(1);
    }
    outfile.close();
}

void DataHandler::setBalance(string acctNum, float bal){
    int totalAccts = getTotalAccounts();
    string accountInfos[totalAccts];

    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        for (int i = 0; i < totalAccts; i++){
            AcctInfo infoExtracted = getSingleInfos(infile);
            ostringstream strs;
            if (infoExtracted.acctNum == acctNum){
                infoExtracted.balance = bal;
            }
            strs << infoExtracted.balance;
            string strBal = strs.str();
            string accountInfo =
                    string("\n") +
                    string("*AcctInfo:\n") +
                    infoExtracted.name + string(";\n") +
                    infoExtracted.address + string(";\n") +
                    infoExtracted.acctNum + string(";\n") +
                    strBal + string(";\n") +
                    infoExtracted.pin + string(";\n");
            accountInfos[i] = accountInfo;
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    clearFileContents(filename);
    for (int i = 0; i < totalAccts; i++){
        writeStringToFile(filename, accountInfos[i]);
    }
}

void DataHandler::setPin(string acctNum, string pin){
    int totalAccts = getTotalAccounts();
    string accountInfos[totalAccts];

    string filename = ACCT_FILE;
    ifstream infile;
    infile.open(filename.data(), ios::in);
    if (infile.is_open()){
        for (int i = 0; i < totalAccts; i++){
            AcctInfo infoExtracted = getSingleInfos(infile);
            ostringstream strs;
            if (infoExtracted.acctNum == acctNum){
                infoExtracted.pin = pin;
            }
            strs << infoExtracted.balance;
            string strBal = strs.str();
            string accountInfo =
                    string("\n") +
                    string("*AcctInfo:\n") +
                    infoExtracted.name + string(";\n") +
                    infoExtracted.address + string(";\n") +
                    infoExtracted.acctNum + string(";\n") +
                    strBal + string(";\n") +
                    infoExtracted.pin + string(";\n");
            accountInfos[i] = accountInfo;
            if (infile.eof()) break;
        }
    }
    else {
        cerr << "unable to open file";
        exit(1);
    }
    infile.close();

    clearFileContents(filename);
    for (int i = 0; i < totalAccts; i++){
        writeStringToFile(filename, accountInfos[i]);
    }
}
