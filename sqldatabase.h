#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <iostream>
using namespace std;

class SQLDatabase
{
public:
    SQLDatabase();
    void connect();
};

#endif // SQLDATABASE_H
