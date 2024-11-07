#include "transaction.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
Transaction::Transaction() : IDTRANSACTION(0), TAXES(0.0), REDUCTION(0.0), MONTANT(0.0),LISTEARTICLES(""), METHODEPAIEMENT("") {}

Transaction::Transaction(int IDTRANSACTION, QDateTime DATEHEUREAJOUT, QString LISTEARTICLES, float taxes, float reduction, float montant, QString METHODEPAIEMENT)
    : IDTRANSACTION(IDTRANSACTION), DATEHEUREAJOUT(DATEHEUREAJOUT), LISTEARTICLES(LISTEARTICLES), TAXES(taxes), REDUCTION(reduction), MONTANT(montant), METHODEPAIEMENT(METHODEPAIEMENT) {}

int Transaction::getIdTransaction() const { return IDTRANSACTION; }
QDateTime Transaction::getDateHeureAjout() const { return DATEHEUREAJOUT; }
QString Transaction::getListeArticles() const { return LISTEARTICLES; }
float Transaction::getTaxes() const { return TAXES; }
float Transaction::getReduction() const { return REDUCTION; }
float Transaction::getMontant() const { return MONTANT; }
QString Transaction::getMethodePaiement() const { return METHODEPAIEMENT; }

void Transaction::setIdTransaction(int IDTRANSACTION) { this-> IDTRANSACTION = IDTRANSACTION; }
void Transaction::setDateHeureAjout(const QDateTime &DATEHEUREAJOUT) {  this-> DATEHEUREAJOUT = DATEHEUREAJOUT ; }
void Transaction::setListeArticles(const QString &LISTEARTICLES) {  this-> LISTEARTICLES = LISTEARTICLES; }
void Transaction::setTaxes(float t) { TAXES = t; }
void Transaction::setReduction(float r) { REDUCTION = r; }
void Transaction::setMontant(float m) { MONTANT = m; }
void Transaction::setMethodePaiement(const QString &METHODEPAIEMENT) {  this-> METHODEPAIEMENT = METHODEPAIEMENT; }

bool Transaction::ajouter(int IDTRANSACTION, const QDateTime& DATEHEUREAJOUT, const QString& LISTEARTICLES, float TAXES, float REDUCTION, float MONTANT, const QString& METHODEPAIEMENT) {
    QSqlQuery query;
    query.prepare("INSERT INTO TRANSACTION (IDTRANSACTION, DATEHEUREAJOUT, LISTEARTICLES, TAXES, REDUCTION, MONTANT, METHODEPAIEMENT) "
                  "VALUES (:IDTRANSACTION, :DATEHEUREAJOUT, :LISTEARTICLES, :taxes, :reduction, :montant, :METHODEPAIEMENT)");
    query.bindValue(":IDTRANSACTION", IDTRANSACTION);
    query.bindValue(":DATEHEUREAJOUT", DATEHEUREAJOUT);
    query.bindValue(":LISTEARTICLES", LISTEARTICLES);
    query.bindValue(":taxes", TAXES);
    query.bindValue(":reduction", REDUCTION);
    query.bindValue(":montant", MONTANT);
    query.bindValue(":METHODEPAIEMENT", METHODEPAIEMENT);
    return query.exec();
}

QSqlQueryModel* Transaction::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TRANSACTION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDTRANSACTION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEHEUREAJOUT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LISTEARTICLES"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Taxes"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Réduction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("METHODEPAIEMENT"));
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


bool Transaction::modifier(int IDTRANSACTION, const QDateTime& DATEHEUREAJOUT, const QString& LISTEARTICLES, float TAXES, float REDUCTION, float MONTANT, const QString& METHODEPAIEMENT) {
    QSqlQuery query;
    query.prepare("UPDATE TRANSACTION SET DATEHEUREAJOUT = :DATEHEUREAJOUT, LISTEARTICLES = :LISTEARTICLES, TAXES = :TAXES, "
                  "REDUCTION = :REDUCTION, MONTANT = :MONTANT, METHODEPAIEMENT = :METHODEPAIEMENT WHERE IDTRANSACTION = :IDTRANSACTION");
    query.bindValue(":IDTRANSACTION", IDTRANSACTION);
    query.bindValue(":DATEHEUREAJOUT", DATEHEUREAJOUT);
    query.bindValue(":LISTEARTICLES", LISTEARTICLES);
    query.bindValue(":TAXES", TAXES);
    query.bindValue(":REDUCTION", REDUCTION);
    query.bindValue(":MONTANT", MONTANT);
    query.bindValue(":METHODEPAIEMENT", METHODEPAIEMENT);

    return query.exec();
}

