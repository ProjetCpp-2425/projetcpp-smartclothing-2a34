#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QButtonGroup>
#include <QPalette>
#include<QDebug>
#include "Article.h"
#include <qstandarditemmodel.h>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QDate>
#include <QTimer>
#include "notification.h"
#include <Qt3DExtras/Qt3DWindow>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


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
    void applyStyleSheet(); // Déclare une méthode pour appliquer les styles.


private slots:

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


    void connectSignals();

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



private:
    Ui::MainWindow *ui;
    ARTICLE ART;
    QStandardItemModel *notificationModel;
    // Déclaration de l'icône de la barre des tâches pour les notifications
    QSystemTrayIcon *trayIcon;
    QList<Notification> notificationHistory;  // Liste des notifications non vues
    QNetworkAccessManager *networkManager;


};



#endif // MAINWINDOW_H
