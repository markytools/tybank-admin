#include "mastercardapplication.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "datahandler.h"
#include "utils.h"
using namespace std;

//Run in for loop!
MastercardInfo MastercardApplication::getSingleMCInfo(ifstream &infile)
{
    MastercardInfo mcInfo;

    string lineInfo;
    getline(infile >> ws, lineInfo);
    if (!stringIsEmptyOrHasOnlyWS(lineInfo)){

        string acctNum = substringAtPos(lineInfo.substr(0, 20), 0, ' ');
        string cardNum = substringAtPos(lineInfo.substr(20, 20), 0, ' ');
        string expiryDate = substringAtPos(lineInfo.substr(40, 10), 0, ' ');
        string cvc = substringAtPos(lineInfo.substr(50, 3), 0, ' ');

        mcInfo.acctNumber = acctNum;
        mcInfo.cardNumber = cardNum;
        mcInfo.expiryDate = expiryDate;
        mcInfo.cvc = cvc;
    }

    return mcInfo;
}

void MastercardApplication::outputMCInfo(MastercardInfo mcInfo)
{
    ofstream outfile;
    outfile.open((MC_DIRECTORY + "mastercardLists.mc").data(), ios::app);
    if (outfile.is_open()){
        outfile << left
                << setw(20) << mcInfo.acctNumber
                << setw(20) << mcInfo.cardNumber
                << setw(10) << mcInfo.expiryDate
                << setw(3) << mcInfo.cvc;
        outfile << endl;
    }
    else {
        cerr << "Error creating mastercard file." << endl;
        exit(1);
    }
    outfile.close();
}

bool MastercardApplication::checkIfMastercardExists(string acctNum)
{
    return fileExists(MC_DIRECTORY + acctNum + ".mc");
}

bool MastercardApplication::checkIfCardNumExists(string cardNum)
{
    string directory = MC_DIRECTORY + "mastercardLists.mc";
    if (!fileExists(directory)) createFile(directory);

    ifstream infile;
    infile.open(directory.data(), ios::in);
    if (infile.is_open()){
        while (!infile.eof()){
            MastercardInfo mcInfo = getSingleMCInfo(infile);
            if (mcInfo.cardNumber == cardNum){
                infile.close();
                return true;
            }
        }
    }
    else {
        cerr << "Unable to open Mastercard file." << endl;
        exit(1);
    }
    infile.close();
    return false;
}

string MastercardApplication::generateCardNumber()
{
    string cardNum = "";
    srand(time(NULL));

    do {
        int size = 0;
        while (size != 16){
            int genNum = rand() % 10;
            std::ostringstream strs;
            strs << genNum;
            cardNum += strs.str();
            size++;
        }
        if (checkIfCardNumExists(cardNum)){
            size = 0;
            cardNum = "";
        }
        else break;
    } while (1);

    return cardNum;
}

string MastercardApplication::setDate()
{
    time_t theTime = time(NULL);
    struct tm * aTime = localtime(&theTime);

    int month = aTime -> tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    int year = aTime -> tm_year + 1900; // Year is # years since 1900

    int expiryDate = year + 10;

    ostringstream strs1;
    strs1 << month;
    string strMonth = strs1.str();

    ostringstream strs2;
    strs2 << expiryDate;
    string strYear = strs2.str();

    return strMonth + "/" + strYear;
}

string MastercardApplication::generateCVC()
{
    string cvc;
    srand(time(NULL));
    int size = 0;
    while (size != 3){
        int genNum = rand() % 10;
        std::ostringstream strs;
        strs << genNum;
        cvc += strs.str();
        size++;
    }

    return cvc;
}

MastercardApplication::MastercardApplication()
{

}

MastercardApplication::MastercardApplication(DataHandler dataHandler)
{
    this->dataHandler = dataHandler;
}

void MastercardApplication::applyForMastercard()
{
    string acctNumber;
    string name, address;
    AcctInfo currentAcct;

    clearScreen();
    cout << "\tMASTERCARD APPLICATION" << endl;

    do {
        cout << "Please enter your account number: ";
        getline(cin >> ws, acctNumber);
        currentAcct = dataHandler.getMatchedAccount(acctNumber);
        if (currentAcct.name != "") break;
        cout << "Invalid Account Number" << endl;
    } while (1);

    if (!checkIfMastercardExists(acctNumber)){
        if (currentAcct.balance - 15000 < 0){
            cout << "It seems that you have insufficient balance to proceed. Your"
                    " account should have a minimum balance of P15000." << endl;
        }
        else {
            cout << "Before we proceed, we need to confirm the name and address of your account," << endl;

            do {
                cout << "Please enter your full name: ";
                getline(cin >> ws, name);
                if (name == currentAcct.name) break;
                cout << "Name does not match!" << endl;
            } while (1);

            do {
                cout << "Please enter your full address: ";
                getline(cin >> ws, address);
                if (address == currentAcct.address) break;
                cout << "Address does not match!" << endl;
            } while (1);

            cout << "Thank you. You will be charged P200." << endl;
            enterToContinue();
            clearScreen();

            MastercardInfo mcInfo;
            mcInfo.cardNumber = generateCardNumber();
            mcInfo.acctNumber = currentAcct.acctNum;
            mcInfo.expiryDate = setDate();
            mcInfo.cvc = generateCVC();
            outputMCInfo(mcInfo);
            cout << "You have successfully created your Mastercard. Please take note of the following." << endl;
            cout << "Card Number: " << mcInfo.cardNumber << endl;
            cout << "Card Expiry Date: " << mcInfo.expiryDate << endl;
            cout << "Card CVC: " << mcInfo.cvc << endl;
            cout << endl;
        }
        enterToContinue();
    }
    else {
        cout << "You already have a Mastercard." << endl;
        enterToContinue();
    }
}

