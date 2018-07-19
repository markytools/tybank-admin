#include "sqldatabase.h"

SQLDatabase::SQLDatabase()
{

}

void SQLDatabase::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("ricky.heliohost.org");
    db.setDatabaseName("slylily_tybank");   //You can use our heliohost database, but if you want to create your own, you can use
    db.setUserName("slylily_guest");        //replace the configs here
    db.setPassword("12345678");
    if (!db.open()) cout << "not connected" << endl;

    QSqlQuery query;
    query.exec("SET time_zone = '+00:00'");

//    while (query.next())
//    cout << query.value(0).toInt() << endl;
}
