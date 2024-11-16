#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QXlsx/QXlsx/header\xlsxdocument_p.h>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QTime>
#include <QMap>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QtNetwork>
#include <QBrush>
#include <QColor>
#include <QPropertyAnimation>
#include <QTime>

#include <QRandomGenerator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);



    ui->stackedWidgetSign->setCurrentIndex(0);
    ui->stackedWidgetlogin->setCurrentIndex(0);


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




    initializeStackedWidgetSignPages();

    connect(ui->retour, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
    connect(ui->retour_2, &QPushButton::clicked, this, &MainWindow::navigateToEmploye);
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

    connect(ui->buttonsupp, &QPushButton::clicked, this, &MainWindow::onSupprimerClicked);
    connect(ui->loadbutton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);

    connect(ui->buttonmodifier, &QPushButton::clicked, this, &MainWindow::onModifyButtonClicked);
    connect(ui->buttonanuuler_2, &QPushButton::clicked, this, &MainWindow::clear);

    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &MainWindow::onSearchCriteriaChanged);
    connect(ui->comboBoxSearchCriteria, &QComboBox::currentIndexChanged, this, &MainWindow::onSearchCriteriaChanged);


        connect(ui->statistique,&QPushButton::clicked,this,&MainWindow::displayPosteStatistics);
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(updateDateInTextEdit()));

        connect(ui->loadcongebutton, &QPushButton::clicked, this, &MainWindow::loadconge);
    connect(ui->envoyerdemande, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);


    ui->stackedWidgetSign->show();
    ui->stackedWidgetlogin->hide();
    ui->sort->show();
    ui->salaire->hide();
    ui->date_em->hide();
    ui->nom->hide();
    connect(ui->sort,&QPushButton::clicked,this,&MainWindow::sortclicked);

    connect(ui->salaire,&QPushButton::clicked,this,&MainWindow::sortBySalary);
    connect(ui->date_em,&QPushButton::clicked,this,&MainWindow::sortByHireDate);
    connect(ui->nom,&QPushButton::clicked,this,&MainWindow::sortByName);



    connect(ui->validerButton, &QPushButton::clicked, this, &MainWindow::onAjouterClicked);


    connect(ui->pushButton_24, &QPushButton::clicked, this, &MainWindow::on_pushButton_24_clicked);
    connect(ui->pushButton_26, &QPushButton::clicked, this, &MainWindow::on_pushButton_26_clicked);
    connect(ui->pushButton_27, &QPushButton::clicked, this, &MainWindow::on_pushButton_27_clicked);
    connect(ui->annuler,&QPushButton::clicked,this,&MainWindow::on_annuler_clicked);


    connect(ui->excel,&QPushButton::clicked,this,&MainWindow::generateExcelReport);

    connect(ui->accepterconge,&QPushButton::clicked,this,&MainWindow::on_acceptButton_clicked);

    connect(ui->refuserconge,&QPushButton::clicked,this,&MainWindow::on_refuseButton_clicked);

    connect(ui->connecter,&QPushButton::clicked,this,&MainWindow::on_connecter_clicked);
    connect(ui->envoyercode,&QPushButton::clicked,this,&MainWindow::on_sendSmsButton_clicked);
    connect(ui->newmdp,&QPushButton::clicked,this,&MainWindow::on_updatePasswordButton_clicked);
    connect(ui->mdpoublier,&QPushButton::clicked,this,&MainWindow::mdpoublier);

    connect(ui->mdpchanger,&QPushButton::clicked,this,&MainWindow::on_verifyCodeButton_clicked);


    ui->label_169->hide();
    ui->tableViewConge->hide();
    ui->accepterconge->hide();
    ui->refuserconge->hide();

    ui->textEdit_congeDescription->hide();
    ui->calendarWidget->hide();

    ui->labelposte1->hide();
    ui->labelposte2->hide();
    ui->labelposte3->hide();
    ui->labelposte4->hide();
    ui->labelposte5->hide();
    ui->label_216->show();
    employeModel = new QSqlQueryModel(this);
    afficherEmployes();
    displaydemandeconge();
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


void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);

}
void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);

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
    QString description;
    QString motedepass="000";


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

    Employe employe(nom, prenom, email, telephone, Id_employe, poste, salaire, presence, suppl, dateNaissance, dateEmbauche,description,motedepass);
    if(ui->checkBox_3->isChecked()){
      if (employe.ajouter()) {
        afficherEmployes();
        ui->cinLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->prenomLineEdit->clear();
        ui->emailLineEdit->clear();
        ui->phoneLineEdit->clear();
        ui->posteComboBox->setCurrentIndex(0);
        ui->salaireComboBox->setCurrentIndex(0);
        ui->suppLineEdit->clear();
        ui->dateNaissanceLineEdit->setDate(QDate::currentDate());
        ui->dateEmbaucheLineEdit->setDate(QDate::currentDate());
    } else {
        QMessageBox::warning(this, "Erreur", "L'ajout de l'employé a échoué.");
    }
    }else{
        QMessageBox::warning(this, "Erreur", "Veuillez cocher la case avant de continuer.");


    }
}

void MainWindow::afficherEmployes() {
    employeModel->setQuery("SELECT Id_employe, Nom, Prenom, Email, Telephone, Poste, Salaire, Presence,heures_supplementaires, Date_naissance, Date_embauche FROM EMPLOYE");
    ui->tableView->setModel(employeModel);
}

void MainWindow::onSupprimerClicked() {
    QString Id_employe = ui->lineEditsupp->text();

    if (Id_employe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un Id_employe valide.");
        return;
    }

    Employe employe("", "", "", 0, Id_employe, "", 0.0, "", 0.0, "", "","","");
    if(employe.load()){
    if (employe.supprimer()) {
        afficherEmployes();
        ui->lineEditsupp->clear();
    } else {
        QMessageBox::warning(this, "Erreur", "La suppression de l'employé a échoué.");
    }
    }
    else {
        QMessageBox::warning(this, "Erreur", "Échec du chargement des données de l'employé. Veuillez vérifier l'ID.");
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
        QMessageBox::warning(this, "Erreur", "Échec du chargement des données de l'employé. Veuillez vérifier l'ID.");
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

void MainWindow::onSearchCriteriaChanged() {
    QString searchValue = ui->lineEditSearch->text();
    QString criteria = ui->comboBoxSearchCriteria->currentText();

    Employe employe;
    QSqlQueryModel* model = nullptr;

    if (searchValue.isEmpty() && criteria.isEmpty()) {
        qDebug() << "Both search value and criteria are empty, displaying all employees.";
        afficherEmployes();

    }
    else if (criteria == "Recherche un employe a partir de son Prenom" && !searchValue.isEmpty()) {
        model = employe.afficherParPrenom(searchValue);
    }
    else if (criteria == "Recherche un employe a partir de son Poste" && !searchValue.isEmpty()) {
        model = employe.afficherParPoste(searchValue);
    }
    else if (criteria == "Recherche un employe a partir de son ID" && !searchValue.isEmpty()) {
        model = employe.afficherParID(searchValue);
    }
    else {
        afficherEmployes();
    }
    if (model) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

    }
}

void MainWindow::sortBySalary() {
    QSqlQuery query;
    QString queryStr = "SELECT * FROM employe ORDER BY Salaire ASC";
    query.prepare(queryStr);
    if (query.exec()) {
        qDebug() << "Query executed successfully: " << queryStr;

        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

        qDebug() << "Table sorted by Salaire (Salary)";
    } else {
        qDebug() << "Query execution failed: " << query.lastError();
    }
}

void MainWindow::sortByHireDate() {
    QSqlQuery query;
    QString queryStr = "SELECT * FROM employe ORDER BY Date_embauche ASC";
    query.prepare(queryStr);

    if (query.exec()) {
        qDebug() << "Query executed successfully: " << queryStr;

        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

        qDebug() << "Table sorted by Date_embauche (Hire Date)";
    } else {
        qDebug() << "Query execution failed: " << query.lastError();
    }
}

void MainWindow::sortByName() {
    QSqlQuery query;
    QString queryStr = "SELECT * FROM employe ORDER BY Nom ASC";
    query.prepare(queryStr);
    if (query.exec()) {
        qDebug() << "Query executed successfully: " << queryStr;

        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

        qDebug() << "Table sorted by Nom (Name)";
    } else {
        qDebug() << "Query execution failed: " << query.lastError();
    }
}
void MainWindow::generateExcelReport() {
    QSqlQuery query("SELECT * FROM EMPLOYE");


    QXlsx::Document xlsx;

    xlsx.write("A1", "ID Employe");
    xlsx.write("B1", "Nom");
    xlsx.write("C1", "Prenom");
    xlsx.write("D1", "Poste");
    xlsx.write("E1", "Salaire");
    xlsx.write("F1", "Heures Supplémentaires");
    xlsx.write("G1", "Salaire Total");
    xlsx.write("H1", "Email");
    xlsx.write("I1", "Téléphone");
    xlsx.write("J1", "Date de Naissance");
    xlsx.write("K1", "Date d'Embauche");
    xlsx.write("L1", "Présence");

    int row = 2;

    while (query.next()) {
        xlsx.write(row, 1, query.value("Id_employe").toString());
        xlsx.write(row, 2, query.value("Nom").toString());
        xlsx.write(row, 3, query.value("Prenom").toString());
        xlsx.write(row, 4, query.value("Poste").toString());
        xlsx.write(row, 5, query.value("Salaire").toDouble());
        xlsx.write(row, 6, query.value("Heures_supplementaires").toDouble());

        double totalSalary = query.value("Salaire").toDouble() + (query.value("Heures_supplementaires").toDouble() *20 );
        xlsx.write(row, 7, totalSalary);

        xlsx.write(row, 8, query.value("Email").toString());
        xlsx.write(row, 9, query.value("Telephone").toInt());
        xlsx.write(row, 10, query.value("Date_naissance").toString());
        xlsx.write(row, 11, query.value("Date_embauche").toString());

        QString presence = query.value("Presence").toString();
        xlsx.write(row, 12, presence);

        QXlsx::Format format;
        if (presence == "Absent") {
            format.setPatternBackgroundColor(Qt::red);
        } else if (presence == "Present") {
            format.setPatternBackgroundColor(Qt::green);
        } else {
            format.setPatternBackgroundColor(Qt::black);
        }

        xlsx.write(row, 12, presence, format);
        row++;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save Excel File", QDir::homePath(), "Excel Files (*.xlsx)");

    if (!filePath.isEmpty()) {
        bool saved = xlsx.saveAs(filePath);

        if (saved) {
            QMessageBox::information(this, "Exportation réussie", "Fichier Excel exporté avec succès vers :\n" + filePath);
        } else {
            QMessageBox::critical(this, "Export Failed", "Error exporting Excel file.");
        }
    } else {
        QMessageBox::critical(this, "Échec de l'exportation", "Erreur lors de l'exportation du fichier Excel.");
    }
}



QMap<QString, int> MainWindow::getEmployeeCountByPoste() {
    QMap<QString, int> posteData;
    QSqlQuery query;

    query.prepare("SELECT Poste, COUNT(*) FROM EMPLOYE GROUP BY Poste");

    if (query.exec()) {
        while (query.next()) {
            QString poste = query.value(0).toString();
            int count = query.value(1).toInt();
            posteData[poste] = count;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return posteData;
}

void MainWindow::displayPosteStatistics() {

    QMap<QString, int> posteData = getEmployeeCountByPoste();

    if (posteData.isEmpty()) {
        qDebug() << "No data retrieved for poste statistics.";
        return;
    }

    int totalEmployees = 0;
    for (int count : posteData) {
        totalEmployees += count;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = posteData.begin(); it != posteData.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());

        double percentage = (static_cast<double>(it.value()) / totalEmployees) * 100.0;
        slice->setLabel(QString("%1 (%2%)").arg(it.key()).arg(percentage, 0, 'f', 1));
        slice->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Count by Poste");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setBackgroundBrush(QBrush(QColor(251, 251, 243)));
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBrush(QBrush(QColor(251, 251, 243)));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (QLayout *existingLayout = ui->chartPlaceholder->layout()) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->chartPlaceholder);
    layout->addWidget(chartView);
    ui->chartPlaceholder->setLayout(layout);
}
void MainWindow::loadconge(){
        QString Id_employe = ui->lineEditsconge->text();

        Employe employe;
        employe.setIdEmploye(Id_employe);
        if (employe.load()) {
            ui->textEdit_congeDescription->show();
            ui->calendarWidget->show();
            QMessageBox::information(this, "Employé Chargé", "Les informations de l'employé ont été chargées. Veuillez saisir la demande de congé.");
        } else {
            QMessageBox::warning(this, "Erreur", "L'ID de l'employé est invalide.");
            ui->textEdit_congeDescription->hide();
            ui->calendarWidget->hide();
        }
}
void MainWindow::updateDateInTextEdit() {
    QDate selectedDate = ui->calendarWidget->selectedDate();

    QString dateText = selectedDate.toString("dd/MM/yyyy");

    QString existingText = ui->textEdit_congeDescription->toPlainText();
    existingText.append("\n" + dateText);

    ui->textEdit_congeDescription->setPlainText(existingText);
}
void MainWindow::displaydemandeconge() {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("EMPLOYE");
    model->setFilter("description IS NOT NULL");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("ID Employé"));
    model->setHeaderData(1, Qt::Horizontal, tr("Prénom"));
    model->setHeaderData(12, Qt::Horizontal, tr("Description"));

    ui->tableViewConge->setModel(model);
    for (int col = 0; col < model->columnCount(); ++col) {
        if (col != 0 && col != 2 && col != 12) {
            ui->tableViewConge->hideColumn(col);
        }
    }
   ui->tableViewConge->setColumnWidth(12, 700);
}





void MainWindow::on_sendButton_clicked() {
    QString Id_employe = ui->lineEditsconge->text();
    QString description = ui->textEdit_congeDescription->toPlainText();

    Employe employe;
    employe.setIdEmploye(Id_employe);

    if (employe.load()) {
        QString prenom = employe.getPrenom();
        QSqlQuery query;
        query.prepare("UPDATE EMPLOYE SET description = :description WHERE id_employe = :id_employe");
        query.bindValue(":id_employe", Id_employe);
        query.bindValue(":description", description);

        if (query.exec()) {
            displaydemandeconge();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de l'enregistrement de la demande de congé.");
        }
        ui->lineEditsconge->clear();
        ui->textEdit_congeDescription->clear();
        ui->textEdit_congeDescription->hide();
        ui->calendarWidget->hide();
    } else {
        QMessageBox::warning(this, "Erreur", "L'ID de l'employé est invalide.");
    }
}
void MainWindow::sendSms(const QString &phoneNumber, const QString &message) {


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(apiUrl);
    QNetworkRequest request(url);

    QString credentials = accountSid + ":" + authToken;
    QByteArray authData = "Basic " + credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", authData);

    QString formattedPhoneNumber = phoneNumber.startsWith("+") ? phoneNumber : "+216" + phoneNumber;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    qDebug() << "Sending SMS with the following parameters:";
    qDebug() << "From:" << fromPhoneNumber;
    qDebug() << "To:" << formattedPhoneNumber;
    qDebug() << "Message:" << message;

    QByteArray postData;
    postData.append("To=" + formattedPhoneNumber.toUtf8() + "&");
    postData.append("From=" + fromPhoneNumber.toUtf8() + "&");
    postData.append("Body=" + message.toUtf8());

    QNetworkReply *reply = manager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "Succès", "SMS envoyé avec succès !");
        } else {
            QString errorMsg = "Failed to send SMS: " + reply->errorString();
            QByteArray responseBody = reply->readAll();
            if (!responseBody.isEmpty()) {
                errorMsg += "\nResponse: " + QString(responseBody);
            }
            QMessageBox::warning(nullptr, "Erreur", errorMsg);
        }
        reply->deleteLater();
    });
}

void MainWindow::on_acceptButton_clicked() {
    QItemSelectionModel *selection = ui->tableViewConge->selectionModel();
    QModelIndexList selectedIndexes = selection->selectedRows();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une ligne.");
        return;
    }

    int row = selectedIndexes.first().row();
    QString employeeId = ui->tableViewConge->model()->data(ui->tableViewConge->model()->index(row, 0)).toString();

    Employe employe;
    employe.setIdEmploye(employeeId);
    if (employe.load()) {
        int phoneNumber = employe.getTelephone();
        QString phoneNumberStr = QString::number(phoneNumber);
        QString message = "Your leave request has been accepted.";
        sendSms(phoneNumberStr, message);

        clearLeaveRequest(employeeId);
    } else {
        QMessageBox::warning(this, "Erreur", "Détails de l'employé non trouvés.");
    }
}


void MainWindow::on_refuseButton_clicked() {
    QItemSelectionModel *selection = ui->tableViewConge->selectionModel();
    QModelIndexList selectedIndexes = selection->selectedRows();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une ligne.");
        return;
    }

    int row = selectedIndexes.first().row();
    QString employeeId = ui->tableViewConge->model()->data(ui->tableViewConge->model()->index(row, 0)).toString();

    Employe employe;
    employe.setIdEmploye(employeeId);
    if (employe.load()) {
        int phoneNumber = employe.getTelephone();
        QString phoneNumberStr = QString::number(phoneNumber);
        QString message = "Your leave request has been refused.";
        sendSms(phoneNumberStr, message);

        clearLeaveRequest(employeeId);
    } else {
        QMessageBox::warning(this, "Erreur", "Détails de l'employé non trouvés.");
    }
}

void MainWindow::clearLeaveRequest(const QString &employeeId) {
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ui->tableViewConge->model());

    if (model) {
        bool rowFound = false;
        int descriptionColumnIndex = 12;

        for (int row = 0; row < model->rowCount(); ++row) {
            if (model->data(model->index(row, 0)).toString() == employeeId) {
                rowFound = true;
                model->setData(model->index(row, descriptionColumnIndex), "");

                if (model->submitAll()) {
                    model->select();
                }
                break;
            }
        }

        if (!rowFound) {
            QMessageBox::warning(this, "Erreur", "Aucune ligne trouvée avec l'ID d'employé spécifié.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Le modèle n'est pas valide.");
    }
}

void MainWindow::initializeStackedWidgetSignPages() {
    initializePage1();
    initializePage2();
    initializePage3();
    initializePage4();
}

void MainWindow::initializePage1() {
    connect(ui->lineeditnomsign, &QLineEdit::textChanged, this, [this]() {
        bool enableNext = !ui->lineeditnomsign->text().isEmpty() && !ui->lineeditprenomsign->text().isEmpty();
        ui->next1->setEnabled(enableNext);
    });

    connect(ui->lineeditprenomsign, &QLineEdit::textChanged, this, [this]() {
        bool enableNext = !ui->lineeditnomsign->text().isEmpty() && !ui->lineeditprenomsign->text().isEmpty();
        ui->next1->setEnabled(enableNext);
    });

    connect(ui->next1, &QPushButton::clicked, this, [this]() {
        if (!ui->lineeditnomsign->text().isEmpty() && !ui->lineeditprenomsign->text().isEmpty()) {
            ui->stackedWidgetSign->setCurrentIndex(1);
            qDebug() << "Page 1: Transitioning to Page 2";
        }
    });
}

void MainWindow::initializePage2() {
    connect(ui->lineeditemailsign, &QLineEdit::textChanged, this, [this]() {
        validateEmailAndEnableNext();
    });

    connect(ui->dateNaissancesign, &QDateEdit::dateChanged, this, [this]() {
        validateEmailAndEnableNext();
    });

    connect(ui->comboboxpostesign, &QComboBox::currentTextChanged, this, [this]() {
        validateEmailAndEnableNext();
    });

    connect(ui->next2, &QPushButton::clicked, this, [this]() {
        if (validateEmailAndEnableNext()) {
            ui->stackedWidgetSign->setCurrentIndex(2);
            qDebug() << "Page 2: Transitioning to Page 3";
        }
    });
    connect(ui->precedent2, &QPushButton::clicked, this, [this]() {
            ui->stackedWidgetSign->setCurrentIndex(0);

    });

}

bool MainWindow::validateEmailAndEnableNext() {
    bool enableNext = !ui->lineeditemailsign->text().isEmpty() &&
                      !ui->comboboxpostesign->currentText().isEmpty() &&
                      ui->dateNaissancesign->date().isValid();
    ui->next2->setEnabled(enableNext);
    qDebug() << "Email:" << ui->lineeditemailsign->text()
             << "Poste:" << ui->comboboxpostesign->currentText()
             << "Date Naissance:" << ui->dateNaissancesign->date().toString()
             << "Next button enabled:" << enableNext;
    return enableNext;
}

void MainWindow::initializePage3() {
    connect(ui->lineedittelephonesign, &QLineEdit::textChanged, this, [this]() {
        validateTelephoneAndPassword();
    });

    connect(ui->lineeditmdpsign, &QLineEdit::textChanged, this, [this]() {
        validateTelephoneAndPassword();
    });

    connect(ui->next3, &QPushButton::clicked, this, [this]() {
        if (validateTelephoneAndPassword()) {
            ui->stackedWidgetSign->setCurrentIndex(3);
            qDebug() << "Page 3: Transitioning to Page 4";
        }
    });
    connect(ui->precedent3, &QPushButton::clicked, this, [this]() {
            ui->stackedWidgetSign->setCurrentIndex(1);

    });
}

bool MainWindow::validateTelephoneAndPassword() {
    bool enableNext = !ui->lineedittelephonesign->text().isEmpty() && !ui->lineeditmdpsign->text().isEmpty();
    ui->next3->setEnabled(enableNext);
    qDebug() << "Telephone:" << ui->lineedittelephonesign->text()
             << "Mot de Passe:" << ui->lineeditmdpsign->text()
             << "Next button enabled:" << enableNext;
    return enableNext;
}

void MainWindow::initializePage4() {
    QString generatedId = generateUniqueId();
    ui->idlabel->setText(generatedId);
    qDebug() << "Generated ID: " << generatedId;

    connect(ui->sincrire, &QPushButton::clicked, this, [this]() {
        saveNewEmployeeSign();
    });
    connect(ui->precedent3, &QPushButton::clicked, this, [this]() {
            ui->stackedWidgetSign->setCurrentIndex(2);

    });
}

QString MainWindow::generateUniqueId() {
    QSqlQuery query;
    query.exec("SELECT MAX(Id_employe) FROM EMPLOYE");
    query.next();
    int randomId = QRandomGenerator::global()->bounded(10000000, 99999999);

    return QString::number(randomId);
}

void MainWindow::saveNewEmployeeSign() {
    QString Id_employe = ui->idlabel->text();
    QString nom = ui->lineeditnomsign->text();
    QString prenom = ui->lineeditprenomsign->text();
    QString email = ui->lineeditemailsign->text();

    QString phoneText = ui->lineedittelephonesign->text();
    bool ok;
    int telephone = phoneText.toInt(&ok);
    if (!ok || phoneText.isEmpty()) {
        QMessageBox::warning(this, "Numéro de téléphone invalide", "Veuillez entrer un numéro de téléphone valide.");
        return;
    }

    QString poste = ui->comboboxpostesign->currentText();
    QString dateNaissance = ui->dateNaissancesign->text();



    QDate dateEmbauche = QDate::currentDate();

    QString dateEmbaucheStr = dateEmbauche.toString("dd/MM/yyyy");

    QString motedepass = ui->lineeditmdpsign->text();
    QString presence = "Present";
    double salaire = 100;
    double suppl = 0.0;
    QString description;

    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Id_employe:" << Id_employe;
    qDebug() << "Poste:" << poste;
    qDebug() << "Date Naissance:" << dateNaissance;
    qDebug() << "Date Embauche:" << dateEmbaucheStr;
    qDebug() << "Mot de Passe:" << motedepass;

    Employe employe(nom, prenom, email, telephone, Id_employe, poste, salaire, presence, suppl, dateNaissance, dateEmbaucheStr,description,motedepass);

    if (employe.ajouter()) {
        afficherEmployes();
        QMessageBox::information(this, "Success", "L'employé a été ajouté avec succès!");
        ui->stackedWidget->setCurrentIndex(1);

        ui->lineeditnomsign->clear();
        ui->lineeditprenomsign->clear();
        ui->lineeditemailsign->clear();
        ui->lineedittelephonesign->clear();
        ui->comboboxpostesign->setCurrentIndex(0);
        ui->lineeditmdpsign->clear();
        ui->idlabel->clear();
        ui->dateNaissancesign->setDate(QDate::currentDate());
    } else {
        QMessageBox::warning(this, "Erreur", "L'ajout de l'employé a échoué.");
        ui->stackedWidgetSign->setCurrentIndex(0);

    }
}
void MainWindow::on_connecter_clicked()
{
    QString idEmploye = ui->telephonelogin->text();
    QString password = ui->mdplogin->text();

    if (idEmploye.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID de l'employé et le mot de passe.");
        return;
    }
    Employe employe;
    employe.setIdEmploye(idEmploye);
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE ID_EMPLOYE = :idEmploye AND MOTEDEPASS = :motedepasse");
    query.bindValue(":idEmploye", idEmploye);
    query.bindValue(":motedepasse", password);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur de la requête SQL.");
        return;
    }
    QString dbPassword = query.value("MOTEDEPASS").toString();
    qDebug() << "Password from DB: " << dbPassword;
    if (query.next()) {
        QString nom = query.value("Nom").toString();
        QString prenom = query.value("Prenom").toString();
         ui->telephonelogin->clear();
        ui->mdplogin->clear();
         ui->smsmdp->clear();
        ui->newmdplineedit->clear();
        QMessageBox::information(this, "Connexion réussie", "Bienvenue, " + nom + " " + prenom);
        ui->stackedWidget->setCurrentIndex(1);

    } else {
        QMessageBox::warning(this, "Erreur", "ID de l'employé ou mot de passe incorrect.");
    }

}

void MainWindow::on_deja1_clicked()
{
    ui->stackedWidgetSign->hide();
    ui->stackedWidgetlogin->show();
    ui->label_216->hide();

}


void MainWindow::on_navez_clicked()
{
    ui->stackedWidgetSign->show();
    ui->stackedWidgetlogin->hide();
    ui->label_216->show();

}


void MainWindow::mdpoublier(){

     ui->stackedWidgetlogin->setCurrentIndex(1);
}
void MainWindow::on_sendSmsButton_clicked() {
    QString employeeId = ui->telephonelogin->text();
    Employe employe;
    employe.setIdEmploye(employeeId);
    if (employe.load()) {
        int phoneNumber = employe.getTelephone();
        QString phoneNumberStr = QString::number(phoneNumber);

        verificationCode = QString::number(QRandomGenerator::global()->bounded(100000)).rightJustified(5, '0');

        sendSms(phoneNumberStr, verificationCode);

        QMessageBox::information(this, "SMS envoyé", "Un code de vérification a été envoyé au téléphone de l'employé");

    } else {
        QMessageBox::critical(this, "Erreur", "Employé non trouvé.");





    }
}


void MainWindow::on_verifyCodeButton_clicked() {
    QString enteredCode = ui->smsmdp->text();

    if (enteredCode == verificationCode) {
        QMessageBox::information(this, "Vérification réussie", "Code vérifié avec succès !");
        ui->stackedWidgetlogin->setCurrentIndex(2);
    } else {
        QMessageBox::warning(this, "Échec de la vérification", "Le code que vous avez saisi est incorrect. Veuillez réessayer.");
    }
}
void MainWindow::on_updatePasswordButton_clicked() {
    QString employeeId = ui->telephonelogin->text();
    QString newPassword = ui->newmdplineedit->text();

    if (newPassword.isEmpty()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un nouveau mot de passe.");
        return;
    }

    Employe employe;
    employe.setIdEmploye(employeeId);

    qDebug() << "Attempting to load employee with ID:" << employeeId;

    if (employe.load()) {
        qDebug() << "Employee found, updating password.";
        employe.setPassword(newPassword);

        QSqlQuery query;
        query.prepare("UPDATE employe SET MOTEDEPASS = :password WHERE ID_EMPLOYE = :id_employe");
        query.bindValue(":password", newPassword);
        query.bindValue(":id_employe", employeeId);

        if (query.exec()) {
            qDebug() << "Password updated successfully.";
            QMessageBox::information(this, "Succès", "Mot de passe mis à jour avec succès !");
            ui->stackedWidgetlogin->setCurrentIndex(0);
        } else {
            qDebug() << "Failed to update password. Error:" << query.lastError().text();
            QMessageBox::warning(this, "Erreur", "Échec de la mise à jour du mot de passe. Veuillez réessayer.");
        }
    } else {
        qDebug() << "Employee not found for ID:" << employeeId;
        QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
    }
}

void MainWindow::on_sortie_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_clicked()
{
    QString employeeId = ui->idreponse->text();
    Employe employe;
    employe.setIdEmploye(employeeId);
    qDebug() << "Employee eee:" << employe.getPoste();
    if (employe.load()) {

    if(employe.getPoste()=="Manager de magasin"){
        QMessageBox::information(this, "Connexion réussie", "Bienvenue, " + employe.getNom() + " " + employe.getPrenom());
        ui->label_169->show();
        ui->tableViewConge->show();
        ui->accepterconge->show();
        ui->refuserconge->show();


    } else {
        QMessageBox::warning(this, "Erreur", "Sauf les managers, personne n'a le droit d'entrer ceci.");
    }
    } else {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé");
    }



}


void MainWindow::on_retour_5_clicked()
{
    ui->label_169->hide();
    ui->tableViewConge->hide();
    ui->accepterconge->hide();
    ui->refuserconge->hide();
    ui->idreponse->clear();
}

