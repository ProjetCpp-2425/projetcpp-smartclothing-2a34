#include "articlenotifier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QDate>

ArticleNotifier::ArticleNotifier() {
    trayIcon.setIcon(QIcon(":/new/prefix1/icon.png")); // Remplacer par une icône réelle
    trayIcon.setVisible(true);
}

void ArticleNotifier::notifyStockLow() {
    QSqlQuery query;
    query.prepare("SELECT ID_ARTICLE, NOM_A, QUANTITE_STOCK FROM ARTICLE WHERE QUANTITE_STOCK <= 5");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString idArticle = query.value("ID_ARTICLE").toString();
        QString nom = query.value("NOM_A").toString();
        int quantiteStock = query.value("QUANTITE_STOCK").toInt();

        trayIcon.showMessage("Alerte Stock Faible",
                             QString("L'article %1 (%2) a un stock faible : %3 unités restantes.")
                                 .arg(idArticle)
                                 .arg(nom)
                                 .arg(quantiteStock),
                             QSystemTrayIcon::Warning);
    }
}

void ArticleNotifier::notifyPromotion() {
    QSqlQuery query;
    query.prepare("SELECT ID_ARTICLE, NOM_A, PRIX FROM ARTICLE WHERE PRIX < 50");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString idArticle = query.value("ID_ARTICLE").toString();
        QString nom = query.value("NOM_A").toString();
        double prix = query.value("PRIX").toDouble();

        trayIcon.showMessage("Offre Spéciale",
                             QString("L'article %1 (%2) est en promotion à %3€.").arg(idArticle).arg(nom).arg(prix),
                             QSystemTrayIcon::Information);
    }
}

void ArticleNotifier::notifyAnniversary() {
    QDate currentDate = QDate::currentDate();

    QSqlQuery query;
    query.prepare("SELECT ID_ARTICLE, NOM_A, DATE_AJOUT FROM ARTICLE "
                  "WHERE MONTH(DATE_AJOUT) = :month AND DAY(DATE_AJOUT) = :day");
    query.bindValue(":month", currentDate.month());
    query.bindValue(":day", currentDate.day());

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString idArticle = query.value("ID_ARTICLE").toString();
        QString nom = query.value("NOM_A").toString();
        QDate dateAjout = query.value("DATE_AJOUT").toDate();

        int age = currentDate.year() - dateAjout.year();
        if (currentDate < dateAjout.addYears(age)) {
            age--; // Si l'anniversaire n'est pas encore passé cette année
        }

        trayIcon.showMessage("Anniversaire d'Article",
                             QString("C'est l'anniversaire de l'article %1 (%2) ajouté le %3. Il a %4 an(s) aujourd'hui !")
                                 .arg(idArticle)
                                 .arg(nom)
                                 .arg(dateAjout.toString("dd/MM/yyyy"))
                                 .arg(age),
                             QSystemTrayIcon::Information);
    }
}
