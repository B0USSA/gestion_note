#include "dbconnect.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

dbConnect::dbConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("gestion_note");
    db.setHostName("localhost");
    db.setPassword("");
    db.setUserName("root");

    if(db.open()) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected : " << db.lastError();
    }
}
