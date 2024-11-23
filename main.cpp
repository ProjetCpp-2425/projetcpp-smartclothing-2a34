#include <QApplication>
#include "mainwindow.h"
#include"connection.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Crée l'application
    MainWindow w;                 // Crée la fenêtre principale
    // Utilisation de la classe Connection
    connection connection;
    if (!connection.createconnection()) {
        QMessageBox::critical(nullptr, "Erreur", "Connexion à la base de données échouée !");
        return -1; // Quitte l'application si la connexion échoue
    }
    w.show();                     // Affiche la fenêtre
    return app.exec();            // Lance la boucle événementielle
}
