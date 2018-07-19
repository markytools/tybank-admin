#ifndef ATM_H
#define ATM_H

#include <iostream>
#include "statementmanager.h"
#include "datahandler.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include "../src/SmtpMime"
#include "utils.h"
#include <QString>
using namespace std;

const string NOT_ENOUGH_BAL = "Insufficient Balance.";
const string MAX_AMOUNT = "Maximum withdraw amount is P 50,000.";
const string INV_CASH_DENOM = "You can only withdraw cash in denominations of 100, 200, 500, 1000.";

const string FAST_CASH_SELECTIONS =
        string("1 - P 10,000                                              \n") +
        string("2 - P 5,000                                               \n") +
        string("3 - P 2,000                                               \n") +
        string("4 - P 1,000                                               \n") +
        string("5 - P 500                                                 \n");

const string BILLS_PAYMENT_SELECTIONS =
        string("1 - SMART                                                  \n") +
        string("2 - GLOBE                                                  \n") +
        string("3 - NORECO                                                 \n") +
        string("4 - SILLIMAN                                               \n");

const string TRANSFER_COST = "P 1.00 per P 100.00";

enum Atm_Trans_Selection {
    BALANCE_INQUIRY, WITHDRAW_CASH, FAST_CASH, CHANGE_PIN, DEPOSIT, BILLS_PAYMENT, FUND_TRANSFER
};

class Atm : public DataHandler
{
private:
    AcctInfo loadedAcct;
    StatementManager sManager;
    string loadedAcctNum = "";
    Atm_Trans_Selection aTSelection;
    bool exitATM = false;

    void displayCurrentTransaction();
    void setLoadedAccount();

protected:
    bool validatePin();
    void performAnotherTransaction();
    bool checkIfWholeNumber(float num);
    bool isDigits(string &str);
    bool checkIfOkToWithdraw(float bal, float amount);
    void flushTransInfo(string acctNum, string name, float credits, float debits, string date, string remarks);
    AcctInfo getMatchedATMAcct(string acctNumber);

public:
    Atm();
    Atm(StatementManager sManager);

    void balanceInquiry();
    void withdrawCash();
    void fastCash();
    void changePin();
    void deposit();
    void billsPayment();
    void fundTransfer();
    void resetLoadedAccount();
    void displayATM();
};

#endif // ATM_H
