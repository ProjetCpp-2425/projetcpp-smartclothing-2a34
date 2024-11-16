#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSqlQueryModel>
#include "employe.h"
#include "connection.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<Employe> getAllEmployees();


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

    void on_pushButton_clicked();

    void on_retour_5_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *employeModel;
    QString verificationCode;

    void afficherEmployes();
    void generateExcelRepor();
};

#endif
