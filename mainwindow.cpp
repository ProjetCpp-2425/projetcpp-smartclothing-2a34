#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transaction.h"
#include <QMessageBox>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableView->setModel(transactionModel.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_ajouter_clicked() {
    int IDTRANSACTION = ui->l1->text().toInt();
    if (ui->l1->text().length() != 8 || IDTRANSACTION == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide de longueur 8 non null.");
        return;
    }

    QDateTime DATEHEUREAJOUT = ui->date->dateTime();
    QString LISTEARTICLES = ui->l3->text();

    bool istaxesFloat = false;
    float taxes = ui->l4->text().toFloat(&istaxesFloat);
    if (!istaxesFloat) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant de taxes valide sous forme de float.");
        return;
    }


    bool isreductionFloat = false;
    float reduction = ui->l6->text().toFloat(&isreductionFloat);
    if (!isreductionFloat) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant de réduction valide sous forme de float.");
        return;
    }

    float montant = ui->l2->value();
    QString METHODEPAIEMENT = ui->box->currentText();

    if (transactionModel.ajouter(IDTRANSACTION, DATEHEUREAJOUT, LISTEARTICLES, taxes, reduction, montant, METHODEPAIEMENT)) {
        ui->tableView->setModel(transactionModel.afficher());
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

        QMessageBox::information(this, QObject::tr("Succès"),
                                 QObject::tr("Suppression effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("La suppression a échoué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_clicked() {
    int IDTRANSACTION = ui->l1->text().toInt();
    if (ui->l1->text().length() != 8 || IDTRANSACTION == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide de longueur 8 non null.");
        return;
    }

    QDateTime DATEHEUREAJOUT = ui->date->dateTime();
    QString LISTEARTICLES = ui->l3->text();

    bool istaxesFloat = false;
    float taxes = ui->l4->text().toFloat(&istaxesFloat);
    if (!istaxesFloat) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant de taxes valide sous forme de float.");
        return;
    }

    bool isreductionFloat = false;
    float reduction = ui->l6->text().toFloat(&isreductionFloat);
    if (!isreductionFloat) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant de réduction valide sous forme de float.");
        return;
    }

    float montant = ui->l2->value();
    QString METHODEPAIEMENT = ui->box->currentText();

    if (transactionModel.modifier(IDTRANSACTION, DATEHEUREAJOUT, LISTEARTICLES, taxes, reduction, montant, METHODEPAIEMENT)) {
        ui->tableView->setModel(transactionModel.afficher());
        QMessageBox::information(this, "Succès", "Transaction modifiée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la modification de la transaction.");
    }
}


