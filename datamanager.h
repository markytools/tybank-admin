#ifndef DATAMANAGER
#define DATAMANAGER

#include <fstream>
#include "atm.h"
using namespace std;

const string ACCT_FILE = "D:/Documents/QT Project/TyBankOOD/acct.lst";
const string RECORDS_DIR = "D:/Documents/QT Project/TyBankOOD/records/";

enum Bank_Home_State {
    OUT, IN
};

enum Selection {
    NEW_ACCOUNT, ACQUIRE_BS, ATM_TRANS, EXIT_BANK
};

void setBHState(Bank_Home_State state);
void setSelection(Selection s);
void setBalance(string acctNum, float bal);
void setPin(string acctNum, string pin);

struct AcctInfo;

class dataHandler{
public:
    AcctInfo getSingleInfos(ifstream &infile);
    AcctInfo getMatchedAccount(string acctNumber);
};

#endif // DATAMANAGER

