#include "connection.h"
#include <QSqlError>

connection::connection() {}

bool connection::createconnection() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a34");
    db.setUserName("Doua");  // Nom de l'utilisateur
    db.setPassword("oracle");  // Mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
        qDebug() << "Connexion à la base de données réussie.";
    } else {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
    }

    return test;
}

void connection::closeConnection() {
    QSqlDatabase::database().close();
    qDebug() << "Connexion à la base de données fermée.";
}
