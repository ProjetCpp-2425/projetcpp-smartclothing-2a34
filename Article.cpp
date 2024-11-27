#include "Article.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QFile>
#include <QMessageBox>
//#include <QtXlsx>

ARTICLE::ARTICLE(const QString &ID_ARTICLE,const QString &NOM_A,const QString &DESCRIPTIONN,double PRIX,const QString &CATEGORIE,int QUANTITE_STOCK,
                 const QString &TAILLE ,const QString &COULEUR, const QString &TYPE, const QDate &DATE_AJOUT)
    :ID_ARTICLE(ID_ARTICLE),NOM_A(NOM_A),DESCRIPTIONN(DESCRIPTIONN),PRIX(PRIX),CATEGORIE(CATEGORIE),QUANTITE_STOCK(QUANTITE_STOCK),
    TAILLE(TAILLE),COULEUR(COULEUR),TYPE(TYPE),DATE_AJOUT(DATE_AJOUT){}

bool ARTICLE::ajouterArticle()
{
    QSqlQuery query;


    query.prepare("INSERT INTO ARTICLE (ID_ARTICLE, NOM_A, DESCRIPTIONN,PRIX, CATEGORIE,QUANTITE_STOCK,TAILLE,COULEUR,TYPE,DATE_AJOUT) "
                  "VALUES (:ID_ARTICLE, :NOM_A, :DESCRIPTIONN,:PRIX,:CATEGORIE,:QUANTITE_STOCK,:TAILLE, :COULEUR,:TYPE,:DATE_AJOUT)");

    query.bindValue(":ID_ARTICLE",ID_ARTICLE);
    query.bindValue(":NOM_A",NOM_A);
    query.bindValue(":DESCRIPTIONN",DESCRIPTIONN);
    query.bindValue(":PRIX",PRIX);
    query.bindValue(":CATEGORIE",CATEGORIE);
    query.bindValue(":QUANTITE_STOCK",QUANTITE_STOCK);
    query.bindValue(":TAILLE",TAILLE);
    query.bindValue(":COULEUR",COULEUR);
    query.bindValue(":TYPE",TYPE);
    query.bindValue(":DATE_AJOUT",DATE_AJOUT);



    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion dans la base de données:" << query.lastError().text();
        return false;
    }

    return true;
}

bool ARTICLE::supprimerArticles(QString ID_ARTICLE)
{
    QSqlQuery query;
    QString res=QString (ID_ARTICLE);
    query.prepare("Delete from ARTICLE where ID_ARTICLE= :ID_ARTICLE ");
    query.bindValue(":ID_ARTICLE",res);
    return query.exec();
}

QSqlQueryModel * ARTICLE::afficherArticle()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM ARTICLE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ARTICLE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_A"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTIONN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("QUANTITE_STOCK"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("TAILLE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("COULEUR"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATE_AJOUT"));

    return model;
}



bool ARTICLE::chercher(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM ARTICLE WHERE ID_ARTICLE = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            this->ID_ARTICLE = query.value("ID_ARTICLE").toString();
            this->NOM_A = query.value("NOM_A").toString();
            this->DESCRIPTIONN = query.value("DESCRIPTIONN").toString();
            this->COULEUR = query.value("COULEUR").toString();
            this->TAILLE = query.value("TAILLE").toString();
            this->QUANTITE_STOCK = query.value("QUANTITE_STOCK").toInt();
            this->CATEGORIE = query.value("CATEGORIE").toString();
            this->TYPE = query.value("TYPE").toString();
            this->DATE_AJOUT = query.value("DATE_AJOUT").toDate();
            this->PRIX = query.value("PRIX").toDouble();

            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool ARTICLE::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE ARTICLE SET "
                  "NOM_A = :nom, "
                  "DESCRIPTIONN = :description, "
                  "COULEUR = :couleur, "
                  "TAILLE = :taille, "
                  "QUANTITE_STOCK = :quantite, "
                  "CATEGORIE = :categorie, "
                  "TYPE = :type, "
                  "DATE_AJOUT = TO_DATE(:date_ajout, 'DD-MM-YYYY'), "
                  "PRIX = :prix "
                  "WHERE ID_ARTICLE = :id");

    query.bindValue(":nom", this->NOM_A);
    query.bindValue(":description", this->DESCRIPTIONN);
    query.bindValue(":couleur", this->COULEUR);
    query.bindValue(":taille", this->TAILLE);
    query.bindValue(":quantite", this->QUANTITE_STOCK);
    query.bindValue(":categorie", this->CATEGORIE);
    query.bindValue(":type", this->TYPE);
    query.bindValue(":date_ajout", this->DATE_AJOUT.toString("dd-MM-yyyy"));
    query.bindValue(":prix", this->PRIX);
    query.bindValue(":id", this->ID_ARTICLE);

    qDebug() << "Attempting to modify article with ID:" << this->ID_ARTICLE;
    qDebug() << "Query being executed: " << query.lastQuery();

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error updating record: " << query.lastError().text();
        return false;  // La mise à jour a échoué
    }
}

bool ARTICLE::estIdentique(const ARTICLE &autre) const {
    return (ID_ARTICLE == autre.ID_ARTICLE &&
            NOM_A.trimmed().toLower() == autre.NOM_A.trimmed().toLower() &&
            DESCRIPTIONN.trimmed() == autre.DESCRIPTIONN.trimmed() &&
            PRIX == autre.PRIX &&
            CATEGORIE.trimmed().toLower() == autre.CATEGORIE.trimmed().toLower() &&
            QUANTITE_STOCK == autre.QUANTITE_STOCK &&
            TAILLE.trimmed().toLower() == autre.TAILLE.trimmed().toLower() &&  // Si TAILLE est une liste, utilisez une comparaison de liste
            QSet<QString>(COULEUR.begin(), COULEUR.end()) == QSet<QString>(autre.COULEUR.begin(), autre.COULEUR.end()) &&
            TYPE.trimmed().toLower() == autre.TYPE.trimmed().toLower() &&
            DATE_AJOUT == autre.DATE_AJOUT);
}


QStringList ARTICLE::genererAlertesModification(const ARTICLE &articleOriginal) const {
    QStringList alertes;

    // Vérification du nom
    if (NOM_A.trimmed().toLower() != articleOriginal.NOM_A.trimmed().toLower()) {
        alertes.append("Nom changé de '" + articleOriginal.NOM_A + "' à '" + NOM_A + "'");
    }
    qDebug() << "Nom actuel : " << NOM_A << " | Nom original : " << articleOriginal.NOM_A;

    // Vérification de la description
    if (DESCRIPTIONN.trimmed() != articleOriginal.DESCRIPTIONN.trimmed()) {
        alertes.append("Description modifiée");
    }
    qDebug() << "Description actuelle : " << DESCRIPTIONN << " | Description originale : " << articleOriginal.DESCRIPTIONN;

    // Vérification de la couleur


    // Traitement de COULEUR, un QSet<QString>
    QSet<QString> couleurSet;
    for (const QString color : COULEUR) {
        couleurSet.insert(color.trimmed().toLower());
    }

    // Traitement de articleOriginal.COULEUR qui est une QStringList
    QSet<QString> couleurOriginalSet;
    for (const QString color : articleOriginal.COULEUR) {
        couleurOriginalSet.insert(color.trimmed().toLower());
    }

    // Comparaison des deux ensembles
    if (couleurSet != couleurOriginalSet) {
        alertes.append("Couleur changée de '" + articleOriginal.COULEUR + "' à '" + COULEUR + "'");
    }


    qDebug() << "Couleur actuelle : " << COULEUR << " | Couleur originale : " << articleOriginal.COULEUR;

    // Vérification des tailles
    QStringList currentTailles = TAILLE.split(",", Qt::SkipEmptyParts);
    QStringList originalTailles = articleOriginal.TAILLE.split(",", Qt::SkipEmptyParts);

    currentTailles.sort();
    originalTailles.sort();

    if (currentTailles != originalTailles) {
        alertes.append("Taille(s) modifiée(s)");
    }
    qDebug() << "Tailles actuelles : " << currentTailles.join(", ") << " | Tailles originales : " << originalTailles.join(", ");

    // Vérification de la quantité en stock
    if (QUANTITE_STOCK != articleOriginal.QUANTITE_STOCK) {
        alertes.append("Quantité en stock modifiée");
    }
    qDebug() << "Quantité actuelle : " << QUANTITE_STOCK << " | Quantité originale : " << articleOriginal.QUANTITE_STOCK;

    // Vérification de la catégorie
    if (CATEGORIE.trimmed().toLower() != articleOriginal.CATEGORIE.trimmed().toLower()) {
        alertes.append("Catégorie changée de '" + articleOriginal.CATEGORIE + "' à '" + CATEGORIE + "'");
    }
    qDebug() << "Catégorie actuelle : " << CATEGORIE << " | Catégorie originale : " << articleOriginal.CATEGORIE;

    // Vérification du prix
    if (PRIX != articleOriginal.PRIX) {
        alertes.append("Prix modifié");
    }
    qDebug() << "Prix actuel : " << PRIX << " | Prix original : " << articleOriginal.PRIX;

    // Vérification de la date d'ajout
    if (DATE_AJOUT != articleOriginal.DATE_AJOUT) {
        alertes.append("Date d'ajout modifiée");
    }
    qDebug() << "Date d'ajout actuelle : " << DATE_AJOUT.toString() << " | Date d'ajout originale : " << articleOriginal.DATE_AJOUT.toString();

    return alertes;
}

