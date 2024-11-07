#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSqlQueryModel>
#include "employe.h"
#include "connection.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void onLoadButtonClicked();


    void on_modifier_employe_clicked();
    void clear();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *employeModel;

    void afficherEmployes();
};

#endif
