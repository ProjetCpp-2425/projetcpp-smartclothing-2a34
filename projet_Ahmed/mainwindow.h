#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QSqlQuery>
#include <QSqlError>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QPainter>
#include <QSqlQueryModel>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_afficher_clicked();
    void on_searchButton_clicked();
    void on_statsButton_clicked();
    void on_Telecharger_button_clicked();
    void on_trier_activated(int index);
    void on_tableView_2_headerClicked(int section); // Handle header clicks for sorting


private:
    Ui::MainWindow *ui;
    client c;  // Global client object for operations
    QChartView *chartView; // Chart view for statistics
    QMainWindow *statsWindow = nullptr;
    QSqlQueryModel *model; // Query model for dynamic queries
    bool sortOrderAscending; // Track sorting order
};


#endif // MAINWINDOW_H
