#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class Employe {
public:
    QString Nom;
    QString Prenom;
    QString Email;
    int Telephone;
    QString Id_employe;
    QString Poste;
    double Salaire;
    QString Presence;
    double heures_supplementaires;
    QString Date_naissance;
    QString Date_embauche;

    Employe();
    Employe(const QString &Nom, const QString &Prenom, const QString &Email, int Telephone,
            const QString &Id_employe, const QString &Poste, double Salaire, const QString &Presence,
            double heures_supplementaires, const QString &Date_naissance, const QString &Date_embauche);

    QString getIdEmploye() const { return Id_employe; }
    QString getNom() const { return Nom; }
    QString getPrenom() const { return Prenom; }
    QString getEmail() const { return Email; }
    int getTelephone() const { return Telephone; }
    QString getPoste() const { return Poste; }
    double getSalaire() const { return Salaire; }
    QString getPresence() const { return Presence; }
    double getHeuresSupplementaires() const { return heures_supplementaires; }
    QString getDateNaissance() const { return Date_naissance; }
    QString getDateEmbauche() const { return Date_embauche; }

    void setIdEmploye(const QString& id) { Id_employe = id; }
    void setNom(const QString& nom) { Nom = nom; }
    void setPrenom(const QString& prenom) { Prenom = prenom; }
    void setEmail(const QString& email) { Email = email; }
    void setTelephone(int telephone) { Telephone = telephone; }
    void setPoste(const QString& poste) { Poste = poste; }
    void setSalaire(double salaire) { Salaire = salaire; }
    void setPresence(const QString& presence) { Presence = presence; }
    void setHeuresSupplementaires(double heures) { heures_supplementaires = heures; }
    void setDateNaissance(const QString& date) { Date_naissance = date; }
    void setDateEmbauche(const QString& date) { Date_embauche = date; }
    bool ajouter();
    bool supprimer();
    bool modifier();
    bool load();
    QSqlQueryModel* afficher();
};

#endif
