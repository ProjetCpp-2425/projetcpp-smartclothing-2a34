#include "Transaction.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QTextDocument>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QMap>
#include <qdir.h>

Transaction::Transaction()
    : IDTRANSACTION(0), DATEHEUREAJOUT(QDateTime()), LISTEARTICLES(""), TAXES(0.0), REDUCTION(0.0),
    MONTANT(0.0), METHODEPAIEMENT(""), CIN(0), status(0) {}

// Constructeur avec paramètres
Transaction::Transaction(int IDTRANSACTION, QDateTime DATEHEUREAJOUT, QString LISTEARTICLES, float TAXES,
                         float REDUCTION, float MONTANT, QString METHODEPAIEMENT, int CIN, int status)
    : IDTRANSACTION(IDTRANSACTION), DATEHEUREAJOUT(DATEHEUREAJOUT), LISTEARTICLES(LISTEARTICLES),
    TAXES(TAXES), REDUCTION(REDUCTION), MONTANT(MONTANT), METHODEPAIEMENT(METHODEPAIEMENT), CIN(CIN), status(status) {}

// Getters
int Transaction::getIdTransaction() const { return IDTRANSACTION; }
QDateTime Transaction::getDateHeureAjout() const { return DATEHEUREAJOUT; }
QString Transaction::getListeArticles() const { return LISTEARTICLES; }
float Transaction::getTaxes() const { return TAXES; }
float Transaction::getReduction() const { return REDUCTION; }
float Transaction::getMontant() const { return MONTANT; }
QString Transaction::getMethodePaiement() const { return METHODEPAIEMENT; }
int Transaction::getCin() const { return CIN; }
int Transaction::getStatus() const { return status; }

// Setters
void Transaction::setIdTransaction(int IDTRANSACTION) { this->IDTRANSACTION = IDTRANSACTION; }
void Transaction::setDateHeureAjout(const QDateTime &DATEHEUREAJOUT) { this->DATEHEUREAJOUT = DATEHEUREAJOUT; }
void Transaction::setListeArticles(const QString &LISTEARTICLES) { this->LISTEARTICLES = LISTEARTICLES; }
void Transaction::setTaxes(float t) { TAXES = t; }
void Transaction::setReduction(float r) { REDUCTION = r; }
void Transaction::setMontant(float m) { MONTANT = m; }
void Transaction::setMethodePaiement(const QString &METHODEPAIEMENT) { this->METHODEPAIEMENT = METHODEPAIEMENT; }
void Transaction::setCin(int cin) { CIN = cin; }
void Transaction::setStatus(int status) { this->status = status; }

// Méthode d'ajout de la transaction
bool Transaction::ajouter(int idTransaction, const QDateTime& dateAjout, const QString& listeArticles,
                          float taxes, float reduction, float montant, const QString& methodePaiement,
                          int cin, int status) {
    QSqlQuery query;
    query.prepare("INSERT INTO TRANSACTION (IDTRANSACTION, DATEHEUREAJOUT, LISTEARTICLES, TAXES, REDUCTION, MONTANT, METHODEPAIEMENT, CIN, STATUS) "
                  "VALUES (:idTransaction, :dateAjout, :listeArticles, :taxes, :reduction, :montant, :methodePaiement, :cin, :status)");

    query.bindValue(":idTransaction", idTransaction);
    query.bindValue(":dateAjout", dateAjout);
    query.bindValue(":listeArticles", listeArticles);
    query.bindValue(":taxes", taxes);
    query.bindValue(":reduction", reduction);
    query.bindValue(":montant", montant);
    query.bindValue(":methodePaiement", methodePaiement);
    query.bindValue(":cin", cin);
    query.bindValue(":status", status);

    return query.exec();
}
bool Transaction::existeDeja(int idTransaction) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM TRANSACTION WHERE IDTRANSACTION = :idTransaction");
    query.bindValue(":idTransaction", idTransaction);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

QSqlQueryModel* Transaction::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT IDTRANSACTION, DATEHEUREAJOUT, LISTEARTICLES, TAXES, REDUCTION, MONTANT, METHODEPAIEMENT, CIN, STATUS FROM TRANSACTION");

    // Définition des en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Transaction"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date & Heure d'Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Liste d'Articles"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Taxes"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Réduction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Méthode de Paiement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));
    addToHistory("Afficher",0);

    return model;
}


bool Transaction::supprimer(int IDTRANSACTION) {
    QSqlQuery query;
    query.prepare("DELETE FROM Transaction WHERE IDTRANSACTION = :IDTRANSACTION");
    query.bindValue(":IDTRANSACTION", IDTRANSACTION);

    if (!query.exec()) {

        qDebug() << "Erreur lors de la suppression :" << query.lastError().text();
        return false;
    }

    qDebug() << "Suppression réussie pour IDTRANSACTION :" << IDTRANSACTION;
    return true;
}
bool Transaction::idExiste(int idTransaction) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM TRANSACTION WHERE IDTRANSACTION = :idTransaction");
    query.bindValue(":idTransaction", idTransaction);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0;  // Si le compte est supérieur à zéro, l'ID existe
        }
    }
    return false;  // Si la requête échoue ou l'ID n'existe pas, retourner false
}


bool Transaction::modifier(int idTransaction, const QDateTime& dateAjout, const QString& listeArticles,
                           float taxes, float reduction, float montant, const QString& methodePaiement,
                           int cin, int status) {
    // Vérifier si l'ID existe avant de modifier
    if (!existeDeja(idTransaction)) {
        return false;  // Si l'ID n'existe pas, retourner false pour indiquer l'échec
    }

    QSqlQuery query;
    query.prepare("UPDATE TRANSACTION SET "
                  "DATEHEUREAJOUT = :dateAjout, "
                  "LISTEARTICLES = :listeArticles, "
                  "TAXES = :taxes, "
                  "REDUCTION = :reduction, "
                  "MONTANT = :montant, "
                  "METHODEPAIEMENT = :methodePaiement, "
                  "CIN = :cin, "
                  "STATUS = :status "
                  "WHERE IDTRANSACTION = :idTransaction");

    // Lier les paramètres pour la requête
    query.bindValue(":idTransaction", idTransaction);
    query.bindValue(":dateAjout", dateAjout);
    query.bindValue(":listeArticles", listeArticles);
    query.bindValue(":taxes", taxes);
    query.bindValue(":reduction", reduction);
    query.bindValue(":montant", montant);
    query.bindValue(":methodePaiement", methodePaiement);
    query.bindValue(":cin", cin);
    query.bindValue(":status", status);

    // Exécuter la requête et vérifier le succès
    return query.exec();
}
void Transaction::exporterPDF(const QString &nomFichier, QSqlQueryModel *model) {
    // Crée le fichier PDF
    QPdfWriter pdfWriter(nomFichier);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setTitle("Liste des Transactions");
    pdfWriter.setCreator("Application de Gestion des Transactions");

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Définir la police et la couleur
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));

    // Titre du PDF
    painter.drawText(2500, 1100, "Liste des Transactions");

    // Coordonnées et dimensions des cellules
    int startX = 200;
    int startY = 1800;
    int cellWidth = 1100;
    int cellHeight = 450;

    // En-têtes du tableau
    QStringList headers = {"ID Transaction", "Liste des Articles", "Taxes", "Réduction", "Montant", "Mode de Paiement"};
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawText(startX + col * cellWidth, startY, cellWidth, cellHeight, Qt::AlignCenter, headers[col]);
    }

    // Données des transactions
    int rowCount = model->rowCount();
    painter.setFont(QFont("Arial", 10));
    for (int row = 0; row < rowCount; ++row) {
        QColor bgColor = (row % 2 == 0) ? Qt::lightGray : Qt::white;

        for (int col = 0; col < headers.size(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QRect cellRect(startX + col * cellWidth, startY + (row + 1) * cellHeight, cellWidth, cellHeight);

            // Remplir les cellules avec des couleurs alternées pour une meilleure lisibilité
            painter.fillRect(cellRect, bgColor);
            painter.drawText(cellRect, Qt::AlignCenter, data);
            painter.drawRect(cellRect);
        }
    }

    // Fin du dessin du PDF
    painter.end();

    // Message de confirmation
    QMessageBox::information(nullptr, "PDF Créé", "Un fichier PDF a été créé pour les transactions.");
}
QSqlQueryModel* Transaction::trierParDate() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Vérification de la colonne date d'ajout dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM TRANSACTION ORDER BY DATEHEUREAJOUT DESC");  // Utiliser le bon nom de colonne

    if (!query.exec()) {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return nullptr;  // Si la requête échoue, retourne nullptr
    }

    model->setQuery(std::move(query));


    if (model->rowCount() == 0) {
        qDebug() << "Aucune transaction trouvée.";
        return nullptr;  // Si aucune transaction n'est trouvée, retourne nullptr
    }

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Transaction"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Liste des Articles"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Taxes"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Réduction"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mode de Paiement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date d'Ajout"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}
QSqlQueryModel* Transaction::rechercher(int idTransaction) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer la requête pour chercher une transaction par son ID
    query.prepare("SELECT * FROM TRANSACTION WHERE IDTRANSACTION = :idTransaction");
    query.bindValue(":idTransaction", idTransaction);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche de la transaction :" << query.lastError().text();
        delete model;  // Libérer la mémoire si la requête échoue
        return nullptr;  // Retourner nullptr en cas d'échec
    }

    // Charger les résultats dans le modèle
    model->setQuery(std::move(query));

    // Si aucune ligne n'est trouvée, retourner nullptr
    if (model->rowCount() == 0) {
        delete model;
        return nullptr;  // Aucun résultat trouvé
    }

    // Retourner le modèle avec les résultats
    return model;
}
QMap<QString, double> Transaction::statistiquesParStatut() {
    QMap<QString, double> stats;
    QSqlQuery query;

    // Récupérer le nombre total de transactions
    query.prepare("SELECT COUNT(*) FROM TRANSACTION");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération du nombre total de transactions :" << query.lastError().text();
        return stats;
    }

    query.next();
    int totalTransactions = query.value(0).toInt();
    if (totalTransactions == 0) {
        return stats;
    }

    // Récupérer les statistiques par statut
    query.prepare("SELECT STATUS, COUNT(*) FROM TRANSACTION GROUP BY STATUS");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des statistiques de statut :" << query.lastError().text();
        return stats;
    }

    while (query.next()) {
        int status = query.value(0).toInt();
        int count = query.value(1).toInt();
        double percentage = (count * 100.0) / totalTransactions;

        if (status == 1) {
            stats["Approuvé"] = percentage;
        } else {
            stats["Rejeté"] = percentage;
        }
    }

    return stats;
}

void Transaction::addToHistory(const QString &action, int idTransaction) {
    QString cheminFichier = "C:/Users/DELL/Desktop/employe/historique_transaction.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique des transactions.";
        return;
    }

    QTextStream out(&file);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (idTransaction != 0) {
        out << " pour l'ID " << idTransaction;
    }
    out << "\n";
    file.close();
}
