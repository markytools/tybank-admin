#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <fstream>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <utils.h>
using namespace std;

const string MC_DIRECTORY = "D:/ROOT/CODE/DIR/mastercard/";
const string ACCT_FILE = "D:/ROOT/CODE/DIR/acct.lst";
const string RECORDS_DIR = "D:/ROOT/CODE/DIR/records/";

enum Bank_Home_State {
    OUT, IN
};

enum Selection {
    NEW_ACCOUNT, EDIT_ACCTS, APPLY_FOR_MASTERCARD, ACQUIRE_BS, ATM_TRANS, EXIT_BANK
};

struct AcctInfo {
    string name;
    string address;
    string acctNum;
    float balance;
    string pin;
};

void setBHState(Bank_Home_State state);
void setSelection(Selection s);
void setBalance(string acctNum, float bal);
void setPin(string acctNum, string pin);
bool fileExists(string name);
void createFile(string filename);

class DataHandler
{
protected:
    void setBalance(string acctNum, float bal);
    void setPin(string acctNum, string pin);
public:
    DataHandler();
    AcctInfo getSingleInfos(ifstream &infile);
    AcctInfo getMatchedAccount(string acctNumber);
    bool checkSameName(string name);
    bool checkSameAcctNum(string acctNum);
    void getFileInfo();
    int getTotalAccounts();
};


#endif // DATAHANDLER_H
