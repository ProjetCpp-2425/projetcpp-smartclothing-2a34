#include "connection.h"
#include <QMessageBox>
#include <QDebug>

connection::connection() {}

bool connection::createconnection()
{

   /* // Adding the database with the specified driver
    db = QSqlDatabase::addDatabase("QODBC");
    if (!db.isValid()) {
          qDebug() << "Le pilote QODBC n'est pas valide. Vérifiez que le pilote est installé.";
          return false;
      }*/
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("source2a34");      // Set the DSN name
    db.setUserName("projectcpp2a34");       // Set the username
    db.setPassword("mp2a34");              // Set the password

    // Try to open the database
    if (db.open()) {
        qDebug() << "Database connected successfully.";
        test = true;
        //return true;
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
               //return false;
    }
    // Message de confirmation si la connexion réussit
       QMessageBox::information(nullptr, "Succès", "Connexion à la base de données réussie !");
       qDebug() << "Connexion réussie à la base de données.";
    return test;
}

void connection::closeconnection(){db.close();}
