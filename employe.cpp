#include "Employe.h"
#include <QDebug>
#include <QSqlError>

Employe::Employe(const QString &Nom, const QString &Prenom, const QString &Email, int Telephone,
                 const QString &Id_employe, const QString &Poste, double Salaire, const QString &Presence,
                 double heures_supplementaires, const QString &Date_naissance, const QString &Date_embauche)
    : Nom(Nom), Prenom(Prenom), Email(Email), Telephone(Telephone),
    Id_employe(Id_employe), Poste(Poste), Salaire(Salaire), Presence(Presence),
    heures_supplementaires(heures_supplementaires), Date_naissance(Date_naissance),
    Date_embauche(Date_embauche) {}
Employe::Employe()
    : Nom(""), Prenom(""), Email(""), Telephone(0),
    Id_employe(""), Poste(""), Salaire(0.0),
    Presence(""), heures_supplementaires(0.0),
    Date_naissance(""), Date_embauche("") {}
bool Employe::ajouter() {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE Id_employe = :Id_employe");
    checkQuery.bindValue(":Id_employe", Id_employe);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        qDebug() << "Erreur: l'Id_employe existe déjà.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (Id_employe, Nom, Prenom, Poste, Salaire, Telephone, Email, Presence, "
                  "Date_naissance, Date_embauche, heures_supplementaires) "
                  "VALUES (:Id_employe, :Nom, :Prenom, :Poste, :Salaire, :Telephone, :Email, :Presence, "
                  "TO_DATE(:Date_naissance, 'DD/MM/YYYY'), TO_DATE(:Date_embauche, 'DD/MM/YYYY'), :heures_supplementaires)");

    query.bindValue(":Id_employe", Id_employe);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Prenom", Prenom);
    query.bindValue(":Poste", Poste);
    query.bindValue(":Salaire", Salaire);
    query.bindValue(":Telephone", Telephone);
    query.bindValue(":Email", Email);
    query.bindValue(":Presence", Presence);
    query.bindValue(":Date_naissance", Date_naissance);
    query.bindValue(":Date_embauche", Date_embauche);
    query.bindValue(":heures_supplementaires", heures_supplementaires);

    if (query.exec()) {
        qDebug() << "Employe ajouté : " << Nom;
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout de l'employé :" << query.lastError().text();
        return false;
    }
}

bool Employe::supprimer() {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE Id_employe = :Id_employe");
    query.bindValue(":Id_employe", Id_employe);

    if (query.exec()) {
        qDebug() << "Employe supprimé : " << Nom;
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression de l'employé : " << query.lastError().text();
        return false;
    }
}



bool Employe::load() {
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE Id_employe = :id");
    query.bindValue(":id", Id_employe);

    if (query.exec() && query.next()) {
        Nom = query.value("Nom").toString();
        Prenom = query.value("Prenom").toString();
        Email = query.value("Email").toString();
        Telephone = query.value("Telephone").toInt();
        Poste = query.value("Poste").toString();
        Salaire = query.value("Salaire").toDouble();
        Presence = query.value("Presence").toString();
        heures_supplementaires = query.value("heures_supplementaires").toDouble();
        Date_naissance = query.value("Date_naissance").toString();
        Date_embauche = query.value("Date_embauche").toString();
        return true;
    } else {
        return false;
    }
}
bool Employe::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYE SET "
                  "Nom = :nom, "
                  "Prenom = :prenom, "
                  "Email = :email, "
                  "Telephone = :telephone, "
                  "Poste = :poste, "
                  "Salaire = :salaire, "
                  "Presence = :presence, "
                  "Heures_supplementaires = :heures_sup, "
                  "Date_naissance = TO_DATE(:date_naissance, 'YYYY-MM-DD'), "
                  "Date_embauche = TO_DATE(:date_embauche, 'YYYY-MM-DD') "
                  "WHERE Id_employe = :id");

    query.bindValue(":nom", getNom());
    query.bindValue(":prenom", getPrenom());
    query.bindValue(":email", getEmail());
    query.bindValue(":telephone", getTelephone());
    query.bindValue(":poste", getPoste());
    query.bindValue(":salaire", getSalaire());
    query.bindValue(":presence", getPresence());
    query.bindValue(":heures_sup", getHeuresSupplementaires());
    query.bindValue(":date_naissance", getDateNaissance());
    query.bindValue(":date_embauche", getDateEmbauche());
    query.bindValue(":id", getIdEmploye());

    qDebug() << "Attempting to modify employee with ID:" << this->Id_employe;


    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error updating record: " << query.lastError().text();
        return false;
    }
}


QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee");
    return model;
}
