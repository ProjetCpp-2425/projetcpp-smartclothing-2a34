#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSqlQueryModel>
#include "employe.h"
#include "connection.h"
#include "arduinors.h"
#include "client.h"
#include "arduinod.h"

#include "Article.h"
#include "articlenotifier.h"
#include "notification.h"

#include "connection.h"
#include <QTableView>
#include "transaction.h"
#include "vocale.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<Employe> getAllEmployees();

    void ajouter();
    void articles();
    void Statiques();
    void notification();
    void Fabriquer();

    void DiaCirculaire();
    void Graph1();
    void Graph2();



    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();

    QVector<QChartView*> m_charts;
    void on_ID_ARTICLE_clicked();
    void applyStyleSheet(); // Déclare


private slots:
    void onAjouterClicked();
    void onSupprimerClicked();
    void onModifyButtonClicked();
    void navigateToEmploye();
    void navigateToProduit();
    void navigateToClient();
    void navigateToTransaction();
    void on_buttonToAcceuil_clicked();
    void sortclicked();
    void on_ajoute_employe_clicked();
    void on_annuler_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void onLoadButtonClicked();
    void onSearchCriteriaChanged();
    void sortBySalary();
    void sortByHireDate();
    void sortByName();
    void generateExcelReport();
    void on_modifier_employe_clicked();
    void clear();

    void on_pushButton_25_clicked();
    QMap<QString, int> getEmployeeCountByPoste();
    void displayPosteStatistics();
    void updateDateInTextEdit();
    void on_sendButton_clicked();
    void loadconge();
    void displaydemandeconge();
    void sendSms(const QString &phoneNumber, const QString &message);  // Declare sendSms function
    void on_refuseButton_clicked();
    void on_acceptButton_clicked();
    void clearLeaveRequest(const QString &employeeId);
    void initializeStackedWidgetSignPages();
    void   initializePage1();
    void  initializePage2();
    void  initializePage3();
    void  initializePage4();


    bool validateEmailAndEnableNext();
    bool  validateTelephoneAndPassword();
    QString generateUniqueId();
    void saveNewEmployeeSign();
    void on_connecter_clicked();
    void on_deja1_clicked();
    void on_sendSmsButton_clicked();
    void on_navez_clicked();

    void mdpoublier();
    void on_verifyCodeButton_clicked();
    void on_updatePasswordButton_clicked();

    void on_sortie_clicked();

    void on_pushButton_clickedchef();

    void on_retour_5_clicked();



    void on_Page2_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_DiagrammCirculaire_clicked(bool checked);

    void on_pushButton_14_clicked(bool checked);

    void on_pushButton_GraphiqueBarres_clicked(bool checked);



    void changeTheme(int index); // Slot pour changer le thème en fonction du choix dans la ComboBox

    void changeAnimation(int index);

    void on_Ajouter_clicked();


    void on_SUPPRIMER_clicked();

    void on_miseJOUR_clicked();



    void on_MODIFIER_clicked();
    QString getSelectedCategorie();


    void on_comboBox_2_activated(int index);


    void on_rechercher_clicked();

    QMap<QString, int> getTypeCounts();
    void displayTypeStatistics() ;


    void on_pushButton_DiagrammCirculaire_clicked();




    void notifyAnniversary();
    void notifyLowStock();
    void notifyPromotion();
    void markNotificationAsSeen(int notificationIndex); // Marquer la notification comme vue
    void showNotifications();
    void checkNotificationsExpiry();
    void displaySizeStatistics();

    void on_pushButton_GraphiqueBarres_clicked();

    bool generatePdf();

    void on_PDF_clicked();
    void on_pushButton_chatbot_query_clicked();
    void handleChatbotReply(QNetworkReply* reply);

    void setupLineEditCompletion();
//void onArduinoDataReceived();
   // void saveFingerprint();    // Slot triggered when Arduino sends data

    void readFromArduino();



//duaa
    void on_ajouterTransaction_clicked();  // Slot pour ajouter une transaction
    void on_supprimer_clickedt();  // Slot pour supprimer une transaction
    void on_modifier_clicked();  // Slot pour modifier une transaction
    void on_pdf_clicked();

    void on_tri_clicked();  // Slot pour trier les transactions
    void on_rechercherTransaction_clicked();  // Slot pour rechercher des transactions
    void on_statistiqueButtonTransaction_clicked();
    void afficherHistoriqueTransaction();
    void on_pb_historiqueTransaction_clicked();
    //void on_statistique_clicked();  // Slot pour afficher les statistiques
    // void on_HistoriqueButton_Clicked();
    void on_stop_voc_clicked();
    void on_vocale_clicked();
    void on_stop_voc_2_clicked();

    void on_btnAjouter_clicked();

    void on_modifiercl_clicked();
    void on_supprimercl_clicked();
    void on_afficher_clicked();
    void on_searchButton_clicked();
    void on_statsButton_clicked();
    void on_Telecharger_button_clicked();
    void on_trier_activated(int index);
    void on_tableView_2_headerClicked(int section); // Handle header clicks for sorting

    void classifyClients();
    void updateClientPurchase(const QString &cin, int purchaseIncrement);
    void on_envoyer_mail_clicked();
    void affichageClient();

    void on_precedent2_clicked();

    void on_precedent3_clicked();

    void on_presedent4_clicked();
    void updateDisplay(int totalEntries, int totalExits, int currentOccupancy);

    void on_annuler_2_clicked();


    void on_buttonanuuler_clicked();


    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *employeModel;
    QString verificationCode;
    ARTICLE ART;
    Arduino *arduinoa;
    Arduinod A;

    int totalEntries = 0;
    int totalExits = 0;
    int currentOccupancy = 0;
    //QPushButton *historiqueButton;  // Bouton pour afficher l'historique

    void afficherEmployes();
    void generateExcelRepor();
    QStandardItemModel *notificationModel;
    // Déclaration de l'icône de la barre des tâches pour les notifications
    QSystemTrayIcon *trayIcon;
    QList<Notification> notificationHistory;  // Liste des notifications non vues
    QNetworkAccessManager *networkManager;


    ArduinoRS arduino; // To manage Arduino connection
    QByteArray dataFromArduino; // To receive data from Arduino
    //void handleFingerprintScan(); // Function to process fingerprint data
    void updateEmployeeStatus(Employe &employee); //

    client c;  // Global client object for operations
    QChartView *chartView; // Chart view for statistics
    QMainWindow *statsWindow = nullptr;
    QSqlQueryModel *model; // Query model for dynamic queries
    bool sortOrderAscending; // Track sorting order
    bool sendEmailUsingGmail(const QString &to, const QString &subject, const QString &body);

    Transaction transactionModel;  // Votre modèle de transaction
    //QPushButton *historiqueButton;  // Bouton pour afficher l'historique
    QTableView *tableView;  // Vue de la table pour afficher les transactions
    Vocale *vocaleHandler;
    void onTrierParDate();   // Slot pour trier par date récente
    void onTrierParMontant();
};

#endif
