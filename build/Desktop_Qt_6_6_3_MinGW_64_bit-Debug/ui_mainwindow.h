/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_17;
    QTabWidget *tabWidget_client;
    QWidget *tabWidgetPage1;
    QPushButton *btnAjouter;
    QWidget *widget_24;
    QLabel *label_78;
    QLineEdit *CIN_input;
    QLabel *label_79;
    QLineEdit *NOM_input;
    QLabel *label_80;
    QLineEdit *PRENOM_input;
    QLabel *label_112;
    QLineEdit *Numero_input;
    QTableView *tableView;
    QPushButton *modifier;
    QPushButton *supprimer;
    QPushButton *afficher;
    QWidget *tabWidgetPage2;
    QLabel *label_110;
    QLineEdit *lineEdit_CIN_2;
    QRadioButton *radio_CIN;
    QRadioButton *radio_Nom;
    QRadioButton *radio_Mail;
    QTableWidget *tableWidget_3;
    QWidget *widget_26;
    QLabel *label_121;
    QComboBox *trier;
    QProgressBar *progressBar;
    QPushButton *Telecharger_button;
    QWidget *tab_5;
    QLabel *label_118;
    QLCDNumber *lcdNumber;
    QPushButton *nb_client;
    QWidget *tab_6;
    QFrame *chart_graph;
    QWidget *envoyersms;
    QComboBox *combo_reservation;
    QLabel *label_119;
    QLabel *label_120;
    QPushButton *envoyer_mail;
    QTextEdit *mail_titre;
    QLabel *label_111;
    QLineEdit *numero;
    QWidget *tab_7;
    QTableView *afficher_historique;
    QProgressBar *progressBar_2;
    QPushButton *Telecharger_historique;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1230, 744);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget_17 = new QWidget(centralwidget);
        widget_17->setObjectName("widget_17");
        widget_17->setGeometry(QRect(-20, 30, 1311, 851));
        widget_17->setStyleSheet(QString::fromUtf8("background-color: rgb(251, 251, 243);\n"
"font: 700 9pt \"Segoe UI\";\n"
"border: 1px solid #000; \n"
"border-color: rgb(251, 251, 243);\n"
"\n"
"\n"
""));
        tabWidget_client = new QTabWidget(widget_17);
        tabWidget_client->setObjectName("tabWidget_client");
        tabWidget_client->setEnabled(true);
        tabWidget_client->setGeometry(QRect(70, 20, 1211, 711));
        tabWidget_client->setMinimumSize(QSize(1211, 711));
        tabWidget_client->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 153, 162);\n"
"border-radius: 50px;\n"
" border: 1px solid #000; \n"
""));
        tabWidget_client->setTabBarAutoHide(false);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName("tabWidgetPage1");
        btnAjouter = new QPushButton(tabWidgetPage1);
        btnAjouter->setObjectName("btnAjouter");
        btnAjouter->setGeometry(QRect(730, 280, 171, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(9);
        font.setBold(true);
        font.setItalic(false);
        btnAjouter->setFont(font);
        btnAjouter->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        widget_24 = new QWidget(tabWidgetPage1);
        widget_24->setObjectName("widget_24");
        widget_24->setGeometry(QRect(70, 90, 621, 421));
        widget_24->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 153, 162);\n"
"    border-radius: 50px;\n"
"    border: 1px solid #000; \n"
"    padding: 5px;\n"
""));
        label_78 = new QLabel(widget_24);
        label_78->setObjectName("label_78");
        label_78->setGeometry(QRect(50, 180, 71, 31));
        CIN_input = new QLineEdit(widget_24);
        CIN_input->setObjectName("CIN_input");
        CIN_input->setGeometry(QRect(50, 220, 221, 31));
        label_79 = new QLabel(widget_24);
        label_79->setObjectName("label_79");
        label_79->setGeometry(QRect(40, 30, 71, 41));
        NOM_input = new QLineEdit(widget_24);
        NOM_input->setObjectName("NOM_input");
        NOM_input->setGeometry(QRect(30, 90, 221, 31));
        label_80 = new QLabel(widget_24);
        label_80->setObjectName("label_80");
        label_80->setGeometry(QRect(400, 30, 91, 31));
        PRENOM_input = new QLineEdit(widget_24);
        PRENOM_input->setObjectName("PRENOM_input");
        PRENOM_input->setGeometry(QRect(360, 90, 221, 31));
        label_112 = new QLabel(widget_24);
        label_112->setObjectName("label_112");
        label_112->setGeometry(QRect(40, 290, 121, 41));
        Numero_input = new QLineEdit(widget_24);
        Numero_input->setObjectName("Numero_input");
        Numero_input->setGeometry(QRect(40, 350, 221, 31));
        tableView = new QTableView(tabWidgetPage1);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(770, 20, 391, 221));
        modifier = new QPushButton(tabWidgetPage1);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(730, 350, 171, 51));
        modifier->setFont(font);
        modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        supprimer = new QPushButton(tabWidgetPage1);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(730, 430, 171, 51));
        supprimer->setFont(font);
        supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        afficher = new QPushButton(tabWidgetPage1);
        afficher->setObjectName("afficher");
        afficher->setGeometry(QRect(930, 350, 171, 51));
        afficher->setFont(font);
        afficher->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        tabWidget_client->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName("tabWidgetPage2");
        label_110 = new QLabel(tabWidgetPage2);
        label_110->setObjectName("label_110");
        label_110->setGeometry(QRect(100, 50, 211, 51));
        lineEdit_CIN_2 = new QLineEdit(tabWidgetPage2);
        lineEdit_CIN_2->setObjectName("lineEdit_CIN_2");
        lineEdit_CIN_2->setGeometry(QRect(100, 110, 271, 31));
        lineEdit_CIN_2->setStyleSheet(QString::fromUtf8(""));
        lineEdit_CIN_2->setMaxLength(8);
        radio_CIN = new QRadioButton(tabWidgetPage2);
        radio_CIN->setObjectName("radio_CIN");
        radio_CIN->setGeometry(QRect(400, 70, 131, 20));
        radio_Nom = new QRadioButton(tabWidgetPage2);
        radio_Nom->setObjectName("radio_Nom");
        radio_Nom->setGeometry(QRect(610, 70, 131, 20));
        radio_Nom->setStyleSheet(QString::fromUtf8(""));
        radio_Mail = new QRadioButton(tabWidgetPage2);
        radio_Mail->setObjectName("radio_Mail");
        radio_Mail->setGeometry(QRect(810, 70, 131, 20));
        tableWidget_3 = new QTableWidget(tabWidgetPage2);
        if (tableWidget_3->columnCount() < 8)
            tableWidget_3->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget_3->rowCount() < 4)
            tableWidget_3->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(3, __qtablewidgetitem11);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(220, 190, 801, 181));
        tableWidget_3->setStyleSheet(QString::fromUtf8(""));
        widget_26 = new QWidget(tabWidgetPage2);
        widget_26->setObjectName("widget_26");
        widget_26->setGeometry(QRect(40, 450, 401, 121));
        widget_26->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 153, 162);\n"
"    border-radius: 50px;\n"
"    border: 1px solid #000; \n"
"    padding: 5px;\n"
"\n"
""));
        label_121 = new QLabel(widget_26);
        label_121->setObjectName("label_121");
        label_121->setGeometry(QRect(30, 10, 141, 31));
        label_121->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border-color: rgb(211, 152, 161);\n"
"font: 700 8pt \"Segoe UI\";"));
        trier = new QComboBox(widget_26);
        trier->addItem(QString());
        trier->addItem(QString());
        trier->addItem(QString());
        trier->addItem(QString());
        trier->setObjectName("trier");
        trier->setGeometry(QRect(90, 60, 191, 24));
        trier->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 700 8pt \"Segoe UI\";"));
        progressBar = new QProgressBar(tabWidgetPage2);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(870, 540, 271, 24));
        progressBar->setValue(24);
        Telecharger_button = new QPushButton(tabWidgetPage2);
        Telecharger_button->setObjectName("Telecharger_button");
        Telecharger_button->setGeometry(QRect(900, 420, 241, 31));
        Telecharger_button->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        tabWidget_client->addTab(tabWidgetPage2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_118 = new QLabel(tab_5);
        label_118->setObjectName("label_118");
        label_118->setGeometry(QRect(20, 40, 231, 51));
        label_118->setSizeIncrement(QSize(50, 50));
        QPalette palette;
        QBrush brush(QColor(212, 153, 162, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_118->setPalette(palette);
        label_118->setFont(font);
        lcdNumber = new QLCDNumber(tab_5);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(80, 110, 461, 181));
        nb_client = new QPushButton(tab_5);
        nb_client->setObjectName("nb_client");
        nb_client->setGeometry(QRect(650, 120, 251, 181));
        nb_client->setFont(font);
        nb_client->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        tabWidget_client->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        chart_graph = new QFrame(tab_6);
        chart_graph->setObjectName("chart_graph");
        chart_graph->setGeometry(QRect(60, 30, 821, 461));
        chart_graph->setFrameShape(QFrame::Shape::StyledPanel);
        chart_graph->setFrameShadow(QFrame::Shadow::Raised);
        tabWidget_client->addTab(tab_6, QString());
        envoyersms = new QWidget();
        envoyersms->setObjectName("envoyersms");
        combo_reservation = new QComboBox(envoyersms);
        combo_reservation->addItem(QString());
        combo_reservation->addItem(QString());
        combo_reservation->addItem(QString());
        combo_reservation->setObjectName("combo_reservation");
        combo_reservation->setGeometry(QRect(40, 70, 211, 61));
        label_119 = new QLabel(envoyersms);
        label_119->setObjectName("label_119");
        label_119->setGeometry(QRect(40, 40, 171, 16));
        label_120 = new QLabel(envoyersms);
        label_120->setObjectName("label_120");
        label_120->setGeometry(QRect(60, 150, 131, 51));
        envoyer_mail = new QPushButton(envoyersms);
        envoyer_mail->setObjectName("envoyer_mail");
        envoyer_mail->setGeometry(QRect(670, 300, 201, 71));
        envoyer_mail->setFont(font);
        envoyer_mail->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        mail_titre = new QTextEdit(envoyersms);
        mail_titre->setObjectName("mail_titre");
        mail_titre->setGeometry(QRect(50, 210, 441, 271));
        label_111 = new QLabel(envoyersms);
        label_111->setObjectName("label_111");
        label_111->setGeometry(QRect(320, 30, 191, 41));
        numero = new QLineEdit(envoyersms);
        numero->setObjectName("numero");
        numero->setGeometry(QRect(320, 80, 191, 41));
        tabWidget_client->addTab(envoyersms, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        afficher_historique = new QTableView(tab_7);
        afficher_historique->setObjectName("afficher_historique");
        afficher_historique->setGeometry(QRect(40, 60, 881, 371));
        afficher_historique->setFont(font);
        progressBar_2 = new QProgressBar(tab_7);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setGeometry(QRect(40, 530, 231, 23));
        progressBar_2->setValue(24);
        Telecharger_historique = new QPushButton(tab_7);
        Telecharger_historique->setObjectName("Telecharger_historique");
        Telecharger_historique->setGeometry(QRect(840, 450, 191, 31));
        Telecharger_historique->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 168, 213);\n"
""));
        tabWidget_client->addTab(tab_7, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1230, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_client->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnAjouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_78->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        CIN_input->setInputMask(QCoreApplication::translate("MainWindow", "99999999", nullptr));
        label_79->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        label_80->setText(QCoreApplication::translate("MainWindow", "PRENOM", nullptr));
        label_112->setText(QCoreApplication::translate("MainWindow", "Numero", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        afficher->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(tabWidgetPage1), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_110->setText(QCoreApplication::translate("MainWindow", "Recherche avec CIN", nullptr));
        radio_CIN->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        radio_Nom->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        radio_Mail->setText(QCoreApplication::translate("MainWindow", "MAIL", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "MAIL", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Numero", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Date d'inscription", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_121->setText(QCoreApplication::translate("MainWindow", "Trier selon:", nullptr));
        trier->setItemText(0, QString());
        trier->setItemText(1, QCoreApplication::translate("MainWindow", "Date d'inscription", nullptr));
        trier->setItemText(2, QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        trier->setItemText(3, QCoreApplication::translate("MainWindow", "Nom", nullptr));

        trier->setCurrentText(QString());
        Telecharger_button->setText(QCoreApplication::translate("MainWindow", "Telecharger la liste des clients", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(tabWidgetPage2), QCoreApplication::translate("MainWindow", "Liste de client", nullptr));
        label_118->setText(QCoreApplication::translate("MainWindow", "NOMBRE DES CLIENTS:", nullptr));
        nb_client->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Nombre des clients", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        combo_reservation->setItemText(0, QString());
        combo_reservation->setItemText(1, QCoreApplication::translate("MainWindow", "Normal", nullptr));
        combo_reservation->setItemText(2, QCoreApplication::translate("MainWindow", "VIP", nullptr));

        label_119->setText(QCoreApplication::translate("MainWindow", "Select Client", nullptr));
        label_120->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        envoyer_mail->setText(QCoreApplication::translate("MainWindow", "Envoyer par SMS", nullptr));
        label_111->setText(QCoreApplication::translate("MainWindow", "Taper votre numero", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(envoyersms), QCoreApplication::translate("MainWindow", "Evenements et Soldes", nullptr));
        Telecharger_historique->setText(QCoreApplication::translate("MainWindow", "Telecharger l'historique", nullptr));
        tabWidget_client->setTabText(tabWidget_client->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Historique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
