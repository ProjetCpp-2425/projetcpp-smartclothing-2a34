#ifndef ARTICLE_H
#define ARTICLE_H
#include<QDateTime>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlDatabase>
#include<QDebug>

class ARTICLE
{
    QString ID_ARTICLE;
    QString NOM_A;
    QString DESCRIPTIONN;
    double PRIX;
    QString CATEGORIE;
    int QUANTITE_STOCK;
    QString TAILLE;
    QString COULEUR;  // Changement en QStringList pour supporter plusieurs couleurs
    QString TYPE;
    QDate DATE_AJOUT;


public:
    //Constructeurs
    ARTICLE(){}
    ARTICLE(const QString &ID_ARTICLE, const QString &NOM_A, const QString &DESCRIPTIONN, double PRIX, const QString &CATEGORIE, int QUANTITE_STOCK,
            const QString &TAILLE , const QString &COULEUR, const QString &TYPE, const QDate &DATE_AJOUT);



    //Getters
    QString getCodeArticle()const{return ID_ARTICLE;}
    QString getNomArticle()const{return NOM_A;}
    QString getDescription()const{return DESCRIPTIONN;}
    double getPrix()const{return PRIX;}
    QString getCategorie()const{return CATEGORIE;}
    int getQuantiteStock()const{return QUANTITE_STOCK;}
    QString getTaille()const{return TAILLE;}
    QString getCouleur()const{return COULEUR;}
    QString getType()const{return TYPE;}
    QDate getDateAjout()const{return DATE_AJOUT;}


    //Setters
    void setCodeArticle(const QString &ID_ARTICLE){this->ID_ARTICLE=ID_ARTICLE;}
    void setNomArticle(const QString &n){NOM_A=n;}
    void setDescription(const QString &d){DESCRIPTIONN=d;}
    void setPrix(double P){PRIX=P;}
    void setCategorie(const QString &E){CATEGORIE=E;}
    void setQuantiteStock(int Q){QUANTITE_STOCK=Q;}
    void setTaille(const QString &T){TAILLE=T;}
    void setCouleur(const QString &c){COULEUR=c;}
    void setType(const QString &Y){TAILLE=Y;}
    void setDateAjout(const QDate &M){DATE_AJOUT=M;}

    //Fonctionnalités de base relatives à l'entité Articles

    bool ajouterArticle();
    QSqlQueryModel * afficherArticle();
    bool supprimerArticles(QString ID_ARTICLE);
    /* bool mettreAJourArticle(QString ID_ARTICLE, QString NOM_A, QString DESCRIPTIONN, double PRIX,
                              QString CATEGORIE, int QUANTITE_STOCK, QString TAILLE, QString COULEUR,
                              QString TYPE, QDateTime DATE_AJOUT);*/
    bool chercher(QString id);
    bool modifier();
    // Comparer les articles pour détecter les modifications
    bool estIdentique(const ARTICLE &autre) const;

    // Générer un message de changement pour chaque attribut modifié
    QStringList genererAlertesModification(const ARTICLE &articleOriginal) const;

};




















#endif // ARTICLE_H
