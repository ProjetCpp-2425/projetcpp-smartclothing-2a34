#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QMap>
#include <QTableView>

class Transaction {
    int IDTRANSACTION;
    QDateTime DATEHEUREAJOUT;
    QString LISTEARTICLES;
    float TAXES;
    float REDUCTION;
    float MONTANT;
    QString METHODEPAIEMENT;
    int CIN;
    int status;

public:
    Transaction();
    Transaction(int IDTRANSACTION, QDateTime DATEHEUREAJOUT, QString LISTEARTICLES, float TAXES, float REDUCTION,
                float MONTANT, QString METHODEPAIEMENT, int CIN, int status);

    // Getters et setters (comme définis précédemment)
    int getIdTransaction() const;
    QDateTime getDateHeureAjout() const;
    QString getListeArticles() const;
    float getTaxes() const;
    float getReduction() const;
    float getMontant() const;
    QString getMethodePaiement() const;
    int getCin() const;
    int getStatus() const;

    void setIdTransaction(int IDTRANSACTION);
    void setDateHeureAjout(const QDateTime &DATEHEUREAJOUT);
    void setListeArticles(const QString &LISTEARTICLES);
    void setTaxes(float t);
    void setReduction(float r);
    void setMontant(float m);
    void setMethodePaiement(const QString &METHODEPAIEMENT);
    void setCin(int cin);
    void setStatus(int status);




    bool ajouter(int idTransaction, const QDateTime& DATEHEUREAJOUT, const QString& listeArticles,
                 float taxes, float reduction, float montant, const QString& methodePaiement,
                 int cin, int status);
    bool existeDeja(int idTransaction);
    QSqlQueryModel* afficher();
    bool supprimer(int IDTRANSACTION);
    bool existeTransaction(int idTransaction) ;


    bool modifier(int idTransaction, const QDateTime& dateAjout, const QString& listeArticles,
                  float taxes, float reduction, float montant, const QString& methodePaiement,
                  int cin, int status);
    bool idExiste(int idTransaction);
    void exporterPDF(const QString& filePath, QSqlQueryModel* model);
    QSqlQueryModel* trierParDate();

    QSqlQueryModel* rechercher(int idTransaction);
    QMap<QString, double> statistiquesParStatut();
    void addToHistory(const QString &action, int idTransaction);

};

#endif // TRANSACTION_H
