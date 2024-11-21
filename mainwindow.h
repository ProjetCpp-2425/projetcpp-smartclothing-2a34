#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QTableView>
#include "transaction.h"
#include "vocale.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT  // Macro nécessaire pour activer les signaux et slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Transaction transactionModel;  // Votre modèle de transaction
    //QPushButton *historiqueButton;  // Bouton pour afficher l'historique
    QTableView *tableView;  // Vue de la table pour afficher les transactions
    Vocale *vocaleHandler;

private slots:
    void on_ajouter_clicked();  // Slot pour ajouter une transaction
    void on_supprimer_clicked();  // Slot pour supprimer une transaction
    void on_modifier_clicked();  // Slot pour modifier une transaction
    void on_pdf_clicked();  // Slot pour exporter en PDF
    void on_tri_clicked();  // Slot pour trier les transactions
    void on_rechercher_clicked();  // Slot pour rechercher des transactions
    void on_statistiqueButtonTransaction_clicked();
    void afficherHistoriqueTransaction();
    void on_pb_historiqueTransaction_clicked();
    //void on_statistique_clicked();  // Slot pour afficher les statistiques
   // void on_HistoriqueButton_Clicked();
    void on_stop_voc_clicked();
    void on_vocale_clicked();
};
#endif // MAINWINDOW_H
