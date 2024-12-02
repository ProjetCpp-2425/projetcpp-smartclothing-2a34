#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class client
{
private:

    QString cin_client;
    QString numero_c;
    QString nomc;
    QString prenomc;
    QString mail_c;
    QDate date_inscription;

public:
    client();
    client(QString cin_client, QString numero_c, QString nomc, QString prenomc, QString mail_c, QDate date_inscription);

    QString getCIN() const;
    QString getNumero() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getMail() const;
    QDate getDateInscription() const;

    void setCIN(QString cin);
    void setNumero(QString numero);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setMail(QString mail);
    void setDateInscription(QDate date);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(QString cin_client);
    bool cinExists(QString cin_client);
    QSqlQueryModel* rechercher(const QString& keyword, const QString& field);
    QSqlQuery searchClient(const QString &searchColumn, const QString &searchTerm);
    QSqlQueryModel *getAllClients();
};

#endif // CLIENT_H
