#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>

class Transaction {
    int IDTRANSACTION;
    QDateTime DATEHEUREAJOUT;
    QString LISTEARTICLES;
    float TAXES;
    float REDUCTION;
    float MONTANT;
    QString METHODEPAIEMENT;

public:
    Transaction();
    Transaction(int IDTRANSACTION, QDateTime DATEHEUREAJOUT, QString LISTEARTICLES, float TAXES, float reduction, float montant, QString METHODEPAIEMENT);

    int getIdTransaction() const;
    QDateTime getDateHeureAjout() const;
    QString getListeArticles() const;
    float getTaxes() const;
    float getReduction() const;
    float getMontant() const;
    QString getMethodePaiement() const;

    void setIdTransaction(int IDTRANSACTION);
    void setDateHeureAjout(const QDateTime &DATEHEUREAJOUT);
    void setListeArticles(const QString &LISTEARTICLES);
    void setTaxes(float taxes);
    void setReduction(float reduction);
    void setMontant(float montant);
    void setMethodePaiement(const QString &METHODEPAIEMENT);


    bool ajouter(int IDTRANSACTION, const QDateTime& DATEHEUREAJOUT, const QString& LISTEARTICLES, float taxes, float reduction, float montant, const QString& METHODEPAIEMENT);
    bool modifier(int IDTRANSACTION, const QDateTime& DATEHEUREAJOUT, const QString& LISTEARTICLES, float TAXES, float REDUCTION, float MONTANT, const QString& METHODEPAIEMENT);

    QSqlQueryModel* afficher();
    bool supprimer(int IDTRANSACTION);
};

#endif // TRANSACTION_H
