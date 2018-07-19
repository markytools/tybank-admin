#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <datahandler.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <iostream>
#include <QDateTime>
#include <QSqlError>
using namespace std;

class AccountManager : private DataHandler
{
private:
    void flushInfo(string name, string address, string acctNum, float balance, string pin);
    string generateAcctNumber();

protected:
    void acquireData();
    bool checkForDuplicates(string firstName, string middleName, string lastName);

public:
    AccountManager();

    void displayAccountCreation();
};

#endif // ACCOUNTMANAGER_H
