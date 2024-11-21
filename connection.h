#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QDebug>
#include <QtSql/qsqldatabase.h>

class connection {
    QSqlDatabase db;

public:
    connection();
    bool createconnection();
    void closeConnection();
};

#endif // CONNECTION_H
