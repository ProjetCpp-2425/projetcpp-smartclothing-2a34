#include "mainwindow.h"
#include "Article.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlError>
#include "ui_mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include<QDebug>
#include <QStandardItemModel>
#include<QSortFilterProxyModel>
#include <QtCharts/QValueAxis>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QFile>
#include <QPdfWriter>
#include <QPainter>
#include <QVBoxLayout>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QDate>
#include <QTimer>
#include<QProcess>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QSqlQuery>
#include <QMap>
#include <QStringList>
#include <QColor>
#include <QBrush>
#include <QVBoxLayout>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <numeric> // Pour std::accumulate
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QDesktopServices>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrlQuery>
#include <QByteArray>
#include <QHttpMultiPart>
#include <QCompleter>



MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent), ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this))

{
    ui->setupUi(this);

    setupLineEditCompletion();

    applyStyleSheet();

    // Configurer le mode de sélection multiple
    ui->listWidget_Tailles->setSelectionMode(QAbstractItemView::MultiSelection);

    // Ajouter des éléments à la liste pour tester
    ui->listWidget_Tailles->addItems(QStringList() << "XS" << "S" << "M" << "L" << "XL" << "XXL" << "XXXL");

    ui->tableView->setModel(ART.afficherArticle());
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    qApp->setPalette(palette());



    // Initialiser trayIcon (icône de la barre des tâches)
        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(QIcon(":/new/prefix1/try_icon.png"));  // Mettre à jour le chemin de l'icône
        trayIcon->setVisible(true);  // Rendre l'icône visible

        // Vérifier les promotions toutes les 10 minutes (600 000 ms)
        /*QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::checkNotificationsExpiry);
        timer->start(86400000);  // 10 minutes*/

        // Vérifier les promotions toutes les 10 minutes (600 000 ms)
       /* QTimer *timerSTOCK = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::notifyLowStock);
        timer->start(5000);  // 10 minutes*/

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::notifyLowStock);

        timer->start(86400000);  // 10 minutes
        // Connexion des boutons aux méthodes correspondantes
        connect(ui->pushButton_notifyAnniversary, &QPushButton::clicked, this, &MainWindow::notifyAnniversary);
        //connect(ui->pushButton_notifyLowStock, &QPushButton::clicked, this, &MainWindow::showNotifications);

        connect(ui->pushButton_notifyLowStock, &QPushButton::clicked, this, &MainWindow::notifyLowStock);
        connect(ui->pushButton_notifyPromotion, &QPushButton::clicked, this, &MainWindow::notifyPromotion);

        // notification systeme
        QMenu *trayIconMenu = new QMenu(this);
        QAction *quitAction = new QAction("Quitter", this);
        connect(quitAction, &QAction::triggered, this, &QApplication::quit);
        trayIconMenu->addAction(quitAction);
        trayIcon->setContextMenu(trayIconMenu);

        // Appel à la méthode pour afficher les anniversaires des articles
        notifyAnniversary();
        notifyLowStock();
        notifyPromotion();

       //chatbot
        connect(ui->pushButton_chatbot_query, &QPushButton::clicked, this, &MainWindow::on_pushButton_chatbot_query_clicked);
        connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);



   ui->tableView->setStyleSheet("QTableView::item { background-color: rgb(173, 216, 230); color: black; }");

      // Set `tableView` to use the proxy model

      // Connect the search button to the filter function
      connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
      connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(on_comboBox_2_activated(int)));
     // connect(ui->btnExportRupture, &QPushButton::clicked, this, &MainWindow::exporterRuptureStock);


      /*  connect(ui->lineEdit_NOM, &QLineEdit::textChanged, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->lineEdit_DESCRIPTION, &QLineEdit::textChanged, this, &MainWindow::on_pushButton_ALERTES_clicked);*/


        /*// Connecter le signal currentIndexChanged à un slot pour gérer la sélection
        // Connecter les checkboxes au slot on_pushButton_ALERTES_clicked()
        connect(ui->checkBox_Blanc, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Noir, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Bleu, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Gris, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Rouge, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Beige, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Vert, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Rose, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Marron, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Jaune, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Violet, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->checkBox_Orange, &QCheckBox::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->spinBox_Quantite, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->radioButton_Automne, &QRadioButton::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->radioButton_Hiver, &QRadioButton::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->radioButton_Printemps, &QRadioButton::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->radioButton_Ete, &QRadioButton::toggled, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::on_pushButton_ALERTES_clicked);
        connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::on_pushButton_ALERTES_clicked);*/


        notificationModel = new QStandardItemModel(this);

        connect(ui->rechercher, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);



   connect(ui->themeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &MainWindow::changeTheme);

    ui->stacked->addWidget(ui->ajouter);
    ui->stacked->addWidget(ui->articles);
    ui->stacked->addWidget(ui->Statiques);
    ui->stacked->addWidget(ui->notification);
    ui->stacked->addWidget(ui->Fabriquer);


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::ajouter);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::articles);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::Statiques);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::notification);

    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::ajouter);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::articles);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::Statiques);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::notification);

    connect(ui->FABRIQUER,&QPushButton::clicked, this, &MainWindow::Fabriquer);

    connect(ui->ID_ARTICLE, &QPushButton::clicked, this, &MainWindow::on_ID_ARTICLE_clicked);


    ui->stackedWidget->addWidget(ui->DiaCirculaire);
    ui->stackedWidget->addWidget(ui->Graph1);
    ui->stackedWidget->addWidget(ui->Graph2);

    connect(ui->pushButton_DiagrammCirculaire, &QPushButton::clicked, this, &MainWindow::DiaCirculaire);
    connect(ui->pushButton_GraphiqueBarres, &QPushButton::clicked, this, &MainWindow::Graph2);


    ui->comboBox->setStyleSheet("   border: 2px solid white;border-radius: 8px;padding: 1px 18px 1px 3px;background-color: black;color: white;height: 35px");
    ui->comboBox->setStyleSheet(" padding-left: 15px;font-weight: bold;  border: 0;selection-background-color: #298089;");
    ui->pushButton_DiagrammCirculaire->setStyleSheet("height:30px;border-radius:5px");
    ui->pushButton_GraphiqueBarres->setStyleSheet("height:30px;border-radius:5px");


    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::notifyLowStock);


    populateThemeBox();


}

void MainWindow::connectSignals() {
    // Implémentation de la fonction
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::Graph1()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::Graph2()
{
    ui->stackedWidget->setCurrentIndex(3);
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
    ui->pushButton->setStyleSheet("background-color:white; color: red; border: 2px solid white;");
    QFont font = ui->pushButton-> font();
    font.setBold(true);
    ui->pushButton_6->setFont(font);

    ui->pushButton_2->setStyleSheet("");
    QFont font2 = ui->pushButton_2-> font();
    font2.setBold(false);
    ui->pushButton_2->setFont(font2);

    ui->pushButton_3->setStyleSheet("");
    QFont font3 = ui->pushButton_3-> font();
    font3.setBold(false);
    ui->pushButton_3->setFont(font3);

    ui->pushButton_4->setStyleSheet("");
    QFont font4 = ui->pushButton_4-> font();
    font4.setBold(false);
    ui->pushButton_4->setFont(font4);
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


/*void MainWindow::on_lineEdit_editingFinished()
{

    QString inputText = ui->lineEdit->text();
    if(inputText.isEmpty())
    {
        QMessageBox::warning(this, "Attention", "Code est vide ");
    }
    else
    {
    QMessageBox::information(this, "Valider", "Code d'un article ajouter: " + inputText);
    }
}


void MainWindow::on_lineEdit_2_editingFinished()
{
    QString inputText = ui->lineEdit_2->text();
    QMessageBox::information(this, "Saisie", "Nom d'un article ajouter: " + inputText);
}*/


/*void MainWindow::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem*> selectedItems = ui->listWidget_Tailles->selectedItems();
        QString selectedText;

        for (QListWidgetItem* item : selectedItems) {
            selectedText += item->text() + "\n";
        }

        if (!selectedText.isEmpty()) {
            QMessageBox::information(this, "Sélection", "Éléments sélectionnés:\n" + selectedText);
        }
}

*/
/*void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if (checked) {
            QRadioButton *button = qobject_cast<QRadioButton *>(sender());
            if (button) {
                QString choix = button->text();
                qDebug() << "Choix sélectionné :" << choix;

                // Par exemple, mettre à jour un QLabel
                //ui->label->setText("Choix : " + choix);
            }
        }
}
*/

/*void MainWindow::on_radioButton_5_clicked(bool checked)
{
    if (checked) {
            QRadioButton *button = qobject_cast<QRadioButton *>(sender());
            if (button) {
                QString choix = button->text();
                qDebug() << "Choix sélectionné :" << choix;

                // Par exemple, mettre à jour un QLabel
                //ui->label->setText("Choix : " + choix);
            }
        }
}
*/


/*void MainWindow::on_radioButton_6_clicked(bool checked)
{
    if (checked) {
            QRadioButton *button = qobject_cast<QRadioButton *>(sender());
            if (button) {
                QString choix = button->text();
                qDebug() << "Choix sélectionné :" << choix;/
                // Par exemple, mettre à jour un QLabel
                //ui->label->setText("Choix : " + choix);
            }
        }
}*/

/*void MainWindow::on_radioButton_7_clicked(bool checked)
{
    if (checked) {
            QRadioButton *button = qobject_cast<QRadioButton *>(sender());
            if (button) {
                QString choix = button->text();
                qDebug() << "Choix sélectionné :" << choix;

                // Par exemple, mettre à jour un QLabel
                //ui->label->setText("Choix : " + choix);
            }
        }
}
*/

/*void MainWindow::on_lineEdit_3_editingFinished()
{
    QString Texte = ui->lineEdit_3->text();
    if(Texte.isEmpty())
    {
        QMessageBox::warning(this, "Attention", "IL faut ecrire une description ");
    }
    else
    {
    QMessageBox::information(this, "Valider", "Quelle belle description " + Texte);
    }

}*/

/*void MainWindow::on_pushButton_11_clicked()
{
    int row = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(row);

        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(ui->lineEdit->text()));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(ui->lineEdit_2->text()));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(ui->dateTimeEdit->text()));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(ui->comboBox->currentText()));

        QString radioButtonText;

        if (ui->radioButton_4->isChecked()) {
            radioButtonText = ui->radioButton_4->text();
        } else if (ui->radioButton_5->isChecked()) {
            radioButtonText = ui->radioButton_5->text();
        } else if (ui->radioButton_6->isChecked()) {
            radioButtonText = ui->radioButton_6->text();
        } else if (ui->radioButton_7->isChecked()) {
            radioButtonText = ui->radioButton_7->text();
        }

        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(radioButtonText));

        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(QString::number(ui->doubleSpinBox->value())));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(QString::number(ui->spinBox->value())));
        ui->tableWidget_2->setItem(row, 7, new QTableWidgetItem(ui->lineEdit_3->text()));
        ui->tableWidget_2->setItem(row, 8, new QTableWidgetItem(ui->listWidget->currentItem()->text()));
        ui->tableWidget_2->setItem(row, 9, new QTableWidgetItem(ui->lineEdit_4->text()));

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->dateTimeEdit->clear();
        ui->comboBox->clear();
        ui->radioButton_4->setChecked(false);
        ui->doubleSpinBox->setValue(0.0);
        ui->spinBox->setValue(0);
        ui->lineEdit_3->clear();
        ui->listWidget->clear();
        ui->lineEdit_4->clear();

}*/

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
    // add items to animation combobox
    ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);

    connect(ui->animatedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeAnimation);

}

void MainWindow::populateLegendBox()
{
    // add items to legend combobox
    ui->legendComboBox->addItem("No Legend ", 0);
    ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
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

    ui->stackedWidget->setStyleSheet(styleSheet);
}


void MainWindow::changeAnimation(int index)
{
    QChart::AnimationOptions animationOption = static_cast<QChart::AnimationOptions>(ui->animatedComboBox->itemData(index).toInt());

    for (QChartView *chartView : m_charts) {  // m_charts est un QVector<QChartView*>
        chartView->chart()->setAnimationOptions(animationOption);
    }
}

void MainWindow::on_Ajouter_clicked()
{

    //récupération des informations saisies dans les 3 champs
     QString ID_ARTICLE=ui->lineEdit_CODE->text();
     if (ID_ARTICLE.isEmpty()) {
         QMessageBox::warning(this, "Erreur", "L'ID de l'article ne peut pas être vide.");
         return;
     }
     if (ID_ARTICLE.length() < 5 || ID_ARTICLE.length() > 20) {
         QMessageBox::warning(this, "Erreur", "L'ID de l'article doit être compris entre 5 et 20 caractères.");
         return;
     }

     QString NOM_A=ui->lineEdit_NOM->text();

     QStringList valeursAutorisees = {"Chemise", "Pantalon", "Veste", "Robe", "Pull", "Jupe"};

     if (NOM_A.isEmpty()) {
         QMessageBox::warning(this, "Erreur", "Le nom de l'article ne peut pas être vide.");
         return;
     }

     if (!valeursAutorisees.contains(NOM_A)) {
         QMessageBox::warning(this, "Erreur", "Le nom de l'article doit être l'un des suivants : Chemise, Pantalon, Veste, Robe, Pull, Jupe.");
         return;
     }

     QRegularExpression regex("^[A-Za-zÀ-ÿéèêôïîàùç ]+$");  // Permet les lettres, accents et espaces
     QRegularExpressionMatch match = regex.match(NOM_A);
     if (!match.hasMatch()) {
         QMessageBox::warning(this, "Erreur", "Le nom de l'article doit contenir uniquement des lettres et des espaces.");
         return;  // Arrêter l'exécution si le format est invalide
     }

     QDate DATE_AJOUT = ui->dateTimeEdit->date();
     if (DATE_AJOUT < QDate::currentDate()) {
         QMessageBox::warning(this, "Erreur", "La date ne peut pas être dans le passé.");
         return;
     }

     QString TYPE = ui->comboBox->currentText();
     if (TYPE.isEmpty()) {
         QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un type.");
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
      }
     else
     {
         QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une catégorie.");
            return;
     }
     double PRIX=ui->doubleSpinBox->value();
     if (PRIX <= 0) {
         QMessageBox::warning(this, "Erreur", "Le prix doit être supérieur à zéro.");
         return;
     }


     int QUANTITE_STOCK=ui->spinBox_Quantite->value();

     if (QUANTITE_STOCK < 0) {
         QMessageBox::warning(this, "Erreur", "La quantité en stock ne peut pas être négative.");
         return;
     }

     QString DESCRIPTIONN=ui->lineEdit_DESCRIPTION->text();
     if (DESCRIPTIONN.isEmpty()) {
         QMessageBox::warning(this, "Erreur", "La description de l'article ne peut pas être vide.");
         return;
     }

     QString TAILLE;

        // Récupérer les éléments sélectionnés
        QList<QListWidgetItem*> selectedItems = ui->listWidget_Tailles->selectedItems();

        if (!selectedItems.isEmpty()) {
            QStringList taillesList;
            for (QListWidgetItem* item : selectedItems) {
                taillesList.append(item->text());
            }
            TAILLE = taillesList.join(", ");
            //QMessageBox::information(this, "Tailles sélectionnées", "Tailles : " + TAILLE);
        } else {
            QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner au moins une taille.");
        }



     if (!selectedItems.isEmpty()) {
         QStringList taillesList;
         for (QListWidgetItem* item : selectedItems) {
             taillesList.append(item->text());
         }
         // Combiner les tailles sélectionnées en une seule chaîne séparée par des virgules
         TAILLE = taillesList.join(", ");
     } else {
         QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner au moins une taille.");
         return;
     }


     QString COULEUR; // Accumulation de couleurs avec cadres colorés

     // Ajouter chaque couleur sélectionnée avec un cadre coloré
     if (ui->checkBox_Blanc->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #FFFFFF; border: 1px solid #000; margin-right: 5px;'></span>Blanc, ";
     if (ui->checkBox_Noir->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #000000; border: 1px solid #000; margin-right: 5px;'></span>Noir, ";
     if (ui->checkBox_Bleu->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #0000FF; border: 1px solid #000; margin-right: 5px;'></span>Bleu, ";
     if (ui->checkBox_Gris->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #808080; border: 1px solid #000; margin-right: 5px;'></span>Gris, ";
     if (ui->checkBox_Rouge->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #FF0000; border: 1px solid #000; margin-right: 5px;'></span>Rouge, ";
     if (ui->checkBox_Beige->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #F5F5DC; border: 1px solid #000; margin-right: 5px;'></span>Beige, ";
     if (ui->checkBox_Vert->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #008000; border: 1px solid #000; margin-right: 5px;'></span>Vert, ";
     if (ui->checkBox_Rose->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #FFC0CB; border: 1px solid #000; margin-right: 5px;'></span>Rose, ";
     if (ui->checkBox_Marron->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #A52A2A; border: 1px solid #000; margin-right: 5px;'></span>Marron, ";
     if (ui->checkBox_Jaune->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #FFFF00; border: 1px solid #000; margin-right: 5px;'></span>Jaune, ";
     if (ui->checkBox_Violet->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #800080; border: 1px solid #000; margin-right: 5px;'></span>Violet, ";
     if (ui->checkBox_Orange->isChecked()) COULEUR += "<span style='display: inline-block; width: 16px; height: 16px; background-color: #FFA500; border: 1px solid #000; margin-right: 5px;'></span>Orange, ";

     // Vérifier si des couleurs ont été sélectionnées
     if (COULEUR.isEmpty()) {
         QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner au moins une couleur.");
         return;
     }

     // Supprimer la dernière virgule et espace
     COULEUR.chop(2);


     //    QString COULEUR = couleursSelectionnees;  // Les couleurs sélectionnées en une seule chaîne




     ARTICLE A(ID_ARTICLE,NOM_A,DESCRIPTIONN,PRIX,CATEGORIE,QUANTITE_STOCK,TAILLE,COULEUR,TYPE,DATE_AJOUT);//en utilisant les information dans l'interface

     bool test=A.ajouterArticle();//ajouter les information dans le tableau article

     if (test) {
         QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué \n""Click cancel to exit."), QMessageBox::Cancel);

         // Ajouter un message de notification dans la listView
         QString notificationMessage = "Nouvel article ajouté : " + NOM_A;
         QStandardItem *item = new QStandardItem(notificationMessage);
         notificationModel->appendRow(item);
     } else {
         QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Ajout N'est PAS effectué \n""Click cancel to exit."), QMessageBox::Cancel);
     }

}


void MainWindow::on_SUPPRIMER_clicked()
{
    QString ID_ARTICLE=ui->supprimer->text();
    bool test=ART.supprimerArticles(ID_ARTICLE);

    if(test)
    {

        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("SUPPRIMER effectué \n""Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Erreur"),QObject::tr("SUPPRIMER N'est PAS effectué \n""Click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_miseJOUR_clicked()
{
    ui->tableView->setModel(ART.afficherArticle());

}


void MainWindow::on_ID_ARTICLE_clicked()
{
    QString id = ui->lineEdit_IdArticle->text();
    if (ART.chercher(id)) {
        if (!ART.getCodeArticle().isEmpty()) {
            ui->lineEdit_CODE->setText(ART.getCodeArticle());
            ui->lineEdit_NOM->setText(ART.getNomArticle());
            ui->dateTimeEdit->setDate(ART.getDateAjout());
            ui->lineEdit_DESCRIPTION->setText(ART.getDescription());

            QString saison = ART.getCategorie();
            ui->radioButton_Automne->setChecked(saison == "Automne");
            ui->radioButton_Hiver->setChecked(saison == "Hiver");
            ui->radioButton_Ete->setChecked(saison == "Ete");
            ui->radioButton_Printemps->setChecked(saison == "Printemps");

            // Fill other fields
            ui->doubleSpinBox->setValue(ART.getPrix());
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
        ART.setPrix(ui->doubleSpinBox->value());
        ART.setDateAjout(ui->dateTimeEdit->date());

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

    QString order = (ui->comboBox_2->currentIndex() == 0) ? "DESC" : "ASC";

    QString queryStr = QString("SELECT * FROM ARTICLE ORDER BY %1 %2").arg(orderBy, order);
    model->setQuery(queryStr);
    ui->tableView->setModel(model);

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

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents(); // Ajuster la largeur des colonnes

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

    QLayout *existingLayout = ui->chartPlaceholder->layout();
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
    ui->chartPlaceholder->setLayout(layout);

    qDebug() << "Graphique ajouté avec succès.";
}
void MainWindow::on_pushButton_DiagrammCirculaire_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->DiaCirculaire);
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

    qDebug() << "Graphique à barres des tailles généré avec succès.";
}

void MainWindow::on_pushButton_GraphiqueBarres_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->Graph2);
    displaySizeStatistics();
}


void MainWindow::notifyAnniversary() {

    qDebug() << "Vérification des anniversaires des articles...";


    QDate currentDate = QDate::currentDate();

     QAbstractItemModel *model = ui->tableView->model();

     if (!model) {
           qDebug() << "Erreur : modèle du tableView invalide.";
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

    QAbstractItemModel *model = ui->tableView->model();
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

    if (query.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a query.");
        return;
    }

    QJsonObject json;
    json["model"] = "mistral";

    QJsonObject message;
    message["role"] = "user";
    message["content"] = query;

    QJsonArray messages;
    messages.append(message);

    json["messages"] = messages;

    QJsonDocument doc(json);

    QUrl url("http://localhost:11434/v1/chat/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Prevent multiple connections
    disconnect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleChatbotReply);

    networkManager->post(request, doc.toJson());
}


void MainWindow::handleChatbotReply(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg = reply->errorString();
        QMessageBox::critical(this, "Error", "Failed to communicate with Ollama server: " + errorMsg);
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (jsonResponse.isObject()) {
        QJsonObject responseObject = jsonResponse.object();

        if (responseObject.contains("choices") && responseObject["choices"].isArray()) {
            QJsonArray choicesArray = responseObject["choices"].toArray();
            if (!choicesArray.isEmpty() && choicesArray[0].isObject()) {
                QJsonObject firstChoice = choicesArray[0].toObject();
                if (firstChoice.contains("message") && firstChoice["message"].isObject()) {
                    QJsonObject messageObject = firstChoice["message"].toObject();
                    if (messageObject.contains("content") && messageObject["content"].isString()) {
                        QString chatbotResponse = messageObject["content"].toString();
                        ui->textEdit_chatbot_response->setText(chatbotResponse);
                        reply->deleteLater();
                        return;
                    }
                }
            }
        }
    }

    ui->textEdit_chatbot_response->setText("No valid response from chatbot.");
    reply->deleteLater();
}

void MainWindow::applyStyleSheet()
{
    QString styleSheet = R"(
        /* Style pour QLineEdit */
        QLineEdit#lineEdit_chatbot_query {
            border: 2px solid #0078D7;
            border-radius: 8px;
            padding: 6px 10px;
            font-size: 14px;
            font-family: "Arial", sans-serif;
            color: #333;
            background-color: #f9f9f9;
        }

        QLineEdit#lineEdit_chatbot_query:focus {
            border: 2px solid #0056A1;
            background-color: #ffffff;
        }

        /* Style pour QPushButton avec flèche grasse */
        QPushButton#pushButton_chatbot_query {
            position: absolute;
            right: 5px; /* Alignement à droite dans le QLineEdit */
            top: 5px; /* Centrage vertical */
            width: 100px; /* Taille du bouton */
            height: 200px;
            background-color: #0078D7; /* Couleur par défaut */
            color: black; /* Couleur de la flèche */
            border: none;
            border-radius: 16px; /* Bouton rond */
            font-size:50px; /* Taille de la flèche */
            font-weight: bold; /* Flèche en gras */
            text-align: center;
            line-height: 32px; /* Centrage vertical du texte */
            font-family: "Arial", sans-serif; /* Police moderne */
        }

        QPushButton#pushButton_chatbot_query:hover {
            background-color: #0056A1; /* Couleur au survol */
        }

        QPushButton#pushButton_chatbot_query:pressed {
            background-color: #003C71; /* Couleur lors du clic */
        }

        /* Style pour QTextEdit */
        QTextEdit#textEdit_chatbot_response {
            border: 2px solid #cccccc;
            border-radius: 8px;
            padding: 10px;
            font-size: 14px;
            font-family: "Verdana", sans-serif;
            color: #222;
            background-color: #f5f5f5;
        }

        QTextEdit#textEdit_chatbot_response:disabled {
            color: #888;
            background-color: #efefef;
        }

        QWidget#chartPlaceholder {
            border: 2px solid #0078D7;
            border-radius: 8px;
            background-color: #f9f9f9;
            min-height: 200px; /* Hauteur minimale */
        }

        /* Conteneur d'informations de statistiques */
        QLabel#statsLabel {
            font-size: 16px;
            font-family: "Arial", sans-serif;
            color: #444;
            background-color: #f5f5f5;
            border: 1px solid #cccccc;
            border-radius: 8px;
            padding: 10px;
            margin: 10px 0;
            box-shadow: 0px 2px 5px rgba(0, 0, 0, 0.1); /* Ombre légère */
        }

        /* Texte animé */
        QLabel#statsLabel:hover {
            color: #0078D7; /* Texte change de couleur au survol */
            transition: color 0.3s ease;
        }

    )";

    this->setStyleSheet(styleSheet); // Appliquer à la fenêtre principale.

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
    // Liste des valeurs autorisées
    QStringList valeursAutorisees = {"Chemise", "Pantalon", "Veste", "Robe", "Pull", "Jupe"};

    // Configurer le QCompleter
    QCompleter *completer = new QCompleter(valeursAutorisees, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // Auto-complétion insensible à la casse

    // Associer le completer au lineEdit_NOM
    ui->lineEdit_NOM->setCompleter(completer);
}
