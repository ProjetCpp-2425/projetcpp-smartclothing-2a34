#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->ajoute_employe, &QPushButton::clicked, this, &MainWindow::on_ajoute_employe_clicked);



    connect(ui->buttonToEmploye, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->buttonToProduit, &QPushButton::clicked, this, &MainWindow::navigateToProduit);
    connect(ui->buttonToClient, &QPushButton::clicked, this, &MainWindow::navigateToClient);
    connect(ui->buttonToTransaction, &QPushButton::clicked, this, &MainWindow::navigateToTransaction);
    connect(ui->buttonToAcceuil,&QPushButton::clicked,this,&MainWindow::on_buttonToAcceuil_clicked);

    connect(ui->buttonToEmploye_1, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->buttonToProduit_1, &QPushButton::clicked, this, &MainWindow::navigateToProduit);
    connect(ui->buttonToClient_1, &QPushButton::clicked, this, &MainWindow::navigateToClient);
    connect(ui->buttonToTransaction_1, &QPushButton::clicked, this, &MainWindow::navigateToTransaction);

    //connect(ui->buttonToAcceuil_2,&QPushButton::clicked,this,&MainWindow::on_buttonToAcceuil_clicked);
    connect(ui->buttonToAcceuil_3,&QPushButton::clicked,this,&MainWindow::on_buttonToAcceuil_clicked);
    connect(ui->buttonToAcceuil_4,&QPushButton::clicked,this,&MainWindow::on_buttonToAcceuil_clicked);
    connect(ui->buttonToAcceuil_5,&QPushButton::clicked,this,&MainWindow::on_buttonToAcceuil_clicked);
    connect(ui->buttonToEmploye_4, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->buttonToProduit_4, &QPushButton::clicked, this, &MainWindow::navigateToProduit);
    connect(ui->buttonToClient_4, &QPushButton::clicked, this, &MainWindow::navigateToClient);
    connect(ui->buttonToTransaction_4, &QPushButton::clicked, this, &MainWindow::navigateToTransaction);






    connect(ui->retour, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_2, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_3, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_4, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_5, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_6, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);





    connect(ui->buttonToEmploye_2, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->buttonToProduit_2, &QPushButton::clicked, this, &MainWindow::navigateToProduit);
    connect(ui->buttonToClient_2, &QPushButton::clicked, this, &MainWindow::navigateToClient);
    connect(ui->buttonToTransaction_2, &QPushButton::clicked, this, &MainWindow::navigateToTransaction);


    connect(ui->buttonToEmploye_3, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->buttonToProduit_3, &QPushButton::clicked, this, &MainWindow::navigateToProduit);
    connect(ui->buttonToClient_3, &QPushButton::clicked, this, &MainWindow::navigateToClient);
    connect(ui->buttonToTransaction_3, &QPushButton::clicked, this, &MainWindow::navigateToTransaction);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_buttonToAcceuil_clicked);

    connect(ui->buttonsupp, &QPushButton::clicked, this, &MainWindow::onSupprimerClicked);
    connect(ui->loadbutton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(ui->buttonmodifier, &QPushButton::clicked, this, &MainWindow::onModifyButtonClicked);
    connect(ui->buttonanuuler_2, &QPushButton::clicked, this, &MainWindow::clear);






    ui->sort->show();
    ui->salaire->hide();
    ui->date_em->hide();
    ui->nom->hide();
    connect(ui->sort,&QPushButton::clicked,this,&MainWindow::sortclicked);


    connect(ui->validerButton, &QPushButton::clicked, this, &MainWindow::onAjouterClicked);


    connect(ui->pushButton_24, &QPushButton::clicked, this, &MainWindow::on_pushButton_24_clicked);
    connect(ui->pushButton_25, &QPushButton::clicked, this, &MainWindow::on_pushButton_25_clicked);
    connect(ui->pushButton_26, &QPushButton::clicked, this, &MainWindow::on_pushButton_26_clicked);
    connect(ui->pushButton_27, &QPushButton::clicked, this, &MainWindow::on_pushButton_27_clicked);
    connect(ui->annuler,&QPushButton::clicked,this,&MainWindow::on_annuler_clicked);





    ui->graphicsView_6->hide();
    ui->labelposte1->hide();
    ui->labelposte2->hide();
    ui->labelposte3->hide();
    ui->labelposte4->hide();
    ui->labelposte5->hide();
    ui->widget_47->hide();
    ui->label_216->hide();
    employeModel = new QSqlQueryModel(this);
    afficherEmployes();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::navigateToEmploye() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::navigateToProduit() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::navigateToClient() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::navigateToTransaction() {
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_buttonToAcceuil_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void MainWindow::on_ajoute_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);

}
void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

}

void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

}
void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);

}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);

}
void MainWindow::on_modifier_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_annuler_clicked()
{
    ui->nameLineEdit->clear();
    ui->prenomLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->cinLineEdit->clear();
    ui->posteComboBox->setCurrentIndex(0);
    ui->salaireComboBox->setCurrentIndex(0);
    ui->dateEmbaucheLineEdit->clear();
    ui->dateNaissanceLineEdit->clear();
    ui->presenceComboBox->setCurrentIndex(0);;
    ui->suppLineEdit->clear();
    ui->message->clear();
}
void MainWindow::sortclicked()
{
    if(    ui->salaire->isVisible()&&  ui->date_em->isVisible(); ui->nom->isVisible()){
        ui->salaire->hide();
        ui->date_em->hide();
        ui->nom->hide();
    }
    else{
        ui->salaire->show();
        ui->date_em->show();
        ui->nom->show();
    }


}

void MainWindow::onAjouterClicked() {
    QString Id_employe = ui->cinLineEdit->text();
    QString nom = ui->nameLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString email = ui->emailLineEdit->text();
    int telephone = ui->phoneLineEdit->text().toInt();
    QString poste = ui->posteComboBox->currentText();
    double salaire = ui->salaireComboBox->currentText().toDouble();
    QString presence = ui->presenceComboBox->currentText();
    double suppl = ui->suppLineEdit->text().toDouble();
    QString dateNaissance = ui->dateNaissanceLineEdit->text();
    QString dateEmbauche = ui->dateEmbaucheLineEdit->text();

    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Id_employe:" << Id_employe;
    qDebug() << "Poste:" << poste;
    qDebug() << "Salaire:" << salaire;
    qDebug() << "Presence:" << presence;
    qDebug() << "Suppl:" << suppl;
    qDebug() << "Date Naissance:" << dateNaissance;
    qDebug() << "Date Embauche:" << dateEmbauche;

    Employe employe(nom, prenom, email, telephone, Id_employe, poste, salaire, presence, suppl, dateNaissance, dateEmbauche);

    if (employe.ajouter()) {
        afficherEmployes();
    } else {
        QMessageBox::warning(this, "Erreur", "L'ajout de l'employé a échoué.");
    }
}

void MainWindow::afficherEmployes() {
    employeModel->setQuery("SELECT * FROM EMPLOYE");
    ui->tableView->setModel(employeModel);
}

void MainWindow::onSupprimerClicked() {
    QString Id_employe = ui->lineEditsupp->text();

    if (Id_employe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un Id_employe valide.");
        return;
    }

    Employe employe("", "", "", 0, Id_employe, "", 0.0, "", 0.0, "", "");
    if(employe.load()){
    if (employe.supprimer()) {
        afficherEmployes();
        ui->lineEditsupp->clear();
    } else {
        QMessageBox::warning(this, "Erreur", "La suppression de l'employé a échoué.");
    }
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to load employee data. Please check the ID.");
    }
}


void MainWindow::onLoadButtonClicked() {
    QString Id_employe = ui->lineEditmod->text();

    Employe employe;
    employe.setIdEmploye(Id_employe);

    if (employe.load()) {
         employe.setIdEmploye(ui->lineEditcinModif->text());
        ui->lineEditNomModif->setText(employe.getNom());
        ui->lineEditPrenomModif->setText(employe.getPrenom());
        ui->lineEditEmailModif->setText(employe.getEmail());
        ui->lineEditcinModif->setText(ui->lineEditmod->text());
        ui->lineEditTelephoneModif->setText(QString::number(employe.getTelephone()));
        ui->posteComboBoxModif->setCurrentText(employe.getPoste());
        ui->salaireComboBoxModif->setCurrentText(QString::number(employe.getSalaire()));
        ui->presenceComboBoxModif->setCurrentText(employe.getPresence());
        ui->lineEditSuppModif->setText(QString::number(employe.getHeuresSupplementaires()));
        QString dateNaissanceStr = employe.getDateNaissance().split("T").first();
        QString dateEmbaucheStr = employe.getDateEmbauche().split("T").first();

        QDate dateNaissance = QDate::fromString(dateNaissanceStr, "yyyy-MM-dd");
        QDate dateEmbauche = QDate::fromString(dateEmbaucheStr, "yyyy-MM-dd");

            ui->dateNaissanceEditModif->setDate(dateNaissance);


            ui->dateEmbaucheEditModif->setDate(dateEmbauche);

    } else {
        QMessageBox::warning(this, "Error", "Failed to load employee data. Please check the ID.");
    }
}

void MainWindow::onModifyButtonClicked() {
    QString Id_employe = ui->lineEditmod->text();

    Employe employe;
    employe.setIdEmploye(Id_employe);

    employe.setNom(ui->lineEditNomModif->text());
    employe.setPrenom(ui->lineEditPrenomModif->text());
    employe.setEmail(ui->lineEditEmailModif->text());
    employe.setTelephone(ui->lineEditTelephoneModif->text().toInt());
    employe.setPoste(ui->posteComboBoxModif->currentText());
    employe.setSalaire(ui->salaireComboBoxModif->currentText().toDouble());
    employe.setPresence(ui->presenceComboBoxModif->currentText());
    employe.setHeuresSupplementaires(ui->lineEditSuppModif->text().toDouble());
    employe.setDateNaissance(ui->dateNaissanceEditModif->date().toString("yyyy-MM-dd"));
    employe.setDateEmbauche(ui->dateEmbaucheEditModif->date().toString("yyyy-MM-dd"));

    if (employe.modifier()) {
        clear();
        afficherEmployes();
        QMessageBox::information(this, "Succès", "Modification réussie.");
    } else {
        QMessageBox::warning(this, "Erreur", "La modification de l'employé a échoué.");
    }
}
void MainWindow::clear(){
    ui->lineEditmod->clear();
    ui->lineEditcinModif->clear();
    ui->lineEditNomModif->clear();
    ui->lineEditPrenomModif->clear();
    ui->lineEditEmailModif->clear();
    ui->lineEditTelephoneModif->clear();
    ui->posteComboBoxModif->setCurrentIndex(0);
    ui->salaireComboBoxModif->setCurrentIndex(0);
    ui->presenceComboBoxModif->setCurrentIndex(0);
    ui->lineEditSuppModif->clear();
    ui->dateNaissanceEditModif->setDate(QDate::currentDate());
    ui->dateEmbaucheEditModif->setDate(QDate::currentDate());
}





