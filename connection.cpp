#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a34");
    db.setUserName("projetcpp2a34");
    db.setPassword("mp2a34");

    if (db.open()) {
        test = true;
        qDebug() << "Database connected successfully.";
    } else {
        qDebug() << "Database connection failed: " << db.lastError().text();
    }

    return test;
}
