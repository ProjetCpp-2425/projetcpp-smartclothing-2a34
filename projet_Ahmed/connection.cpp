#include "connection.h"
#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include  "connection.h"
#include  <QApplication>
Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("source2a34");
    db.setUserName("Projectcpp2a34");
    db.setPassword("Mp2a34");

    if(db.open())
    {
        test = true;
    }
    return test;
}

void Connection::closeConnection() { db.close(); }
