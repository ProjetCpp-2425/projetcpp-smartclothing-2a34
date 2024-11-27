#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QByteArray> // For fingerprint data


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
    QString description;
    QString motedepass;
    QByteArray fingerprintData;


    Employe();
    Employe(const QString &Nom, const QString &Prenom, const QString &Email, int Telephone,
            const QString &Id_employe, const QString &Poste, double Salaire, const QString &Presence,
            double heures_supplementaires, const QString &Date_naissance, const QString &Date_embauche, const QString &description, const QString motedepass, const QByteArray &fingerprint);

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
    QString getdescription() const { return description; }
    QString getmotedepasse() const { return motedepass; }



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
    void setdescription(const QString& newdescription) { description = newdescription; }
    void setPassword(const QString& newPassword) { motedepass = newPassword; }
    void setFingerprint(const QByteArray &fingerprint) { fingerprintData = fingerprint; };


    bool ajouter();
    bool supprimer();
    bool modifier();
    bool load();
    bool loadfs();
       bool save();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherParPrenom(const QString& prenom);
    QSqlQueryModel* afficherParPoste(const QString& poste);
    QSqlQueryModel* afficherParID(const QString& Id_employe);

    QList<Employe> getAllEmployees();
    void supprimerDemandeConge(const QString &employeeId, const QString &description);
};


#endif
