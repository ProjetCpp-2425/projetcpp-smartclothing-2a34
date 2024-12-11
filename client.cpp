#include "client.h"
#include "qsqlerror.h"

client::client() {}

client::client(QString cin_client, QString numero_c, QString nomc, QString prenomc, QString mail_c, QDate date_inscription)
    : cin_client(cin_client), numero_c(numero_c), nomc(nomc), prenomc(prenomc), mail_c(mail_c), date_inscription(date_inscription)
{
}

QString client::getCIN() const { return cin_client; }
QString client::getNumero() const { return numero_c; }
QString client::getNom() const { return nomc; }
QString client::getPrenom() const { return prenomc; }
QString client::getMail() const { return mail_c; }
QDate client::getDateInscription() const { return date_inscription; }

void client::setCIN(QString cin) { cin_client = cin; }
void client::setNumero(QString numero) { numero_c = numero; }
void client::setNom(QString nom) { nomc = nom; }
void client::setPrenom(QString prenom) { prenomc = prenom; }
void client::setMail(QString mail) { mail_c = mail; }
void client::setDateInscription(QDate date) { date_inscription = date; }

bool client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription) "
                  "VALUES (:CIN_client, :nom_c, :prenom_c, :numero_c, :mail_c, :date_inscription)");
    query.bindValue(":CIN_client", cin_client);
    query.bindValue(":nom_c", nomc);
    query.bindValue(":prenom_c", prenomc);
    query.bindValue(":numero_c", numero_c);
    query.bindValue(":mail_c", mail_c);
    query.bindValue(":date_inscription", date_inscription);

    return query.exec();
}

QSqlQueryModel* client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription FROM CLIENT");
    return model;
}

bool client::modifier()
{
    // Fetch current values from the database if fields are empty
    QSqlQuery query;
    query.prepare("SELECT numero_c, nom_c, prenom_c, date_inscription, mail_c FROM CLIENT WHERE cin_client = :cin_client");
    query.bindValue(":cin_client", cin_client);
    if (!query.exec() || !query.next()) {
        return false; // CIN not found or query failed
    }

    // Default to existing values if fields are left empty
    QString currentNumero = query.value(0).toString();
    QString currentNom = query.value(1).toString();
    QString currentPrenom = query.value(2).toString();
    QDate currentDateInscription = query.value(3).toDate();
    QString currentMail = query.value(4).toString();

    QString updatedNumero = numero_c.isEmpty() ? currentNumero : numero_c;
    QString updatedNom = nomc.isEmpty() ? currentNom : nomc;
    QString updatedPrenom = prenomc.isEmpty() ? currentPrenom : prenomc;
    QDate updatedDateInscription = date_inscription.isValid() ? date_inscription : currentDateInscription;
    QString updatedMail = mail_c.isEmpty() ? currentMail : mail_c;

    // Update query
    query.prepare("UPDATE CLIENT SET numero_c = :numero_c, nom_c = :nom_c, prenom_c = :prenom_c, "
                  "date_inscription = :date_inscription, mail_c = :mail_c WHERE cin_client = :cin_client");
    query.bindValue(":numero_c", updatedNumero);
    query.bindValue(":nom_c", updatedNom);
    query.bindValue(":prenom_c", updatedPrenom);
    query.bindValue(":date_inscription", updatedDateInscription);
    query.bindValue(":mail_c", updatedMail);
    query.bindValue(":cin_client", cin_client);

    return query.exec();
}


bool client::supprimer(QString cin_client)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN_client=:CIN_client");
    query.bindValue(":CIN_client", cin_client);

    return query.exec();
}

bool client::cinExists(QString cin_client)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE CIN_client = :CIN_client");
    query.bindValue(":CIN_client", cin_client);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

QSqlQuery client::searchClient(const QString &searchColumn, const QString &searchTerm) {
    QSqlQuery query;

    // Construct the query string without the MAIL_C column
    QString queryStr = QString("SELECT CIN_client, nom_c, prenom_c, numero_c "
                               "FROM CLIENT WHERE LOWER(%1) LIKE LOWER(:searchTerm)").arg(searchColumn);

    qDebug() << "Executing query: " << queryStr; // Debugging the query to ensure it's correct

    // Prepare the query
    query.prepare(queryStr);
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError().text();
    }

    return query;
}

bool sendEmail(const QString &email, const QString &subject, const QString &message) {
    // Simulate email sending logic (replace with actual email sending API or library)
    qDebug() << "Sending email to:" << email;
    qDebug() << "Subject:" << subject;
    qDebug() << "Message:" << message;

    // Simulate success for demonstration
    return true; // Return true if successful, false otherwise
}

