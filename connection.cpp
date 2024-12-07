#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("haythem");
    db.setPassword("123456");

    if (db.open()) {
        test = true;
        qDebug() << "Database connected successfully.";
    } else {
        qDebug() << "Database connection failed: " << db.lastError().text();
    }

    return test;
}
