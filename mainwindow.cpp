#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QStandardItemModel>
#include <QDebug>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include<QDir>
#include <QProcess>
#include "vocale.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),vocaleHandler(new Vocale(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(transactionModel.afficher());
    // Connexion du signal textCaptured au QTextEdit

    connect(vocaleHandler, &Vocale::textCaptured, this, [this](QString text) {
        qDebug() << "Captured text: " << text;  // Débogage
        ui->voc_text->append(text);  // Ajouter uniquement le texte reconnu dans le champ
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete vocaleHandler;
}
void MainWindow::on_ajouter_clicked() {
    // Validation de l'ID de transaction
    int idTransaction = ui->l1->text().toInt();
    if (idTransaction <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide, positif et non nul.");
        return;
    }

    // Vérification de l'unicité de l'ID de transaction
    Transaction newTransaction;
    if (newTransaction.existeDeja(idTransaction)) {
        QMessageBox::warning(this, "Erreur", "L'ID de transaction existe déjà. Veuillez en entrer un autre.");
        return;
    }

    // Validation du CIN
    int cin = ui->l7_2->text().toInt();
    if (ui->l7_2->text().length() != 8 || cin <= 0) {
        QMessageBox::warning(this, "Erreur", "Le CIN doit être un entier de 8 chiffres.");
        return;
    }

    // Validation de la liste des articles
    QString listeArticles = ui->l3->text();
    if (listeArticles.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une liste d'articles valide.");
        return;
    }

    // Validation des taxes (flottant positif)
    bool isTaxesFloat;
    float taxes = ui->l4->text().toFloat(&isTaxesFloat);
    if (!isTaxesFloat || taxes < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une taxe valide, positive et sous forme de flottant.");
        return;
    }

    // Validation de la réduction (flottant positif)
    bool isReductionFloat;
    float reduction = ui->l6->text().toFloat(&isReductionFloat);
    if (!isReductionFloat || reduction < 0 || reduction >100) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une réduction valide, positive, <100 et sous forme de flottant.");
        return;
    }

    // Validation du montant (flottant positif)
    bool isMontantFloat;
    float montant = ui->l2->text().toFloat(&isMontantFloat);
    if (!isMontantFloat || montant < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant valide, positif et sous forme de flottant.");
        return;
    }

    // Validation du status (0 ou 1)
    int status = ui->l8->text().toInt();
    if (status != 0 && status != 1) {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 0 ou 1.");
        return;
    }

    // Validation de la date
    QDateTime dateAjout = ui->date->dateTime();
    // Validation de la méthode de paiement (doit être sélectionnée)
    QString methodePaiement = ui->box->currentText();
    if (methodePaiement.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une méthode de paiement.");
        return;
    }

    // Si tout est valide, on appelle la méthode d'ajout
    if (newTransaction.ajouter(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status)) {
        ui->tableView->setModel(transactionModel.afficher());
        transactionModel.addToHistory("Ajouter",idTransaction);
        QMessageBox::information(this, "Succès", "Transaction ajoutée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de la transaction.");
    }
}

void MainWindow::on_supprimer_clicked() {
    int IDTRANSACTION = ui->l7->text().toInt();

    bool test = transactionModel.supprimer(IDTRANSACTION);

    if (test) {

        ui->tableView->setModel(transactionModel.afficher());
        transactionModel.addToHistory("Supprimer",IDTRANSACTION);

        QMessageBox::information(this, QObject::tr("Succès"),
                                 QObject::tr("Suppression effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("La suppression a échoué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_clicked() {
    // Récupération de l'ID de transaction
    int idTransaction = ui->l7->text().toInt();
    qDebug() << "ID de transaction récupéré :" << idTransaction;
    if (idTransaction <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide, positif et non nul.");
        return;
    }

    Transaction transactionTemp;
    if (!transactionTemp.existeDeja(idTransaction)) {
        QMessageBox::warning(this, "Erreur", "L'ID de transaction n'existe pas. Veuillez vérifier l'ID.");
        qDebug() << "L'ID de transaction n'a pas été trouvé dans la base de données.";
        return;
    }

    // Récupérer les autres champs de la transaction
    QString listeArticles = ui->l3->text();
    if (listeArticles.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une liste d'articles valide.");
        return;
    }

    bool isTaxesFloat;
    float taxes = ui->l4->text().toFloat(&isTaxesFloat);
    if (!isTaxesFloat || taxes < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une taxe valide, positive et sous forme de flottant.");
        return;
    }

    bool isReductionFloat;
    float reduction = ui->l6->text().toFloat(&isReductionFloat);
    if (!isReductionFloat || reduction < 0 || reduction > 100) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une réduction valide, positive et sous forme de flottant (et inférieure à 100).");
        return;
    }

    bool isMontantFloat;
    float montant = ui->l2->text().toFloat(&isMontantFloat);
    if (!isMontantFloat || montant < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant valide, positif et sous forme de flottant.");
        return;
    }

    int cin = ui->l7_2->text().toInt();
    if (ui->l7_2->text().length() != 8 || cin <= 0) {
        QMessageBox::warning(this, "Erreur", "Le CIN doit être un entier de 8 chiffres.");
        return;
    }

    int status = ui->l8->text().toInt();
    if (status != 0 && status != 1) {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 0 ou 1.");
        return;
    }

    QDateTime dateAjout = ui->date->dateTime();
    QString methodePaiement = ui->box->currentText();
    if (methodePaiement.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une méthode de paiement.");
        return;
    }

    // Création d'un objet Transaction et mise à jour dans la base de données
    Transaction updatedTransaction(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status);
    // Appel de la fonction modifier en lui passant tous les arguments nécessaires
    bool success = updatedTransaction.modifier(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status);

    if (success) {
        transactionModel.addToHistory("modifier",idTransaction);
        ui->tableView->setModel(transactionModel.afficher());  // Mettre à jour l'affichage des transactions
        QMessageBox::information(this, "Succès", "Transaction modifiée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la modification de la transaction.");
    }
}
void MainWindow::on_pdf_clicked() {
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichier.isEmpty()) {
        // Modèle de données des transactions
        QSqlQueryModel *model = transactionModel.afficher();  // Assurez-vous que vous avez une fonction afficher() qui renvoie un QSqlQueryModel

        // Appel de la méthode pour exporter au format PDF
        Transaction transaction;
        transaction.exporterPDF(nomFichier, model);

        // Libération de la mémoire
        delete model;
        transactionModel.addToHistory("PDF",0);
    }
}
void MainWindow::on_tri_clicked() {
    // Créer un modèle trié par date (récent -> ancien)
    QSqlQueryModel *model = transactionModel.trierParDate();  // Utilisez la fonction trierParDate de votre modèle

    // Vérifiez si des données sont présentes dans le modèle
    if (model && model->rowCount() > 0) {
        // Mettre à jour la table avec les données triées
        ui->tableView->setModel(model);
        transactionModel.addToHistory("Trier",0);
        QMessageBox::information(this, "Tri par Date", "Transactions triées du plus récent au plus ancien.");
    } else {
        // Affiche un message si aucune donnée n'est trouvée
        QMessageBox::warning(this, "Aucune donnée", "Aucune transaction trouvée.");
    }
}
void MainWindow::on_rechercher_clicked() {
    int idTransaction = ui->recherche->text().toInt();  // Récupérer l'ID de transaction depuis l'interface
    if (idTransaction == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (entier) pour la recherche.");
        return;
    }

    // Appeler la fonction rechercher avec l'ID de transaction
    QSqlQueryModel* model = transactionModel.rechercher(idTransaction);

    if (model && model->rowCount() > 0) {
        // Si des résultats sont trouvés, les afficher dans le QTableView
        ui->tableView->setModel(model);
        transactionModel.addToHistory("Rechercher",idTransaction);
        QMessageBox::information(this, "Recherche réussie", "La transaction a été trouvée.");
    } else {
        // Si aucun résultat n'est trouvé
        QMessageBox::warning(this, "Erreur", "La transaction n'a pas été trouvée dans la base de données.");
        delete model;  // Libérer la mémoire si aucun résultat
    }
}
void MainWindow::on_statistiqueButtonTransaction_clicked() {
    QMap<QString, double> stats = transactionModel.statistiquesParStatut();

    // Calculer le total des transactions
    double totalTransactions = 0;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        totalTransactions += it.value();
    }

    // Vider le layout avant d'ajouter un nouveau graphique
    QLayoutItem* item;
    while ((item = ui->transactionLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Créer un pie series pour le graphique
    QPieSeries *series = new QPieSeries();

    // Ajouter les données de statut dans le graphique avec le pourcentage
    int index = 0;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it, ++index) {
        QString label = QString("%1: %2%").arg(it.key()).arg(it.value(), 0, 'f', 1);
        QPieSlice *slice = series->append(label, it.value());

        // Appliquer des couleurs personnalisées
        if (index == 0) {
            slice->setBrush(QColor(212, 153, 162)); // Couleur pour le premier segment
        } else if (index == 1) {
            slice->setBrush(QColor(209, 168, 213)); // Couleur pour le second segment
        }
    }

    // Créer un graphique à partir de la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des transactions par statut");

    // Créer un chart view pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Améliorer l'anti-aliasing

    // Afficher le graphique dans le layout
    ui->transactionLayout->addWidget(chartView);
    transactionModel.addToHistory("Statistique",0);

}

void MainWindow::afficherHistoriqueTransaction() {
    QString cheminFichier = "C:/Users/elbootic.com/Documents/transactionCRUD/historique_transaction.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier d'historique des transactions.");
        return;
    }

    QTextStream in(&file);
    QString historique = in.readAll();
    file.close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Historique des transactions");
    msgBox.setText(historique);
    msgBox.exec();
}

void MainWindow::on_pb_historiqueTransaction_clicked() {
    QString cheminFichier = "C:/Users/elbootic.com/Documents/transactionCRUD/historique_transaction.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
    QMessageBox::information(this, "Historique", "Les actions ont été enregistrées dans l'historique des transactions.");
}



void MainWindow::on_stop_voc_clicked()
{
    qDebug() << "Stop vocale button clicked.";  // Afficher un message lorsque le bouton stop est cliqué
    vocaleHandler->stopAudioCapture();  // Arrêter la capture audio
}


void MainWindow::on_vocale_clicked()
{

    qDebug() << "Vocale button clicked.";  // Afficher un message lorsque le bouton vocale est cliqué
    vocaleHandler->startAudioCapture();  // Démarrer la capture audio
}

