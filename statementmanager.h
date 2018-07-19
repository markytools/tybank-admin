#ifndef STATEMENTMANAGER_H
#define STATEMENTMANAGER_H

#include "datahandler.h"
using namespace std;

const string TRANS_NAME_DEPOSIT = "Qck. Dep.";
const string TRANS_NAME_CASH = "Qck. Cash";
const string TRANS_NAME_MONEY_TRANSFER = "Money Transfer";
const string TRANS_NAME_MONEY_RECEIVED = "Money Received";
const string TRANS_NAME_BANK_BILL = "Bank Payments";
const string TRANS_NAME_SMART = "Smart Padala";
const string TRANS_NAME_GLOBE = "G-Cash";
const string TRANS_NAME_NORECO = "Noreco BILL";
const string TRANS_NAME_SILLIMAN = "SU. Tuition";

const string REMARKS_OK1 = "N";
const string REMARKS_OK2 = "S";
const string REMARKS_OK3 = "Z";

struct TransactionInfo {
    string name;
    float amountCredited;
    float amountDebited;
    string dateOfTrans;
    string remarks;
};

class StatementManager : private DataHandler
{
private:

public:
    StatementManager();

    void createStatementFile(string acctNum);
    void addTransactionInfo(string acctNum, TransactionInfo transInfo);
    void printBankStatement(string acctNum);
    void acquireBankStatement();
};

#endif // STATEMENTMANAGER_H
