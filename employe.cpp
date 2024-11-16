#include "Employe.h"
#include <QDebug>
#include <QSqlError>
#include <QRegularExpression>
#include <QMessageBox>

#include <QDate>


Employe::Employe(const QString &Nom, const QString &Prenom, const QString &Email, int Telephone,
                 const QString &Id_employe, const QString &Poste, double Salaire, const QString &Presence,
                 double heures_supplementaires, const QString &Date_naissance, const QString &Date_embauche, const QString &description, const QString motedepass)
    : Nom(Nom), Prenom(Prenom), Email(Email), Telephone(Telephone),
    Id_employe(Id_employe), Poste(Poste), Salaire(Salaire), Presence(Presence),
    heures_supplementaires(heures_supplementaires), Date_naissance(Date_naissance),
    Date_embauche(Date_embauche),description(description),motedepass(motedepass){}
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

    if (Id_employe.isEmpty()) {
        qDebug() << "Erreur: Id_employe est vide.";
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

    QRegularExpression idRegex("^\\d{8}$");
    QRegularExpressionMatch idMatch = idRegex.match(Id_employe);
    if (!idMatch.hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur","Id_employe doit contenir exactement 8 chiffres.");
        return false;
    }

    if (Nom.isEmpty() || Prenom.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur","Nom ou Prenom est vide.");
        return false;
    }

    if (Presence.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur","Presence est vide.");
        return false;
    }


    QRegularExpression nameRegex("^[A-Za-zÀ-ÖØ-öø-ÿ\\-\\s]+$");
    if (!nameRegex.match(Nom).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur","Nom ou Prenom ne doit contenir que des lettres.");
        return false;
    }
    if (!nameRegex.match(Prenom).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur","Nom ou Prenom ne doit contenir que des lettres.");
        return false;
    }

    // Basic email format validation regex
    QRegularExpression emailRegex("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    QRegularExpressionMatch emailMatch = emailRegex.match(Email);

    // Check if the email is valid
    if (!emailMatch.hasMatch()) {
        qDebug() << "Erreur: L'email est invalide.";
        return false;
    }

    QDate naissanceDate = QDate::fromString(Date_naissance, "dd/MM/yyyy");
    QDate embaucheDate = QDate::fromString(Date_embauche, "dd/MM/yyyy");

    if (!naissanceDate.isValid()) {
        QMessageBox::warning(nullptr, "Erreur", "naissanceDate est invalide");
        return false;
    }
    if (!embaucheDate.isValid()) {
        QMessageBox::warning(nullptr, "Erreur", "embaucheDate est invalides");
        return false;
    }

    if (Salaire <= 0 || heures_supplementaires < 0) {
        QMessageBox::warning(nullptr, "Erreur","Salaire ou heures supplémentaires sont invalides");
        return false;
    }

    if (Telephone < 10000000 || Telephone > 99999999) {
        QMessageBox::warning(nullptr, "Erreur","Telephone est invalide");
        return false;
    }

    // Add validation for MoteDePass (Password)
    if (motedepass.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Mot de passe est vide.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (Id_employe, Nom, Prenom, Poste, Salaire, Telephone, Email, Presence, "
                  "Date_naissance, Date_embauche, heures_supplementaires, motedepass) "
                  "VALUES (:Id_employe, :Nom, :Prenom, :Poste, :Salaire, :Telephone, :Email, :Presence, "
                  "TO_DATE(:Date_naissance, 'DD/MM/YYYY'), TO_DATE(:Date_embauche, 'DD/MM/YYYY'), :heures_supplementaires, :motedepass)");

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
    query.bindValue(":motedepass", motedepass); // Bind password field

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
QSqlQueryModel* Employe::afficherParPrenom(const QString& prenom) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE Prenom = :prenom");
    query.bindValue(":prenom", prenom);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors de l'affichage des employés par prenom:" << query.lastError().text();
    }

    return model;
}
QSqlQueryModel* Employe::afficherParID(const QString&Id_employe ) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE Id_employe = :Id_employe");
    query.bindValue(":Id_employe", Id_employe);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors de l'affichage des employés par prenom:" << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* Employe::afficherParPoste(const QString& poste) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE Poste = :poste");
    query.bindValue(":poste", poste);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors de l'affichage des employés par poste:" << query.lastError().text();
    }

    return model;
}
// Employe.cpp
void Employe::supprimerDemandeConge(const QString &idEmploye, const QString &description) {
    QSqlQuery query;
    query.prepare("DELETE FROM DemandeConge WHERE Id_employe = :idEmploye AND description = :description");
    query.bindValue(":idEmploye", idEmploye);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Error deleting leave request:" << query.lastError().text();
    } else {
        qDebug() << "Leave request deleted successfully.";
    }
}

