#include "mainwindow.h"
#include "Article.h"

#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QtCharts/QChartView>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <cstdlib> // Pour utiliser rand() et srand()
#include <ctime>   // Pour initialiser le générateur de nombres aléatoires
#include "arduino.h"

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QXlsx/QXlsx/header\xlsxdocument_p.h>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QPdfWriter>
#include <QCompleter>
#include <QNetworkAccessManager>
#include <QNetworkReply>
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

#include<QDir>
#include <QProcess>
#include <QTime>
#include "vocale.h"

#include <QRandomGenerator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),vocaleHandler(new Vocale(this)),
    employeModel(new QSqlQueryModel(this)),
    arduinoa(new Arduino(this)),   // Assuming employeModel is initialized here

    sortOrderAscending(true) // Default sort order
{
    ui->setupUi(this);
 ui->stackedWidgetSign->setCurrentIndex(0);
    ui->stackedWidgetlogin->setCurrentIndex(0);
    if (arduino.connectToArduino()) {
        connect(arduino.getSerial(), &QSerialPort::readyRead, this, &MainWindow::readFromArduino);
        qDebug() << "Arduino connected successfully.";
    } else {
        qDebug() << "Failed to connect to Arduino.";
    }
    arduinoa->setupSerialConnection("COM7");  // Replace COM7 with your Arduino port name

    connect(arduinoa, &Arduino::dataUpdated, this, &MainWindow::updateDisplay);


    connect(ui->ajoute_employe, &QPushButton::clicked, this, &MainWindow::on_ajoute_employe_clicked);

 QByteArray dataToSend = "Hello Arduino!";  // You can replace this with the appropriate message
 arduino.writeToArduino(dataToSend);
 setupLineEditCompletion();
 applyStyleSheet();

 ui->listWidget_Tailles->setSelectionMode(QAbstractItemView::MultiSelection);
 ui->listWidget_Tailles->addItems(QStringList() << "XS" << "S" << "M" << "L" << "XL" << "XXL" << "XXXL");

 ui->tableViewArticle->setModel(ART.afficherArticle());
 populateThemeBox();
 populateAnimationBox();
 populateLegendBox();

 qApp->setPalette(palette());

 trayIcon = new QSystemTrayIcon(this);
 trayIcon->setIcon(QIcon(":/new/prefix1/try_icon.png"));  // Mettre à jour le chemin de l'icône

 trayIcon->setVisible(true);
 qDebug() << "Tray icon visibility: " << trayIcon->isVisible();

 // Set up the tray icon menu
 QMenu *trayIconMenu = new QMenu(this);
 QAction *quitAction = new QAction("Quitter", this);
 connect(quitAction, &QAction::triggered, this, &QApplication::quit);
 trayIconMenu->addAction(quitAction);
 trayIcon->setContextMenu(trayIconMenu);

 // Set up periodic low stock notifications
 QTimer *timer = new QTimer(this);
 connect(timer, &QTimer::timeout, this, &MainWindow::notifyLowStock);
 timer->start(86400000); // 24 hours

 // Immediate notifications
 notifyAnniversary();
 notifyLowStock();
 notifyPromotion();
     //chatbot
 networkManager = new QNetworkAccessManager(this);

 connect(ui->pushButton_chatbot_query, &QPushButton::clicked, this, &MainWindow::on_pushButton_chatbot_query_clicked);
 connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);

 connect(ui->pushButton_notifyAnniversary, &QPushButton::clicked, this, &MainWindow::notifyAnniversary);
 connect(ui->pushButton_notifyLowStock, &QPushButton::clicked, this, &MainWindow::notifyLowStock);
 connect(ui->pushButton_notifyPromotion, &QPushButton::clicked, this, &MainWindow::notifyPromotion);





 ui->tableViewArticle->setStyleSheet("QTableView::item { background-color: rgb(173, 216, 230); color: black; }");

 connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
 connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(on_comboBox_2_activated(int)));

 notificationModel = new QStandardItemModel(this);

 connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);

 connect(ui->themeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeTheme);

 ui->stacked->addWidget(ui->ajouter);
 ui->stacked->addWidget(ui->articles);
 ui->stacked->addWidget(ui->Statiques);
 ui->stacked->addWidget(ui->notification);
 ui->stacked->addWidget(ui->Fabriquer);

 connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::ajouter);
 connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::articles);
 connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::Statiques);
 connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::notification);

 connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::ajouter);
 connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::articles);
 connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::Statiques);
 connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::notification);

 connect(ui->FABRIQUER,&QPushButton::clicked, this, &MainWindow::Fabriquer);

 connect(ui->ID_ARTICLE, &QPushButton::clicked, this, &MainWindow::on_ID_ARTICLE_clicked);

 ui->stackedWidgetArticle->addWidget(ui->DiaCirculaire);
 ui->stackedWidgetArticle->addWidget(ui->Graph1);
 ui->stackedWidgetArticle->addWidget(ui->Graph2);

 connect(ui->pushButton_DiagrammCirculaire, &QPushButton::clicked, this, &MainWindow::DiaCirculaire);
 connect(ui->pushButton_GraphiqueBarres, &QPushButton::clicked, this, &MainWindow::Graph2);

 ui->comboBox_2->setStyleSheet("   border: 2px solid white;border-radius: 8px;padding: 1px 18px 1px 3px;background-color: black;color: white;height: 35px");
 ui->comboBox_2->setStyleSheet(" padding-left: 15px;font-weight: bold;  border: 0;selection-background-color: #298089;");
 ui->pushButton_DiagrammCirculaire->setStyleSheet("height:30px;border-radius:5px");
 ui->pushButton_GraphiqueBarres->setStyleSheet("height:30px;border-radius:5px");

 connect(ui->tableViewArticle->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::notifyLowStock);

 populateThemeBox();






 ui->tableViewtransaction->setModel(transactionModel.afficher());
 // Connexion du signal textCaptured au QTextEdit

 connect(vocaleHandler, &Vocale::textCaptured, this, [this](QString text) {
     qDebug() << "Captured text: " << text;  // Debugging output to see the captured text

     if (ui->voc_text) {  // Check if voc_text widget is valid
         ui->voc_text->append(text);  // Add only the recognized text to the text field
     } else {
         qDebug() << "voc_text is null!";  // Debugging: Check if voc_text is valid
     }
 });
 int ret=A.connect_arduinod();
 switch(ret){
 case(0):qDebug()<< "arduinod is available and connected to : "<< A.getarduinod_port_name();
     break;
 case(1):qDebug() << "arduinod is available but not connected to :" <<A.getarduinod_port_name();
     break;
 case(-1):qDebug() << "arduinod is not available";
 }



 connect(ui->ajouterTransaction, &QPushButton::clicked, this, &MainWindow::on_ajouterTransaction_clicked);
 connect(ui->supprimer_2, &QPushButton::clicked, this, &MainWindow::on_supprimer_clickedt);
 connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
 connect(ui->rechercherTransaction, &QPushButton::clicked, this, &MainWindow::on_rechercherTransaction_clicked);
 connect(ui->statistiqueButtonTransaction, &QPushButton::clicked, this, &MainWindow::on_statistiqueButtonTransaction_clicked);
 connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_tri_clicked);
 connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::on_pdf_clicked);
 connect(ui->vocale, &QPushButton::clicked, this, &MainWindow::on_vocale_clicked);

 connect(ui->stop_voc, &QPushButton::clicked, this, &MainWindow::on_stop_voc_clicked);


 affichageClient();

 connect(ui->trier, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_trier_activated);
 connect(ui->tableViewclient_2->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_tableView_2_headerClicked);

 // Connect the statistics button to its handler
 connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statsButton_clicked);
 connect(ui->btnClassify, &QPushButton::clicked, this, &MainWindow::classifyClients);
 connect(ui->envoyer_mail, &QPushButton::clicked, this, &MainWindow::on_envoyer_mail_clicked);


 connect(ui->btnAjouter, &QPushButton::clicked, this, &MainWindow::on_btnAjouter_clicked);
 connect(ui->modifier_2, &QPushButton::clicked, this, &MainWindow::on_modifiercl_clicked);
 connect(ui->supprimer_3, &QPushButton::clicked, this, &MainWindow::on_supprimercl_clicked);

 connect(ui->afficher, &QPushButton::clicked, this, &MainWindow::on_afficher_clicked);
 connect(ui->Telecharger_button, &QPushButton::clicked, this, &MainWindow::on_Telecharger_button_clicked);
 connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);



 // Input field validators

 QRegularExpression numeroRegex("[0-9]{1,15}");  // Allow only digits for Numero (up to 15 digits)
 QRegularExpressionValidator* numeroValidator = new QRegularExpressionValidator(numeroRegex, this);
 ui->Numero_input->setValidator(numeroValidator);
 ui->NOM_input->setInputMask("AAAAAAAAAAAAAAAAAAAA");      // Up to 20 alphabetic characters
 ui->PRENOM_input->setInputMask("AAAAAAAAAAAAAAAAAAAA");   // Up to 20 alphabetic characters
 // Validator for Email (simple validation pattern)
 QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
 QRegularExpressionValidator* emailValidator = new QRegularExpressionValidator(emailRegex, this);
 ui->MAIL_input->setValidator(emailValidator);
 // Input field for Date of Inscription (QDateEdit widget)
 ui->DATE_input->setCalendarPopup(true);  // Optionally enable the calendar popup
 ui->DATE_input->setDisplayFormat("dd/MM/yyyy");  // Optional: Set the display format (day/month/year)





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



    connect(ui->sortie_2, &QPushButton::clicked, this, &MainWindow::on_sortie_clicked);
    connect(ui->sortie_3, &QPushButton::clicked, this, &MainWindow::on_sortie_clicked);
    connect(ui->sortie_4, &QPushButton::clicked, this, &MainWindow::on_sortie_clicked);



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
    connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
    connect(ui->comboBox_3, SIGNAL(activated(int)), this, SLOT(on_comboBox_2_activated(int)));


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


    ui->label_216->show();
    employeModel = new QSqlQueryModel(this);
    afficherEmployes();
    displaydemandeconge();



}

MainWindow::~MainWindow() {
    delete ui;
    delete vocaleHandler;

}

void MainWindow::navigateToEmploye() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->chartPlaceholder->hide();
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
    QByteArray fingerprint;


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

    Employe employe(nom, prenom, email, telephone, Id_employe, poste, salaire, presence, suppl, dateNaissance, dateEmbauche,description,motedepass,fingerprint);
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

    Employe employe("", "", "", 0, Id_employe, "", 0.0, "", 0.0, "", "","","","");
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
    ui->chartPlaceholder->show();

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
    chart->setTitle("Nombre d'employés par poste");
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

    const QString apiUrl = "https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json";

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
        QString message = "Votre demande de congé a été acceptée.";
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
        QString message = "Votre demande de congé a été refusée.";
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
    QByteArray fingerprint;

    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Id_employe:" << Id_employe;
    qDebug() << "Poste:" << poste;
    qDebug() << "Date Naissance:" << dateNaissance;
    qDebug() << "Date Embauche:" << dateEmbaucheStr;
    qDebug() << "Mot de Passe:" << motedepass;

    Employe employe(nom, prenom, email, telephone, Id_employe, poste, salaire, presence, suppl, dateNaissance, dateEmbaucheStr,description,motedepass,fingerprint);

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
    if (ui->stackedWidget->currentIndex() != 1){
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
            QMessageBox::information(this, "Connexion réussie", "Bienvenue, " + nom + " " + prenom);
            ui->stackedWidget->setCurrentIndex(1);

        } else {
            QMessageBox::warning(this, "Erreur", "ID de l'employé ou mot de passe incorrect.");
        }
    }
    ui->telephonelogin->clear();
    ui->mdplogin->clear();
    ui->smsmdp->clear();
    ui->newmdplineedit->clear();


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
    ui->stackedWidgetSign->setCurrentIndex(0);


}


void MainWindow::on_pushButton_clickedchef()
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
void MainWindow::ajouter()
{
    ui->stacked->setCurrentIndex(0);
}

void MainWindow::articles()
{
    ui->stacked->setCurrentIndex(1);
}

void MainWindow::Statiques()
{
    ui->stacked->setCurrentIndex(2);
}

void MainWindow::notification()
{
    ui->stacked->setCurrentIndex(3);
}

void MainWindow::Fabriquer()
{
    ui->stacked->setCurrentIndex(4);
}

void MainWindow::DiaCirculaire()
{
    ui->stackedWidgetArticle->setCurrentIndex(1);
}

void MainWindow::Graph1()
{
    ui->stackedWidgetArticle->setCurrentIndex(2);
}

void MainWindow::Graph2()
{
    ui->stackedWidgetArticle->setCurrentIndex(3);
}



void MainWindow::on_Page2_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    contextMenu.addAction("Option 1");
    contextMenu.addAction("Option 2");
    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->pushButton_6->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font6 = ui->pushButton_6-> font();
    font6.setBold(true);
    ui->pushButton_6->setFont(font6);

    ui->pushButton_9->setStyleSheet("");
    QFont font9 = ui->pushButton_9-> font();
    font9.setBold(false);
    ui->pushButton_9->setFont(font9);

    ui->pushButton_8->setStyleSheet("");
    QFont font8 = ui->pushButton_8-> font();
    font8.setBold(false);
    ui->pushButton_8->setFont(font8);

    ui->pushButton_7->setStyleSheet("");
    QFont font7 = ui->pushButton_7-> font();
    font7.setBold(false);
    ui->pushButton_7->setFont(font7);

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->pushButton_7->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font7 = ui->pushButton_7-> font();
    font7.setBold(true);
    ui->pushButton_7->setFont(font7);

    ui->pushButton_6->setStyleSheet("");
    QFont font6 = ui->pushButton_6-> font();
    font6.setBold(false);
    ui->pushButton_6->setFont(font6);

    ui->pushButton_9->setStyleSheet("");
    QFont font9 = ui->pushButton_9-> font();
    font9.setBold(false);
    ui->pushButton_9->setFont(font9);

    ui->pushButton_8->setStyleSheet("");
    QFont font8 = ui->pushButton_8-> font();
    font8.setBold(false);
    ui->pushButton_8->setFont(font8);
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->pushButton_8->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font8 = ui->pushButton_8-> font();
    font8.setBold(true);
    ui->pushButton_8->setFont(font8);

    ui->pushButton_7->setStyleSheet("");
    QFont font7 = ui->pushButton_7-> font();
    font7.setBold(false);
    ui->pushButton_7->setFont(font7);

    ui->pushButton_6->setStyleSheet("");
    QFont font6 = ui->pushButton_6-> font();
    font6.setBold(false);
    ui->pushButton_6->setFont(font6);

    ui->pushButton_9->setStyleSheet("");
    QFont font9 = ui->pushButton_9-> font();
    font9.setBold(false);
    ui->pushButton_9->setFont(font9);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->pushButton_9->setStyleSheet("background-color:white;color: red; border: 2px solid white;");
    QFont font9 = ui->pushButton_9-> font();
    font9.setBold(true);
    ui->pushButton_9->setFont(font9);

    ui->pushButton_8->setStyleSheet("");
    QFont font8 = ui->pushButton_8-> font();
    font8.setBold(false);
    ui->pushButton_8->setFont(font8);

    ui->pushButton_7->setStyleSheet("");
    QFont font7 = ui->pushButton_7-> font();
    font7.setBold(false);
    ui->pushButton_7->setFont(font7);

    ui->pushButton_6->setStyleSheet("");
    QFont font6 = ui->pushButton_6-> font();
    font6.setBold(false);
    ui->pushButton_6->setFont(font6);
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


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font2 = ui->pushButton_2-> font();
    font2.setBold(true);
    ui->pushButton_2->setFont(font2);

    ui->pushButton->setStyleSheet("");
    QFont font = ui->pushButton-> font();
    font.setBold(false);
    ui->pushButton_6->setFont(font);

    ui->pushButton_3->setStyleSheet("");
    QFont font3 = ui->pushButton_3-> font();
    font3.setBold(false);
    ui->pushButton_3->setFont(font3);

    ui->pushButton_4->setStyleSheet("");
    QFont font4 = ui->pushButton_4-> font();
    font4.setBold(false);
    ui->pushButton_4->setFont(font4);
}


void MainWindow::on_pushButton_3_clicked()
{

    ui->pushButton_3->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font3 = ui->pushButton_3-> font();
    font3.setBold(true);
    ui->pushButton_3->setFont(font3);

    ui->pushButton->setStyleSheet("");
    QFont font = ui->pushButton-> font();
    font.setBold(false);
    ui->pushButton_6->setFont(font);

    ui->pushButton_2->setStyleSheet("");
    QFont font2 = ui->pushButton_2-> font();
    font2.setBold(false);
    ui->pushButton_2->setFont(font2);



    ui->pushButton_4->setStyleSheet("");
    QFont font4 = ui->pushButton_4-> font();
    font4.setBold(false);
    ui->pushButton_4->setFont(font4);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton_4->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font4 = ui->pushButton_4-> font();
    font4.setBold(true);
    ui->pushButton_4->setFont(font4);

    ui->pushButton->setStyleSheet("");
    QFont font = ui->pushButton-> font();
    font.setBold(false);
    ui->pushButton_6->setFont(font);

    ui->pushButton_2->setStyleSheet("");
    QFont font2 = ui->pushButton_2-> font();
    font2.setBold(false);
    ui->pushButton_2->setFont(font2);

    ui->pushButton_3->setStyleSheet("");
    QFont font3 = ui->pushButton_3-> font();
    font3.setBold(false);
    ui->pushButton_3->setFont(font3);


}
void MainWindow::on_pushButton_DiagrammCirculaire_clicked(bool checked)
{
    if(checked)
    {
        ui-> pushButton_DiagrammCirculaire->setStyleSheet("height:30px;border-radius:5px;background-color:#0056D2;color:white;font-weight:bold");
        ui->pushButton_GraphiqueBarres->setStyleSheet("");

    }
}


void MainWindow::on_pushButton_14_clicked(bool checked)
{
    if(checked)
    {
        ui->pushButton_GraphiqueBarres->setStyleSheet("");
        ui-> pushButton_DiagrammCirculaire->setStyleSheet("");

    }
}


void MainWindow::on_pushButton_GraphiqueBarres_clicked(bool checked)
{
    if(checked)
    {
        ui->pushButton_GraphiqueBarres->setStyleSheet("height:30px;border-radius:5px;background-color:#0056D2;color:white;font-weight:bold");
        ui-> pushButton_DiagrammCirculaire->setStyleSheet("");

    }
}

void MainWindow::populateThemeBox()
{
    // add items to theme combobox
    ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void MainWindow::populateAnimationBox()
{
   //
}

void MainWindow::populateLegendBox()
{
   //dComboBox->addItem("Legend Right", Qt::AlignRight);
}


void MainWindow::changeTheme(int index)
{
    QString styleSheet;

    switch (index) {
    case 0: // Light
        styleSheet = "QWidget { background-color: white; color: black; }"; // Blanc
        break;
    case 1: // Blue Cerulean
        styleSheet = "QWidget { background-color: rgb(0, 123, 167); color: white; }"; // Bleu Cerulean
        break;
    case 2: // Dark
        styleSheet = "QWidget { background-color: rgb(53, 53, 53); color: white; }"; // Gris foncé
        break;
    case 3: // Brown Sand
        styleSheet = "QWidget { background-color: rgb(193, 154, 107); color: black; }"; // Marron sable
        break;
    case 4: // Blue NCS
        styleSheet = "QWidget { background-color: rgb(0, 102, 204); color: white; }"; // Bleu NCS
        break;
    case 5: // High Contrast
        styleSheet = "QWidget { background-color: black; color: white; }"; // Noir
        break;
    case 6: // Blue Icy
        styleSheet = "QWidget { background-color: rgb(173, 216, 230); color: black; }"; // Bleu icy
        break;
    case 7: // Qt Theme
        styleSheet.clear(); // Réinitialise pour utiliser le style par défaut
        break;
    }

    ui->stackedWidgetArticle->setStyleSheet(styleSheet);
}


void MainWindow::changeAnimation(int index)
{
   //
}

void MainWindow::on_Ajouter_clicked() {
    // Retrieve the information entered in the input fields
    QString ID_ARTICLE = ui->lineEdit_CODE->text();

    // Validation: Check if ID_ARTICLE is empty
    if (ID_ARTICLE.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'ID de l'article ne peut pas être vide.");
        qDebug() << "Error: ID_ARTICLE is empty.";
        return;
    }

    // Validation: Check the length of ID_ARTICLE
    if (ID_ARTICLE.length() < 5 || ID_ARTICLE.length() > 20) {
        QMessageBox::warning(this, "Erreur", "L'ID de l'article doit être compris entre 5 et 20 caractères.");
        qDebug() << "Error: Invalid ID_ARTICLE length. Length =" << ID_ARTICLE.length();
        return;
    }

    QString NOM_A = ui->lineEdit_NOM->text();
    QStringList allowedValues = {"Chemise", "Pantalon", "Veste", "Robe", "Pull", "Jupe"};

    // Validation: Check if NOM_A is empty
    if (NOM_A.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom de l'article ne peut pas être vide.");
        qDebug() << "Error: NOM_A is empty.";
        return;
    }

    // Validation: Check if NOM_A is one of the allowed values
    if (!allowedValues.contains(NOM_A)) {
        QMessageBox::warning(this, "Erreur", "Le nom de l'article doit être l'un des suivants : Chemise, Pantalon, Veste, Robe, Pull, Jupe.");
        qDebug() << "Error: NOM_A is invalid. Value =" << NOM_A;
        return;
    }

    // Validation: Check if NOM_A has valid characters
    QRegularExpression regex("^[A-Za-zÀ-ÿéèêôïîàùç ]+$"); // Letters, accents, and spaces
    if (!regex.match(NOM_A).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom de l'article doit contenir uniquement des lettres et des espaces.");
        qDebug() << "Error: NOM_A has invalid characters. Value =" << NOM_A;
        return;
    }

    QDate DATE_AJOUT = ui->dateTimeEdit_2->date();

    // Validation: Check if the date is in the past
    if (DATE_AJOUT < QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "La date ne peut pas être dans le passé.");
        qDebug() << "Error: DATE_AJOUT is in the past. Value =" << DATE_AJOUT;
        return;
    }

    QString TYPE = ui->comboBox_2->currentText();

    // Validation: Check if TYPE is empty
    if (TYPE.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un type.");
        qDebug() << "Error: TYPE is empty.";
        return;
    }

    QString CATEGORIE;
    if (ui->radioButton_Automne->isChecked()) {
        CATEGORIE = ui->radioButton_Automne->text();
    } else if (ui->radioButton_Printemps->isChecked()) {
        CATEGORIE = ui->radioButton_Printemps->text();
    } else if (ui->radioButton_Ete->isChecked()) {
        CATEGORIE = ui->radioButton_Ete->text();
    } else if (ui->radioButton_Hiver->isChecked()) {
        CATEGORIE = ui->radioButton_Hiver->text();
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une catégorie.");
        qDebug() << "Error: No category selected.";
        return;
    }

    double PRIX = ui->doubleSpinBox_2->value();

    // Validation: Check if PRIX is valid
    if (PRIX <= 0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être supérieur à zéro.");
        qDebug() << "Error: Invalid PRIX. Value =" << PRIX;
        return;
    }

    int QUANTITE_STOCK = ui->spinBox_Quantite->value();

    // Validation: Check if QUANTITE_STOCK is valid
    if (QUANTITE_STOCK < 0) {
        QMessageBox::warning(this, "Erreur", "La quantité en stock ne peut pas être négative.");
        qDebug() << "Error: Invalid QUANTITE_STOCK. Value =" << QUANTITE_STOCK;
        return;
    }

    QString DESCRIPTIONN = ui->lineEdit_DESCRIPTION->text();

    // Validation: Check if DESCRIPTIONN is empty
    if (DESCRIPTIONN.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La description de l'article ne peut pas être vide.");
        qDebug() << "Error: DESCRIPTIONN is empty.";
        return;
    }

    QString TAILLE;
    QList<QListWidgetItem*> selectedItems = ui->listWidget_Tailles->selectedItems();

    // Validation: Check if at least one size is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner au moins une taille.");
        qDebug() << "Error: No size selected.";
        return;
    } else {
        QStringList taillesList;
        for (QListWidgetItem* item : selectedItems) {
            taillesList.append(item->text());
        }
        TAILLE = taillesList.join(", ");
    }

    QString COULEUR;
    if (ui->checkBox_Blanc->isChecked()) COULEUR += "Blanc, ";
    if (ui->checkBox_Noir->isChecked()) COULEUR += "Noir, ";
    if (ui->checkBox_Bleu->isChecked()) COULEUR += "Bleu, ";
    if (ui->checkBox_Gris->isChecked()) COULEUR += "Gris, ";
    if (ui->checkBox_Rouge->isChecked()) COULEUR += "Rouge, ";

    // Remove trailing comma and space
    if (!COULEUR.isEmpty()) {
        COULEUR.chop(2);
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner au moins une couleur.");
        qDebug() << "Error: No color selected.";
        return;
    }

    // Create the ARTICLE object
    ARTICLE A(ID_ARTICLE, NOM_A, DESCRIPTIONN, PRIX, CATEGORIE, QUANTITE_STOCK, TAILLE, COULEUR, TYPE, DATE_AJOUT);

    // Attempt to add the article
    if (A.ajouterArticle()) {
        QMessageBox::information(this, "Succès", "L'article a été ajouté avec succès.");
        qDebug() << "Article added successfully. ID:" << ID_ARTICLE;
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'article.");
        qDebug() << "Error: Failed to add article. ID:" << ID_ARTICLE;
    }
}


void MainWindow::on_SUPPRIMER_clicked() {
    QString ID_ARTICLE = ui->supprimer->text(); // Fetch the ID to delete.

    // Debug: Check if the ID field is empty
    if (ID_ARTICLE.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID d'article à supprimer.");
        qDebug() << "Error: Empty ID_ARTICLE field.";
        return;
    }

    // Debug: Log the ID_ARTICLE being searched
    qDebug() << "Trying to find article with ID_ARTICLE:" << ID_ARTICLE;

    // Check if the article exists
    if (ART.chercher(ID_ARTICLE)) {
        qDebug() << "Article found. Proceeding to delete.";

        // Attempt to delete the article
        bool test = ART.supprimerArticles(ID_ARTICLE);

        // Debug: Check the result of the delete operation
        if (test) {
            QMessageBox::information(
                this,
                "OK",
                "Suppression effectuée avec succès.",
                QMessageBox::Cancel
                );
            qDebug() << "Article with ID_ARTICLE" << ID_ARTICLE << "deleted successfully.";
        } else {
            QMessageBox::critical(
                this,
                "Erreur",
                "Échec de la suppression de l'article.",
                QMessageBox::Cancel
                );
            qDebug() << "Error: Failed to delete article with ID_ARTICLE" << ID_ARTICLE;
        }
    } else {
        QMessageBox::critical( this,"Erreur", "Article introuvable.", QMessageBox::Cancel);
        qDebug() << "Error: No article found with ID_ARTICLE:" << ID_ARTICLE;
    }
}



void MainWindow::on_miseJOUR_clicked()
{
    ui->tableViewArticle->setModel(ART.afficherArticle());

}


void MainWindow::on_ID_ARTICLE_clicked()
{
    QString id = ui->lineEdit_IdArticle->text();
    if (ART.chercher(id)) {
        if (!ART.getCodeArticle().isEmpty()) {
            ui->lineEdit_CODE->setText(ART.getCodeArticle());
            ui->lineEdit_NOM->setText(ART.getNomArticle());
            ui->dateTimeEdit_2->setDate(ART.getDateAjout());
            ui->lineEdit_DESCRIPTION->setText(ART.getDescription());

            QString saison = ART.getCategorie();
            ui->radioButton_Automne->setChecked(saison == "Automne");
            ui->radioButton_Hiver->setChecked(saison == "Hiver");
            ui->radioButton_Ete->setChecked(saison == "Ete");
            ui->radioButton_Printemps->setChecked(saison == "Printemps");

            // Fill other fields
            ui->doubleSpinBox_2->setValue(ART.getPrix());
            ui->spinBox_Quantite->setValue(ART.getQuantiteStock());

            ui->listWidget_Tailles->clear();
            ui->listWidget_Tailles->addItems(ART.getTaille().split(","));

            QStringList couleurs = ART.getCouleur().split(", ");

            ui->checkBox_Blanc->setChecked(couleurs.contains("Blanc"));
            ui->checkBox_Noir->setChecked(couleurs.contains("Noir"));
            ui->checkBox_Bleu->setChecked(couleurs.contains("Bleu"));
            ui->checkBox_Gris->setChecked(couleurs.contains("Gris"));
            ui->checkBox_Rouge->setChecked(couleurs.contains("Rouge"));
            ui->checkBox_Beige->setChecked(couleurs.contains("Beige"));
            ui->checkBox_Vert->setChecked(couleurs.contains("Vert"));
            ui->checkBox_Rose->setChecked(couleurs.contains("Rose"));
            ui->checkBox_Marron->setChecked(couleurs.contains("Marron"));
            ui->checkBox_Jaune->setChecked(couleurs.contains("Jaune"));
            ui->checkBox_Violet->setChecked(couleurs.contains("Violet"));
            ui->checkBox_Orange->setChecked(couleurs.contains("Orange"));
        } else {
            QMessageBox::warning(this, "Non trouvé", "Article non trouvé avec cet ID.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "La recherche a échoué.");
    }
}

void MainWindow::on_MODIFIER_clicked()
{
    // Get the article ID (which is a string)
    QString id = ui->lineEdit_IdArticle->text();

    // Check if the ID is not empty
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID d'article.");
        return;
    }

    // Search for the article with this ID
    if (ART.chercher(id)) {
        ART.setNomArticle(ui->lineEdit_NOM->text());
        ART.setDescription(ui->lineEdit_DESCRIPTION->text());
        QStringList couleursSelectionnees;

        if (ui->checkBox_Blanc->isChecked()) couleursSelectionnees << "Blanc";
        if (ui->checkBox_Noir->isChecked()) couleursSelectionnees << "Noir";
        if (ui->checkBox_Bleu->isChecked()) couleursSelectionnees << "Bleu";
        if (ui->checkBox_Gris->isChecked()) couleursSelectionnees << "Gris";
        if (ui->checkBox_Rouge->isChecked()) couleursSelectionnees << "Rouge";
        if (ui->checkBox_Beige->isChecked()) couleursSelectionnees << "Beige";
        if (ui->checkBox_Vert->isChecked()) couleursSelectionnees << "Vert";
        if (ui->checkBox_Rose->isChecked()) couleursSelectionnees << "Rose";
        if (ui->checkBox_Marron->isChecked()) couleursSelectionnees << "Marron";
        if (ui->checkBox_Jaune->isChecked()) couleursSelectionnees << "Jaune";
        if (ui->checkBox_Violet->isChecked()) couleursSelectionnees << "Violet";
        if (ui->checkBox_Orange->isChecked()) couleursSelectionnees << "Orange";

        QString couleur = couleursSelectionnees.join(", ");
        ART.setCouleur(couleur);

        QStringList tailles;
        for (int i = 0; i < ui->listWidget_Tailles->count(); ++i) {
            tailles.append(ui->listWidget_Tailles->item(i)->text());
        }
        ART.setTaille(tailles.join(","));

        ART.setQuantiteStock(ui->spinBox_Quantite->value());
        ART.setCategorie(getSelectedCategorie());
        ART.setPrix(ui->doubleSpinBox_2->value());
        ART.setDateAjout(ui->dateTimeEdit_2->date());

        if (ART.modifier()) {
            QMessageBox::information(this, "Succès", "L'article a été mis à jour.");
        } else {
            QMessageBox::warning(this, "Erreur", "La mise à jour de l'article a échoué.");
        }
    } else {
        QMessageBox::warning(this, "Non trouvé", "Aucun article trouvé avec cet ID.");
    }
}

QString MainWindow::getSelectedCategorie()
{
    if (ui->radioButton_Automne->isChecked()) {
        return "Automne";
    } else if (ui->radioButton_Hiver->isChecked()) {
        return "Hiver";
    } else if (ui->radioButton_Ete->isChecked()) {
        return "Ete";
    } else if (ui->radioButton_Printemps->isChecked()) {
        return "Printemps";
    }
    return "";
}


void MainWindow::on_comboBox_2_activated(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString orderBy;

    // Déterminer le critère de tri selon l'index du combobox
    switch(index) {
    case 0:
        orderBy = "DATE_AJOUT"; // Trier par date d'ajout
        break;
    case 1:
        orderBy = "NOM_A"; // Trier par nom
        break;
    case 2:
        orderBy = "PRIX"; // Trier par prix
        break;
    default:
        orderBy = "ID_ARTICLE"; // Par défaut trier par ID
    }

    QString order = (ui->comboBox_3->currentIndex() == 0) ? "DESC" : "ASC";

    QString queryStr = QString("SELECT * FROM ARTICLE ORDER BY %1 %2").arg(orderBy, order);
    model->setQuery(queryStr);
    ui->tableViewArticle->setModel(model);

    QSqlQuery query;
    for (int row = 0; row < model->rowCount(); ++row) {
        // Extraire les données triées du modèle
        QString idArticle = model->data(model->index(row, 0)).toString();
        QString prix = model->data(model->index(row, 3)).toString();
        QString dateAjout = model->data(model->index(row, 9)).toString();
        QString nom = model->data(model->index(row, 1)).toString();

        int indexT = dateAjout.indexOf('T');
        if (indexT != -1) {
            dateAjout = dateAjout.left(indexT);  // "2024-11-13"
        }

        qDebug() << "Date Ajout : " << dateAjout;

        query.prepare("UPDATE ARTICLE SET PRIX = :prix, DATE_AJOUT = TO_DATE(:dateAjout, 'YYYY-MM-DD'), NOM_A = :nom, ORDRE = :ordre WHERE ID_ARTICLE = :id");
        query.bindValue(":id", idArticle);
        query.bindValue(":prix", prix);
        query.bindValue(":dateAjout", dateAjout);
        query.bindValue(":nom", nom);
        query.bindValue(":ordre", row + 1);
        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour de l'article : " << query.lastError();
        }
    }
}



void MainWindow::on_rechercher_clicked()
{
    QString categorie = ui->lineEdit_categorie->text().trimmed();
    QString prix = ui->lineEdit_prix->text().trimmed();
    QString type = ui->lineEdit_type->text().trimmed();

    QString queryString = "SELECT ID_ARTICLE, NOM_A, DESCRIPTIONN, PRIX, CATEGORIE, QUANTITE_STOCK, TAILLE, COULEUR, TYPE, DATE_AJOUT FROM ARTICLE WHERE ";

    bool hasCondition = false;

    if (!categorie.isEmpty()) {
        queryString += "CATEGORIE LIKE '%" + categorie + "%' ";
        hasCondition = true;
    }

    if (!prix.isEmpty()) {
        if (hasCondition) queryString += "AND ";
        queryString += "PRIX = " + prix + " ";
        hasCondition = true;
    }

    if (!type.isEmpty()) {
        if (hasCondition) queryString += "AND ";
        queryString += "TYPE LIKE '%" + type + "%' ";
        hasCondition = true;
    }

    if (hasCondition) {
        queryString += ";";
    } else {
        queryString += "1=1;";
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(queryString);

    bool found = model->rowCount() > 0;

    if (!found) {
        QMessageBox::information(this, tr("Information"), tr("No results found."));
        delete model;
        return;
    }

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to retrieve data: ") + model->lastError().text());
        delete model;
        return;
    }

    ui->tableViewArticle->setModel(model);
    ui->tableViewArticle->resizeColumnsToContents(); // Ajuster la largeur des colonnes

}

QMap<QString, int> MainWindow::getTypeCounts() {
    QMap<QString, int> typeCounts;

    QSqlQuery query;
    if (query.exec("SELECT TYPE, COUNT(*) AS TOTAL "
                   "FROM ARTICLE "
                   "WHERE TYPE IN ('Femmes', 'Hommes', 'Enfants') "
                   "GROUP BY TYPE")) {
        while (query.next()) {
            QString type = query.value(0).toString(); // TYPE
            int count = query.value(1).toInt();      // Nombre d'articles
            typeCounts[type] = count;
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
    }

    return typeCounts;
}

void MainWindow::displayTypeStatistics() {
    QMap<QString, int> typeCounts = getTypeCounts();

    qDebug() << "Type Counts: " << typeCounts;

    // Si aucune donnée n'est trouvée, afficher un message et quitter la fonction
    if (typeCounts.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les statistiques des types.";
        return;
    }

    if (!typeCounts.contains("Femmes")) {
        typeCounts["Femmes"] = 0;
    }
    if (!typeCounts.contains("Hommes")) {
        typeCounts["Hommes"] = 0;
    }
    if (!typeCounts.contains("Enfants")) {
        typeCounts["Enfants"] = 0;
    }

    int total = typeCounts["Femmes"] + typeCounts["Hommes"] + typeCounts["Enfants"];
    qDebug() << "Total Count: " << total;

    QString statsText = QString("Femmes: %1\nHommes: %2\nEnfants: %3")
                            .arg(typeCounts["Femmes"])
                            .arg(typeCounts["Hommes"])
                            .arg(typeCounts["Enfants"]);

    ui->statsLabel->setText(statsText);

    if (total == 0) {
        qDebug() << "Total est 0, ne pas générer de graphique.";
        return;
    }

    QPieSeries *series = new QPieSeries();

    series->append("Femmes", typeCounts["Femmes"]);
    series->append("Hommes", typeCounts["Hommes"]);
    series->append("Enfants", typeCounts["Enfants"]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des types d'articles");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QLayout *existingLayout = ui->chartPlaceholder_2->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->chartPlaceholder_2->setLayout(layout);

    qDebug() << "Graphique ajouté avec succès.";
}
void MainWindow::on_pushButton_DiagrammCirculaire_clicked() {
    ui->stackedWidgetArticle->setCurrentWidget(ui->DiaCirculaire);
    displayTypeStatistics(); // Affiche les statistiques des types sous forme de graphique circulaire
}

void MainWindow::displaySizeStatistics() {
    QStringList tailles = {"XS", "S", "M", "L", "XL", "XXL", "XXXL"};

    QMap<QString, int> tailleCounts;

    for (const QString &taille : tailles) {
        tailleCounts[taille] = 0;
    }

    QSqlQuery query("SELECT TAILLE, COUNT(*) FROM ARTICLE GROUP BY TAILLE");

    while (query.next()) {
        QString taille = query.value(0).toString();
        int count = query.value(1).toInt();

        if (tailleCounts.contains(taille)) {
            tailleCounts[taille] = count;
        }
    }

    if (tailleCounts.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les statistiques des tailles.";
        return;
    }

    QMap<QString, QColor> tailleColors = {
        {"XS", Qt::green},
        {"S", Qt::blue},
        {"M", Qt::red},
        {"L", Qt::yellow},
        {"XL", Qt::magenta},
        {"XXL", Qt::cyan},
        {"XXXL", Qt::gray}
    };

    QBarSeries *barSeries = new QBarSeries();

    int maxQuantity = 0;

    for (const QString &taille : tailles) {
        QBarSet *barSet = new QBarSet(taille);
        barSet->append(tailleCounts[taille]);

        barSet->setBrush(tailleColors[taille]);
        barSeries->append(barSet);
        maxQuantity = qMax(maxQuantity, tailleCounts[taille]);
    }

    static QChart *chart = nullptr;

    if (chart) {
        chart->removeAllSeries();
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    } else {
        chart = new QChart();
    }

    chart->addSeries(barSeries);
    chart->setTitle("Statistiques des tailles d'articles");
    chart->setAnimationOptions(QChart::AllAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxQuantity + 1);
    axisY->setTitleText("Quantité");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QLayout *existingLayout = ui->chartPlaceholder_3->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->chartPlaceholder_3->setLayout(layout);

    qDebug() << "Graphique à barres des tailles généré avec succès.";
}

void MainWindow::on_pushButton_GraphiqueBarres_clicked() {
    ui->stackedWidgetArticle->setCurrentWidget(ui->Graph2);
    displaySizeStatistics();
}


void MainWindow::notifyAnniversary() {

    qDebug() << "Vérification des anniversaires des articles...";


    QDate currentDate = QDate::currentDate();

    QAbstractItemModel *model = ui->tableViewArticle->model();

    if (!model) {
        qDebug() << "Erreur : modèle du tableViewArticle invalide.";
        return;
    }


    int count = 0;
    bool foundAnniversaries = false;

    // Parcourir les résultats de la requête
    for (int row = 0; row < model->rowCount(); ++row) {
        // Lire les données de chaque colonne (ID_ARTICLE, NOM_A, DATE_AJOUT)
        QString idArticle = model->data(model->index(row, 0)).toString();  // Colonne 0 pour ID_ARTICLE
        QString nom = model->data(model->index(row, 1)).toString();  // Colonne 1 pour NOM_A
        QDate dateAjout = model->data(model->index(row, 9)).toDate();  // Colonne 2 pour DATE_AJOUT

        count++;

        qDebug() << "Vérification de l'anniversaire pour l'article ID:" << idArticle << ", Nom:" << nom;

        //int age = currentDate.year() - dateAjout.year();

        if (currentDate.month() == dateAjout.month() && currentDate.day() == dateAjout.day() /*&& age >= 1*/) {
            foundAnniversaries = true;

            QTimer::singleShot(5000, [this, idArticle, nom, dateAjout]() {
                QString message = QString("C'est l'anniversaire de l'article %1 (%2), ajouté le %3.\n")
                                      .arg(idArticle)
                                      .arg(nom)
                                      .arg(dateAjout.toString("dd/MM/yyyy"));
                trayIcon->showMessage("Anniversaire d'Article", message, QSystemTrayIcon::Information,0);
            });
        }
    }
    /* if (!foundAnniversaries) {
          qDebug() << "Aucun anniversaire trouvé aujourd'hui.";
          QTimer::singleShot(5000, this, [this]() {
              trayIcon->showMessage("Aucun Anniversaire", "Aucun anniversaire d'article trouvé aujourd'hui.", QSystemTrayIcon::Information);
          });
}*/
}

void MainWindow::notifyLowStock() {
    qDebug() << "Vérification des stocks faibles...";

    QAbstractItemModel *model = ui->tableViewArticle->model();
    if (!model) {
        qDebug() << "Erreur : modèle du tableView invalide.";
        return;
    }

    bool foundLowStock = false;

    for (int row = 0; row < model->rowCount(); ++row) {
        QString idArticle = model->data(model->index(row, 0)).toString();
        QString nom = model->data(model->index(row, 1)).toString();
        int quantiteStock = model->data(model->index(row, 5)).toInt();

        if (quantiteStock < 10) {
            foundLowStock = true;

            // Créer le message de notification
            QString notificationMessage = QString("L'article %1 (%2) a un stock faible : %3 unités restantes.")
                                              .arg(idArticle)
                                              .arg(nom)
                                              .arg(quantiteStock);

            // Ajouter la notification à l'historique
            Notification newNotification(notificationMessage);
            notificationHistory.append(newNotification);

            // Afficher la notification
            trayIcon->showMessage("Alerte Stock Faible", notificationMessage, QSystemTrayIcon::Warning);

            // Masquer la notification après 10 secondes
            QTimer::singleShot(10000, [this]() {
                trayIcon->hide();
            });
        }
    }

    if (!foundLowStock) {
        qDebug() << "Aucun stock faible détecté.";
    }
}




void MainWindow::notifyPromotion() {
    // Ajouter ici la logique de notification pour les promotions
    qDebug() << "Vérification des promotions...";

    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Créer une requête SQL pour récupérer les articles dont le prix est inférieur à 50 et la date d'ajout est dans les 30 derniers jours
    QSqlQuery query;
    query.prepare("SELECT ID_ARTICLE, NOM_A, PRIX, DATE_AJOUT FROM ARTICLE "
                  "WHERE PRIX < 50");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    // Parcourir les résultats de la requête et afficher les notifications pour les articles en promotion
    QString promotionMessage;
    while (query.next()) {
        QString idArticle = query.value("ID_ARTICLE").toString();
        QString nom = query.value("NOM_A").toString();
        double prix = query.value("PRIX").toDouble();
        QDateTime dateAjout = query.value("DATE_AJOUT").toDateTime();


        QDateTime promotionEndDate = dateAjout.addDays(30);

        //QDateTime promotionEndDate = dateAjout.addSecs(5);  // Ajoute 5 secondes à la date d'ajout

        // Calculer la durée restante de la promotion
        int daysRemaining = currentDateTime.secsTo(promotionEndDate);

        // Si l'article est encore en promotion (dans les 30 jours)
        if (daysRemaining > 0) {
            // Ajouter un message pour chaque article encore en promotion
            QString message = QString("L'article %1 (%2) est en promotion à %3€. Il reste %4 jour(s) de promotion.\n")
                                  .arg(idArticle)
                                  .arg(nom)
                                  .arg(prix)
                                  .arg(daysRemaining);

            trayIcon->showMessage("Promotion en cours", message, QSystemTrayIcon::Information);
        }
        // Si la promotion est terminée, l'article redevient normal
        /*QTimer::singleShot(5000, [this, idArticle, nom]() {
                // Afficher un message après 5 secondes
                QString expiredMessage = QString("L'article %1 (%2) était en promotion, mais la promotion est terminée.\n")
                                         .arg(idArticle)
                                         .arg(nom);
                // Afficher la notification avec un délai de 5 secondes
                trayIcon->showMessage("Promotion terminée", expiredMessage, QSystemTrayIcon::Warning);*/

        QTimer::singleShot(30 * 24 * 60 * 60 * 1000, [this, idArticle, nom]() {  // 30 jours en millisecondes
            QString endMessage = QString("L'article %1 (%2) était en promotion, mais la promotion est terminée depuis 30 jours.\n")
                                     .arg(idArticle)
                                     .arg(nom);
            trayIcon->showMessage("Promotion Terminée (30 jours)", endMessage, QSystemTrayIcon::Information);
        });
    };
}

void MainWindow::markNotificationAsSeen(int notificationIndex) {
    if (notificationIndex >= 0 && notificationIndex < notificationHistory.size()) {
        notificationHistory[notificationIndex].isSeen = true;
        qDebug() << "Notification marquée comme vue.";
    }
}
void MainWindow::showNotifications() {
    QString notificationsText;
    int unseenCount = 0;  // Compter le nombre de notifications non vues

    for (const Notification &notif : notificationHistory) {
        if (!notif.isSeen) {  // Ne montre que celles qui n'ont pas été vues
            notificationsText += notif.message + "\n";
            unseenCount++;
        }
    }

    if (unseenCount > 0) {
        // Afficher les notifications non vues dans l'icône de la barre de notification
        trayIcon->showMessage("Notifications non vues",
                              QString("Vous avez %1 notification(s) non vue(s):\n%2").arg(unseenCount).arg(notificationsText),
                              QSystemTrayIcon::Information, 5000);  // Affichage pendant 5 secondes
    } else {
        trayIcon->showMessage("Aucune notification non vue",
                              "Vous n'avez aucune notification non vue.",
                              QSystemTrayIcon::Information, 3000);  // Affichage pendant 3 secondes
    }
}


void MainWindow::checkNotificationsExpiry() {
    QDateTime now = QDateTime::currentDateTime();
    for (int i = notificationHistory.size() - 1; i >= 0; --i) {
        if (notificationHistory[i].dateReceived.addSecs(86400) < now) {  // 86400 secondes = 24 heures
            notificationHistory.removeAt(i);
        }
    }
}



bool MainWindow::generatePdf() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/rupture_stock.pdf";
    QFile file(filePath);

    // Ouvrir le fichier en mode écriture
    if (file.open(QIODevice::WriteOnly)) {
        QSqlQuery query;

        // Requête SQL pour récupérer les articles en rupture de stock
        QString sqlQuery = "SELECT ID_ARTICLE, NOM_A, DESCRIPTIONN, PRIX, CATEGORIE, QUANTITE_STOCK, TAILLE, COULEUR, TYPE, DATE_AJOUT "
                           "FROM ARTICLE WHERE QUANTITE_STOCK = 0";

        // Exécuter la requête SQL
        if (!query.exec(sqlQuery)) {
            qWarning() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
            return false;
        }

        // Début de la structure HTML pour le PDF
        QString htmlCode = "<html><head><title>Articles en rupture de stock</title><style> \
            body { font-family: Arial, sans-serif; background: linear-gradient(to bottom right, #ffffff, #e0e0e0); } \
            table { border-collapse: collapse; width: 100%; background-color: #fff; border: 1px solid #ddd; table-layout: fixed; } \
            th, td { padding: 10px; text-align: left; border-bottom: 1px solid #ddd; word-wrap: break-word; } \
            th { background-color: #FF6347; color: white; font-weight: bold; height: 40px; } \
            tr:nth-child(even) { background-color: #f2f2f2; } \
            tr:hover { background-color: #ddd; } \
            </style></head><body><h1 style='text-align:center;'>Articles en rupture de stock</h1>\
            <table><tr><th>ID Article</th><th>Nom</th><th>Description</th><th>Prix</th><th>Catégorie</th><th>Taille</th><th>Couleur</th><th>Type</th><th>Date d'ajout</th></tr>";

            // Parcourir les résultats de la requête
            while (query.next()) {
            QString idArticle = query.value("ID_ARTICLE").toString();
            QString nom = query.value("NOM_A").toString();
            QString description = query.value("DESCRIPTIONN").toString();
            double prix = query.value("PRIX").toDouble();
            QString categorie = query.value("CATEGORIE").toString();
            QString taille = query.value("TAILLE").toString();
            QString couleur = query.value("COULEUR").toString(); // Couleurs sous forme de chaîne unique
            QString type = query.value("TYPE").toString();
            QString dateAjout = query.value("DATE_AJOUT").toDate().toString("yyyy-MM-dd");

            // Ajouter une ligne pour chaque article en rupture de stock
            htmlCode += "<tr><td>" + idArticle + "</td><td>" + nom + "</td><td>" + description + "</td><td>" + QString::number(prix, 'f', 2) + "</td><td>" + categorie + "</td><td>" + taille + "</td><td>" + couleur + "</td><td>" + type + "</td><td>" + dateAjout + "</td></tr>";
        }

        // Fin du tableau HTML
        htmlCode += "</table></body></html>";

        // Créer un document QTextDocument pour générer le PDF
        QTextDocument document;
        document.setHtml(htmlCode);

        // Créer un writer PDF pour écrire dans le fichier
        QPdfWriter writer(&file);
        writer.setPageSize(QPageSize(QPageSize::A4)); // Utiliser QPageSize::A4
        writer.setPageMargins(QMarginsF(10, 0, 0, 0));

        // Imprimer le document sur le fichier PDF
        document.print(&writer);

        // Fermer le fichier après génération du PDF
        file.close();
        return true;
    } else {
        return false;
    }
}


void MainWindow::on_PDF_clicked() {
    // Générer le PDF des articles en rupture de stock
    if (generatePdf()) {
        QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/rupture_stock.pdf";
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la génération du PDF.");
    }
}

//chatbot
void MainWindow::on_pushButton_chatbot_query_clicked()
{
    QString query = ui->lineEdit_chatbot_query->text();

    qDebug() << "Button clicked: on_pushButton_chatbot_query_clicked";

    if (query.isEmpty()) {
        qDebug() << "No query entered.";
        QMessageBox::warning(this, "Input Error", "Please enter a query.");
        return;
    }

    qDebug() << "Query entered by user:" << query;

    QJsonObject json;
    json["model"] = "mistral";

    QJsonObject message;
    message["role"] = "user";
    message["content"] = query;

    QJsonArray messages;
    messages.append(message);

    json["messages"] = messages;

    QJsonDocument doc(json);
    qDebug() << "Request JSON prepared:" << doc.toJson(QJsonDocument::Indented);

    QUrl url("http://localhost:11434/v1/chat/completions"); // Adjust if the endpoint is different
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "Network request prepared with URL:" << url.toString();

    if (!networkManager) {
        networkManager = new QNetworkAccessManager(this);
        qDebug() << "NetworkAccessManager initialized.";
    }

    // Ensure proper signal handling
    disconnect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);

    qDebug() << "Sending POST request to server...";
    networkManager->post(request, doc.toJson());
}



void MainWindow::handleChatbotReply(QNetworkReply* reply)
{
    qDebug() << "handleChatbotReply triggered.";

    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg = reply->errorString();
        qDebug() << "Network error occurred:" << errorMsg;
        QMessageBox::critical(this, "Error", "Failed to communicate with Ollama server: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    qDebug() << "Raw response data received:" << responseData;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (jsonResponse.isNull()) {
        qDebug() << "Failed to parse JSON response.";
        QMessageBox::critical(this, "Error", "Invalid JSON response from server.");
        reply->deleteLater();
        return;
    }

    QJsonObject responseObject = jsonResponse.object();
    qDebug() << "Parsed JSON response:" << jsonResponse.toJson(QJsonDocument::Indented);

    if (responseObject.contains("choices") && responseObject["choices"].isArray()) {
        QJsonArray choicesArray = responseObject["choices"].toArray();
        if (!choicesArray.isEmpty() && choicesArray[0].isObject()) {
            QJsonObject firstChoice = choicesArray[0].toObject();
            if (firstChoice.contains("message") && firstChoice["message"].isObject()) {
                QJsonObject messageObject = firstChoice["message"].toObject();
                if (messageObject.contains("content") && messageObject["content"].isString()) {
                    QString chatbotResponse = messageObject["content"].toString();
                    qDebug() << "Chatbot response:" << chatbotResponse;
                    ui->textEdit_chatbot_response->setText(chatbotResponse);
                    reply->deleteLater();
                    return;
                }
            }
        }
    }

    qDebug() << "No valid response found in JSON.";
    ui->textEdit_chatbot_response->setText("No valid response from chatbot.");
    reply->deleteLater();
}


void MainWindow::applyStyleSheet()
{

   // this->setStyleSheet(styleSheet); // Appliquer à la fenêtre principale.

    // Ajouter un exemple de contenu dans statsLabel
    QLabel *statsLabel = findChild<QLabel *>("statsLabel");
    if (statsLabel) {
        statsLabel->setText("Femmes = 2\nHommes = 5\nEnfants = 2"); // Exemple de texte
        statsLabel->setAlignment(Qt::AlignLeft); // Alignement du texte
    }
    // Configurer le placeholder pour lineEdit_chatbot_query
    QLineEdit *lineEdit = findChild<QLineEdit *>("lineEdit_chatbot_query");
    if (lineEdit) {
        lineEdit->setPlaceholderText("Tapez votre message..."); // Texte d'invite
    }

    // Configurer le texte de la flèche pour pushButton_chatbot_query
    QPushButton *button = findChild<QPushButton *>("pushButton_chatbot_query");
    if (button) {
        button->setText("→"); // Icône fléchée
        button->setCursor(Qt::PointingHandCursor); // Curseur en forme de main au survol
    }

    // Positionner dynamiquement le bouton dans le lineEdit
    if (lineEdit && button) {
        button->setParent(lineEdit); // Associer le bouton au QLineEdit
        button->move(lineEdit->width() - button->width() - 10, (lineEdit->height() - button->height()) / 2);

        // Repositionner le bouton si le contenu ou la taille du QLineEdit change
        connect(lineEdit, &QLineEdit::textChanged, this, [=]() {
            button->move(lineEdit->width() - button->width() - 10, (lineEdit->height() - button->height()) / 2);
        });
    }
}

void MainWindow::setupLineEditCompletion()
{
    // Liste des valeurs autorisée
    QStringList valeursAutorisees = {"Chemise", "Pantalon", "Veste", "Robe", "Pull", "Jupe"};

    // Configurer le QCompleter
    QCompleter *completer = new QCompleter(valeursAutorisees, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // Auto-complétion insensible à la casse

    // Associer le completer au lineEdit_NOM
    ui->lineEdit_NOM->setCompleter(completer);
}


//arduinors
void MainWindow::readFromArduino() {
    QByteArray data = arduino.readFromArduino();
    QString input = QString::fromUtf8(data).trimmed(); // Convert to QString and trim whitespace

    qDebug() << "Received from Arduino:" << input;

    QString prefix = "ID envoye a Qt: ";
    QString responsePrefix = "Received from Qt: MSG:";

    if (input.startsWith(prefix)) {
        QString employeeId = input.mid(prefix.length()).trimmed();

        qDebug() << "Extracted Employee ID:" << employeeId;

        bool isNumeric;
        int idValue = employeeId.toInt(&isNumeric);
        if (employeeId.length() == 8 && isNumeric && idValue > 0) {
            Employe employee;
            employee.setIdEmploye(employeeId);

            if (employee.load()) {
                updateEmployeeStatus(employee); // Call the update function
                qDebug() << "Employee found:" << employeeId; // Log employee found
            } else {
                QString message = "Employe non trouve";
                arduino.writeToArduino(("MSG:" + message).toUtf8());
                qDebug() << "Employee not found for ID:" << employeeId;
            }
        } else {
            QString message = "ID invalide";
            arduino.writeToArduino(("MSG:" + message).toUtf8());
            qDebug() << "Invalid ID format (not 8 digits or non-numeric):" << employeeId;
        }
    } else if (input.startsWith(responsePrefix)) {
        // Handle the message received from Arduino
        QString responseMessage = input.mid(responsePrefix.length()).trimmed();

        // Log the message received from Arduino
        qDebug() << "Message received from Arduino:" << responseMessage;

        // You can now process this message further or update any necessary state in Qt
        // For example, if you want to update UI components or trigger actions based on the message
    } else {
        qDebug() << "Unexpected input from Arduino:" << input; // Log unexpected input
    }
}




void MainWindow::updateEmployeeStatus(Employe &employee) {
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString newPresence;
    QString message;

    // Toggle presence status
    if (employee.getPresence() == "Absent") {
        newPresence = "Present";
        message = "Bonjour " + employee.getPrenom() + " " + employee.getNom() + " at " + currentTime;
        employee.setHeuresSupplementaires(employee.getHeuresSupplementaires() + 8); // Increment overtime hours
    } else if (employee.getPresence() == "Present") {
        newPresence = "Absent";
        message = "Au revoir " + employee.getPrenom() + " " + employee.getNom() + " at " + currentTime;
    } else {
        QMessageBox::warning(this, "Erreur", "Statut de présence inconnu.");
        return; // Abort if presence status is invalid
    }

    // Update employee presence
    employee.setPresence(newPresence);

    // Update the database
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYE SET Presence = :presence, Heures_supplementaires = :heures_supplementaires "
        "WHERE Id_employe = :id_employe");
    query.bindValue(":presence", employee.getPresence());
    query.bindValue(":heures_supplementaires", employee.getHeuresSupplementaires());
    query.bindValue(":id_employe", employee.getIdEmploye());

    if (query.exec()) {
        afficherEmployes(); // Refresh the displayed employees
        QMessageBox::information(this, "Succès", "Présence et heures supplémentaires mises à jour.");
        qDebug() << message;

        arduino.writeToArduino(("MSG:" + message).toUtf8());
    } else
    {
        QMessageBox::warning(this, "Erreur", "La mise à jour de la base de données a échoué: " + query.lastError().text());
        qDebug() << "Database error:" << query.lastError().text();
    }
}


//duaa

void MainWindow::on_ajouterTransaction_clicked() {
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
    QString methodePaiement = ui->box->currentText();
    if (methodePaiement.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une méthode de paiement.");
        return;
    }

    if (newTransaction.ajouter(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status)) {
        ui->tableViewtransaction->setModel(transactionModel.afficher());
        transactionModel.addToHistory("Ajouter",idTransaction);
        QMessageBox::information(this, "Succès", "Transaction ajoutée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de la transaction.");
    }
}

void MainWindow::on_supprimer_clickedt() {
    int IDTRANSACTION = ui->l7->text().toInt();
    Transaction newTransaction;
    if (newTransaction.existeDeja(IDTRANSACTION)) {
        bool test = transactionModel.supprimer(IDTRANSACTION);

    if (test) {

        ui->tableViewtransaction->setModel(transactionModel.afficher());
        transactionModel.addToHistory("Supprimer",IDTRANSACTION);

        QMessageBox::information(this, QObject::tr("Succès"),
                                 QObject::tr("Suppression effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("La suppression a échoué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    }
    else{
        QMessageBox::critical(this, QObject::tr("Erreur"),
                              QObject::tr("transaction pas trouve."), QMessageBox::Cancel);
    }


}

void MainWindow::on_modifier_clicked() {

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


    Transaction updatedTransaction(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status);

    bool success = updatedTransaction.modifier(idTransaction, dateAjout, listeArticles, taxes, reduction, montant, methodePaiement, cin, status);

    if (success) {
        transactionModel.addToHistory("modifier",idTransaction);
        ui->tableViewtransaction->setModel(transactionModel.afficher());
        QMessageBox::information(this, "Succès", "Transaction modifiée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la modification de la transaction.");
    }
}
void MainWindow::on_pdf_clicked() {
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichier.isEmpty()) {

        QSqlQueryModel *model = transactionModel.afficher();


        Transaction transaction;
        transaction.exporterPDF(nomFichier, model);


        delete model;
        transactionModel.addToHistory("PDF",0);
    }
}
void MainWindow::on_tri_clicked(){

    QSqlQueryModel *model = transactionModel.trierParDate();


    if (model && model->rowCount() > 0) {

        ui->tableViewtransaction->setModel(model);
        transactionModel.addToHistory("Trier",0);
        QMessageBox::information(this, "Tri par Date", "Transactions triées du plus récent au plus ancien.");
    } else {

        QMessageBox::warning(this, "Aucune donnée", "Aucune transaction trouvée.");
    }
}
void MainWindow::on_rechercherTransaction_clicked() {
    int idTransaction = ui->recherche_2->text().toInt();
    if (idTransaction == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (entier) pour la recherche.");
        return;
    }


    QSqlQueryModel* model = transactionModel.rechercher(idTransaction);

    if (model && model->rowCount() > 0) {

        ui->tableViewtransaction->setModel(model);
        transactionModel.addToHistory("Rechercher",idTransaction);
        QMessageBox::information(this, "Recherche réussie", "La transaction a été trouvée.");
    } else {

        QMessageBox::warning(this, "Erreur", "La transaction n'a pas été trouvée dans la base de données.");
        delete model;
    }
}
void MainWindow::on_statistiqueButtonTransaction_clicked() {
    QMap<QString, double> stats = transactionModel.statistiquesParStatut();


    double totalTransactions = 0;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        totalTransactions += it.value();
    }


    QLayoutItem* item;
    while ((item = ui->transactionLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }


    QPieSeries *series = new QPieSeries();


    int index = 0;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it, ++index) {
        QString label = QString("%1: %2%").arg(it.key()).arg(it.value(), 0, 'f', 1);
        QPieSlice *slice = series->append(label, it.value());


        if (index == 0) {
            slice->setBrush(QColor(212, 153, 162));
        } else if (index == 1) {
            slice->setBrush(QColor(209, 168, 213));
        }
    }


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des transactions par statut");


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    ui->transactionLayout->addWidget(chartView);
    transactionModel.addToHistory("Statistique",0);

}

void MainWindow::afficherHistoriqueTransaction() {
    QString cheminFichier = "C:/DELL/Desktop/employe/historique_transaction.txt";
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
    QString cheminFichier = "C:/DELL/Desktop/employe/historique_transaction.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
    QMessageBox::information(this, "Historique", "Les actions ont été enregistrées dans l'historique des transactions.");
}



void MainWindow::on_stop_voc_clicked()
{
    qDebug() << "Stop vocale button clicked.";
    vocaleHandler->stopAudioCapture();
}


void MainWindow::on_vocale_clicked()
{

    qDebug() << "Vocale button clicked.";
    vocaleHandler->startAudioCapture();
}


#include <cstdlib> // Pour utiliser rand() et srand()
#include <ctime>   // Pour initialiser le générateur de nombres aléatoires

void MainWindow::on_stop_voc_2_clicked() {
    // Lire la valeur de détection depuis l'interface utilisateur
    int detection = ui->detection->text().toInt();

    if (detection == 0) {
        // Si detection est 1, envoyer "PAS DETECTION" à l'Arduinod
        QString message = "PAS DETECTION";
        QByteArray data = message.toUtf8();
        qDebug() << data;
        A.write_to_arduinod(data);
        ui->detection->clear(); // Réinitialiser le champ de saisie
    } else if(detection ==1){
        // Si detection est 0, récupérer un employé aléatoire avec état "présent"
        QSqlQuery query;

        // Préparer la requête SQL pour sélectionner les employés présents
        query.prepare("SELECT prenom FROM employe WHERE PRESENCE = 'Present'");

        if (query.exec()) {
            // Stocker tous les noms d'employés dans une liste
            QStringList employeeNames;
            while (query.next()) {
                employeeNames << query.value(0).toString();
            }

            // Vérifier si des employés sont trouvés
            if (!employeeNames.isEmpty()) {
                // Sélectionner un employé au hasard
                std::srand(std::time(nullptr)); // Initialiser le générateur aléatoire
                int randomIndex = std::rand() % employeeNames.size();
                QString randomEmployee = employeeNames[randomIndex];

                // Envoyer le nom de l'employé sélectionné à l'Arduinod
                QByteArray data = randomEmployee.toUtf8();
                qDebug() << "Nom employé envoyé : " << data;
                A.write_to_arduinod(data);
                ui->detection->clear(); // Réinitialiser le champ de saisie


            }
        } else {
            // Gérer une erreur dans l'exécution de la requête SQL
            qDebug() << "Erreur dans l'exécution de la requête : " << query.lastError().text();

        }
    }
}


//ahmed
void MainWindow::on_btnAjouter_clicked()
{
    QString cin_client = ui->CIN_input->text();
    QString numero_c = ui->Numero_input->text();
    QString nomc = ui->NOM_input->text();
    QString prenomc = ui->PRENOM_input->text();
    QDate date_inscription = ui->DATE_input->date(); // Assume you have a QDateEdit for this
    QString mail_c = ui->MAIL_input->text();        // Assume you have a QLineEdit for this

    client c(cin_client, numero_c, nomc, prenomc, mail_c,date_inscription);
    if (c.cinExists(cin_client)) {
        QMessageBox::warning(this, "Duplicate CIN", "Client with CIN already exists.");
        return;
    }

    if (c.ajouter()) {
        QMessageBox::information(this, "Success", "Client added successfully.");
        ui->tableViewclient->setModel(c.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Failed to add client.");
    }
}

void MainWindow::on_modifiercl_clicked()
{
    QString cin_client = ui->CIN_input->text();
    QString numero_c = ui->Numero_input->text();
    QString nomc = ui->NOM_input->text();
    QString prenomc = ui->PRENOM_input->text();
    QDate date_inscription = ui->DATE_input->date(); // Assume you have a QDateEdit for this
    QString mail_c = ui->MAIL_input->text();        // Assume you have a QLineEdit for this

    if (cin_client.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "CIN must not be empty.");
        return;
    }

    client c(cin_client, numero_c, nomc, prenomc,mail_c, date_inscription);
    if (c.modifier()) {
        QMessageBox::information(this, "Success", "Client modified successfully.");
        ui->tableViewclient->setModel(c.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify client. Ensure CIN exists.");
    }

    // Clear inputs
    ui->CIN_input->clear();
    ui->Numero_input->clear();
    ui->NOM_input->clear();
    ui->PRENOM_input->clear();
    ui->DATE_input->clear();
    ui->MAIL_input->clear();
}

void MainWindow::on_supprimercl_clicked()
{
    QString cin_client = ui->CIN_input->text();
    client c;

    if (c.supprimer(cin_client)) {
        QMessageBox::information(this, "Success", "Client deleted successfully.");
        ui->tableViewclient->setModel(c.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete client.");
    }
}

void MainWindow::on_afficher_clicked()
{
    client c;
    ui->tableViewclient->setModel(c.afficher());
}


void MainWindow::on_searchButton_clicked()
{
    // Get the search term from the lineEdit (now named searchInput)
    QString searchTerm = ui->searchInput->text();
    QString searchColumn;

    // Determine which column to search based on radio buttons
    if (ui->radio_CIN->isChecked()) {
        searchColumn = "CIN_client";
    } else if (ui->radio_Nom->isChecked()) {
        searchColumn = "nom_c";
    } else if (ui->radio_Mail->isChecked()) {
        searchColumn = "mail_c";
    }

    // Prepare the query with placeholders
    QString queryStr = QString("SELECT CIN_client, nom_c, prenom_c, numero_c,mail_c,date_inscription FROM CLIENT WHERE LOWER(%1) LIKE LOWER(:searchTerm)").arg(searchColumn);
    qDebug() << "Executing query: " << queryStr;

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (query.exec()) {
        qDebug() << "Query executed successfully";

        // Create a model to hold the query results
        QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery(query);

        // Set the model to the tableViewclient (ensure tableViewclient_2 is a QtableViewclient)
        ui->tableViewclient_2->setModel(model);  // Make sure this is a QtableViewclient, not QTableWidget
    } else {
        // Print query failure message if it fails
        qDebug() << "Query failed: " << query.lastError().text();
    }
}

void MainWindow::on_statsButton_clicked()
{
    int normalCount = 0, vipCount = 0;
    int nomCount = 0, prenomCount = 0, numeroCount = 0;

    // Query to get data from CLIENT table
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT");
    if (query.exec()) {
        while (query.next()) {
            int purchasesCount = query.value("purchases_count").toInt();
            QString clientType = query.value("type_client").toString();

            // If client has 10 or more purchases, change their type to VIP
            if (purchasesCount >= 10 && clientType == "Normal") {
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE CLIENT SET type_client = 'VIP' WHERE id = :id");
                updateQuery.bindValue(":id", query.value("id"));
                updateQuery.exec();

                clientType = "VIP"; // Update local variable to reflect change
            }

            // Count Normal and VIP clients
            if (clientType == "Normal") normalCount++;
            else if (clientType == "VIP") vipCount++;

            // Count name, surname, and number fields
            QString clientName = query.value("nom_c").toString();
            QString clientPrenom = query.value("prenom_c").toString();
            QString clientNumber = query.value("numero_c").toString();

            if (!clientName.isEmpty()) nomCount++;
            if (!clientPrenom.isEmpty()) prenomCount++;
            if (!clientNumber.isEmpty()) numeroCount++;
        }
    }

    // Calculate total clients
    int totalCount = normalCount + vipCount;

    // Create the pie chart series
    auto *series = new QPieSeries();
    series->setHoleSize(0.35);

    // Add slices with percentage labels
    QPieSlice *normalSlice = series->append("Normal", normalCount);
    QPieSlice *vipSlice = series->append("VIP", vipCount);

    // Calculate percentages and set labels
    auto formatLabel = [totalCount](int count) {
        double percentage = (count / static_cast<double>(totalCount)) * 100;
        return QString("%1 (%2%)").arg(count).arg(QString::number(percentage, 'f', 1));
    };

    normalSlice->setLabel(formatLabel(normalCount));
    vipSlice->setLabel(formatLabel(vipCount));

    // Make labels visible
    normalSlice->setLabelVisible(true);
    vipSlice->setLabelVisible(true);

    // Create the chart
    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("<h2 style='color:darkblue'>Statistiques des Clients</h2>");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Create the chart view
    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear any previous layout in the QFrame
    QLayout *oldLayout = ui->chartLayout->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget(); // Delete any widgets in the layout
            delete item;           // Delete the layout item
        }
        delete oldLayout;
    }

    // Set up a new layout in the QFrame
    QVBoxLayout *layout = new QVBoxLayout(ui->chartLayout);
    layout->addWidget(chartView);

    // Add details section
    QLabel *details = new QLabel(ui->chartLayout);
    details->setText(
        QString("<h3 style='color:darkgreen'>Détails des Statistiques</h3>"
                "<ul>"
                "<li><b>Nombre de Noms:</b> %1</li>"
                "<li><b>Nombre de Prénoms:</b> %2</li>"
                "<li><b>Nombre de Numéros:</b> %3</li>"
                "<li><b>Normal Clients:</b> %4</li>"
                "<li><b>VIP Clients:</b> %5</li>"
                "</ul>")
            .arg(nomCount)
            .arg(prenomCount)
            .arg(numeroCount)
            .arg(normalCount)
            .arg(vipCount));
    details->setWordWrap(true);
    layout->addWidget(details);

    // Apply the new layout to the QFrame
    ui->chartLayout->setLayout(layout);
}


void MainWindow::on_Telecharger_button_clicked()
{
    // Query to get the number of clients and total purchases this month
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS client_count, SUM(purchases_count) AS total_purchases "
                  "FROM CLIENT "
                  "WHERE EXTRACT(MONTH FROM date_inscription) = EXTRACT(MONTH FROM SYSDATE) "
                  "AND EXTRACT(YEAR FROM date_inscription) = EXTRACT(YEAR FROM SYSDATE)");
    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to execute query to fetch data for the PDF.");
        return;
    }

    int clientCount = 0, totalPurchases = 0;
    if (query.next()) {
        clientCount = query.value("client_count").toInt();
        totalPurchases = query.value("total_purchases").toInt();
    }

    // Ask user to choose file path and name to save PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath() + "/Client_Report_Current_Month.pdf", "PDF Files (*.pdf)");

    // If user cancels, return
    if (filePath.isEmpty()) {
        return;
    }

    // Create a PDF writer object with the selected file path
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setTitle("Client Report - Current Month");

    // Create a QPainter object to paint on the PDF
    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "PDF Error", "Failed to create PDF file.");
        return;
    }

    // Set font and start painting
    QFont font("Arial", 16);  // Increase font size to make it more readable
    painter.setFont(font);

    // Set margins
    int marginLeft = 50;
    int marginTop = 50;
    int lineHeight = 300;  // Space between lines

    // Draw title
    painter.drawText(marginLeft, marginTop, "Client Report - Current Month");

    // Drawing the data on the PDF
    painter.drawText(marginLeft, marginTop + lineHeight, "Number of Clients who made purchases this month: " + QString::number(clientCount));
    painter.drawText(marginLeft, marginTop + 2 * lineHeight, "Total Purchases Made this month: " + QString::number(totalPurchases));

    // Additional creative data: Average purchases per client this month
    if (clientCount > 0) {
        double averagePurchases = static_cast<double>(totalPurchases) / clientCount;
        painter.drawText(marginLeft, marginTop + 3 * lineHeight, "Average Purchases per Client: " + QString::number(averagePurchases, 'f', 2));
    }

    // Include real-time data from Arduino
    painter.drawText(marginLeft, marginTop + 4 * lineHeight, "Total Entries: " + QString::number(totalEntries));
    painter.drawText(marginLeft, marginTop + 5 * lineHeight, "Total Exits: " + QString::number(totalExits));
    painter.drawText(marginLeft, marginTop + 6 * lineHeight, "Current Occupancy: " + QString::number(currentOccupancy));

    // Include the current date
    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");
    painter.drawText(marginLeft, marginTop + 7 * lineHeight, "Date: " + currentDate);

    // End painting
    painter.end();

    // Notify user
    QMessageBox::information(this, "PDF Generated", "The report has been successfully generated and saved.");
}


void MainWindow::on_trier_activated(int index)
{
    QString sortColumn;

    // Map the combo box index to the corresponding database column
    switch (index) {
    case 0:
        sortColumn = "date_inscription";
        break;
    case 1:
        sortColumn = "prenom_c";
        break;
    case 2:
        sortColumn = "nom_c";
        break;
    default:
        qDebug() << "Invalid index selected";
        return;
    }

    // Build the dynamic query for sorting
    QString query = QString(
                        "SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription "
                        "FROM client ORDER BY %1 ASC"
                        ).arg(sortColumn);

    // Execute the query and update the model
    model->setQuery(query);

    // Check for errors
    if (model->lastError().isValid()) {
        qDebug() << "SQL Error:" << model->lastError().text();
    } else {
        qDebug() << "Sorted by" << sortColumn;
    }
}

void MainWindow::on_tableView_2_headerClicked(int section)
{
    QStringList columns = {"CIN_client", "nom_c", "prenom_c", "numero_c", "mail_c", "date_inscription"};

    // Ensure the section index is valid
    if (section < 0 || section >= columns.size()) {
        qDebug() << "Invalid column index clicked:" << section;
        return;
    }

    // Determine column name
    QString columnName = columns[section];

    // Toggle sort order
    QString order = sortOrderAscending ? "ASC" : "DESC";

    // Build the dynamic query for sorting
    QString query = QString(
                        "SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription "
                        "FROM client ORDER BY %1 %2"
                        ).arg(columnName, order);

    // Execute the query and update the model
    model->setQuery(query);

    // Check for errors
    if (model->lastError().isValid()) {
        qDebug() << "SQL Error:" << model->lastError().text();
    } else {
        qDebug() << "Sorted by column:" << columnName << "Order:" << order;
    }

    // Toggle the sorting order for the next click
    sortOrderAscending = !sortOrderAscending;
}

void MainWindow::classifyClients() {
    QSqlQuery query;

    // Step 1: Retrieve all clients and their purchase counts
    query.prepare("SELECT CIN_client, purchases_count FROM CLIENT");

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve client data: " + query.lastError().text());
        return;
    }

    // Step 2: Update client type based on purchases_count
    while (query.next()) {
        QString cinClient = query.value("CIN_client").toString();
        int purchasesCount = query.value("purchases_count").toInt();

        QString clientType = (purchasesCount >= 10) ? "VIP" : "Normal";

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE CLIENT SET type_client = :type_client WHERE CIN_client = :cin_client");
        updateQuery.bindValue(":type_client", clientType);
        updateQuery.bindValue(":cin_client", cinClient);

        if (!updateQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update client type: " + updateQuery.lastError().text());
            return;
        }
    }

    QMessageBox::information(this, "Success", "Client classification updated successfully.");
}

// Function to update purchases_count for a client
void MainWindow::updateClientPurchase(const QString &cin, int purchaseIncrement) {
    QSqlQuery query;

    // Increment the purchases_count
    query.prepare("UPDATE CLIENT SET purchases_count = purchases_count + :increment WHERE CIN_client = :cin");
    query.bindValue(":increment", purchaseIncrement);
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update purchases count: " + query.lastError().text());
        return;
    }

    // Update VIP status if purchases_count exceeds or equals 10
    query.prepare("UPDATE CLIENT SET type_client = 'VIP' WHERE CIN_client = :cin AND purchases_count >= 10");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update client status to VIP: " + query.lastError().text());
    }
    classifyClients();
}

bool MainWindow::sendEmailUsingGmail(const QString &to, const QString &subject, const QString &body) {
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 465;  // SSL port
    QString username = "ahmedghabri007@gmail.com";
    QString password = "xftj hhfi dmef wnfr";

    QSslSocket socket;
    socket.connectToHostEncrypted(smtpServer, smtpPort);

    if (!socket.waitForConnected()) {
        qDebug() << "Error connecting to server:" << socket.errorString();
        return false;
    }

    socket.write("HELO localhost\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("AUTH LOGIN\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write(QByteArray(username.toUtf8()).toBase64() + "\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write(QByteArray(password.toUtf8()).toBase64() + "\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("MAIL FROM:<" + username.toUtf8() + ">\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("RCPT TO:<" + to.toUtf8() + ">\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("DATA\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("From: " + username.toUtf8() + "\r\n");
    socket.write("To: " + to.toUtf8() + "\r\n");
    socket.write("Subject: " + subject.toUtf8() + "\r\n");
    socket.write("\r\n");
    socket.write(body.toUtf8() + "\r\n.\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    socket.write("QUIT\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();

    qDebug() << "Email sent successfully to:" << to;
    socket.close();
    return true;
}

void MainWindow::on_envoyer_mail_clicked() {
    QString selectedType = ui->comb_client->currentText();

    QSqlQuery query;
    query.prepare("SELECT mail_c, type_client FROM CLIENT WHERE mail_c IS NOT NULL AND type_client = :type");
    query.bindValue(":type", selectedType);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch clients from the database.");
        return;
    }

    int successCount = 0;
    int failureCount = 0;

    while (query.next()) {
        QString email = query.value(0).toString();
        QString typeClient = query.value(1).toString();

        QString subject, message;
        if (typeClient == "Normal") {
            subject = "Exclusive Sales!";
            message = "Dear customer,\n\nDon't miss out on our exciting sales this season!";
        } else if (typeClient == "VIP") {
            subject = "Upcoming Events and Collections!";
            message = "Dear valued VIP customer,\n\nWe're excited to share upcoming events and our new collection with you!";
        } else {
            continue;  // Skip unsupported types
        }

        if (sendEmailUsingGmail(email, subject, message)) {
            successCount++;
        } else {
            failureCount++;
            qDebug() << "Failed to send email to:" << email;
        }
    }

    QMessageBox::information(
        this, "Email Campaign Summary",
        QString("Emails sent successfully: %1\nFailed to send: %2")
            .arg(successCount)
            .arg(failureCount)
        );
}void MainWindow::affichageClient()
{
    if (!model) {
        model = new QSqlQueryModel(this);
    }

    model->setQuery("SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription FROM client");
    ui->tableViewclient_2->setModel(model);

    // Enable clickable headers
    ui->tableViewclient_2->horizontalHeader()->setSectionsClickable(true);
}


void MainWindow::on_precedent2_clicked()
{
      ui->stackedWidgetSign->setCurrentIndex(0);

}


void MainWindow::on_precedent3_clicked()
{
    ui->stackedWidgetSign->setCurrentIndex(1);

}


void MainWindow::on_presedent4_clicked()
{
    ui->stackedWidgetSign->setCurrentIndex(1);

}
void MainWindow::updateDisplay(int totalEntries, int totalExits, int currentOccupancy)
{
    this->totalEntries = totalEntries;
    this->totalExits = totalExits;
    this->currentOccupancy = currentOccupancy;

    // Update the labels in your UI with the new data
    ui->entryLabel->setText("Total Entries: " + QString::number(totalEntries));
    ui->exitLabel->setText("Total Exits: " + QString::number(totalExits));
    ui->occupancyLabel->setText("Current Occupancy: " + QString::number(currentOccupancy));
}

void MainWindow::on_annuler_2_clicked()
{
    ui->l1->clear();
    ui->l7_2->clear();
    ui->l2->clear();
    ui->l4->clear();
    ui->l6->clear();
    ui->l8->clear();
    ui->box->setCurrentIndex(0);




}


void MainWindow::on_buttonanuuler_clicked()
{
    ui->lineEditsupp->clear();


}



void MainWindow::on_pushButton_12_clicked()
{
    ui->lineEdit_CODE->clear();
    ui->lineEdit_NOM->clear();
    ui->dateTimeEdit_2->clear();
    ui->lineEdit_DESCRIPTION->clear();

    ui->radioButton_Automne->setChecked(false);
    ui->radioButton_Hiver->setChecked(false);
    ui->radioButton_Ete->setChecked(false);
    ui->radioButton_Printemps->setChecked(false);

    ui->doubleSpinBox_2->clear();
    ui->spinBox_Quantite->clear();


    ui->checkBox_Blanc->setChecked(false);
    ui->checkBox_Noir->setChecked(false);
    ui->checkBox_Bleu->setChecked(false);
    ui->checkBox_Gris->setChecked(false);
    ui->checkBox_Rouge->setChecked(false);
    ui->checkBox_Beige->setChecked(false);
    ui->checkBox_Vert->setChecked(false);
    ui->checkBox_Rose->setChecked(false);
    ui->checkBox_Marron->setChecked(false);
    ui->checkBox_Jaune->setChecked(false);
    ui->checkBox_Violet->setChecked(false);
    ui->checkBox_Orange->setChecked(false);

}

