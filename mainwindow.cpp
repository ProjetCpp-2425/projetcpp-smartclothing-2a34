#include "mainwindow.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QString>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QHeaderView>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chartView(nullptr),
    model(new QSqlQueryModel(this)),  // Initialize model
    sortOrderAscending(true) // Default sort order


{
    ui->setupUi(this);

    model->setQuery("SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription FROM client");
    ui->tableView_2->setModel(model);
    // Enable clickable headers
    ui->tableView_2->horizontalHeader()->setSectionsClickable(true);
    // Connect comboBox signal to the sorting function
    connect(ui->trier, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_trier_activated);
    connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_tableView_2_headerClicked);

    // Connect the statistics button to its handler
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statsButton_clicked);


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

}

MainWindow::~MainWindow()
{
    delete ui;
    if (chartView) {
        delete chartView;
    }
}

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
        ui->tableView->setModel(c.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Failed to add client.");
    }
}

void MainWindow::on_modifier_clicked()
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
        ui->tableView->setModel(c.afficher());
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

void MainWindow::on_supprimer_clicked()
{
    QString cin_client = ui->CIN_input->text();
    client c;

    if (c.supprimer(cin_client)) {
        QMessageBox::information(this, "Success", "Client deleted successfully.");
        ui->tableView->setModel(c.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete client.");
    }
}

void MainWindow::on_afficher_clicked()
{
    client c;
    ui->tableView->setModel(c.afficher());
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

        // Set the model to the tableView (ensure tableView_2 is a QTableView)
        ui->tableView_2->setModel(model);  // Make sure this is a QTableView, not QTableWidget
    } else {
        // Print query failure message if it fails
        qDebug() << "Query failed: " << query.lastError().text();
    }
}


void MainWindow::on_statsButton_clicked()
{
    int nomCount = 0, prenomCount = 0, numeroCount = 0;

    // Query to get data from CLIENT table
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT");
    if (query.exec()) {
        while (query.next()) {
            QString clientName = query.value("nom_c").toString();
            QString clientPrenom = query.value("prenom_c").toString();
            QString clientNumber = query.value("numero_c").toString();

            if (!clientName.isEmpty()) nomCount++;
            if (!clientPrenom.isEmpty()) prenomCount++;
            if (!clientNumber.isEmpty()) numeroCount++;
        }
    }

    // Prepare strings for display
    QString nomCountStr = QString::number(nomCount);
    QString prenomCountStr = QString::number(prenomCount);
    QString numeroCountStr = QString::number(numeroCount);

    // Create the pie chart series
    auto *series = new QPieSeries();
    series->setHoleSize(0.35);
    series->append("Nom: " + nomCountStr, nomCount);
    series->append("Prénom: " + prenomCountStr, prenomCount);
    series->append("Numéro: " + numeroCountStr, numeroCount);

    // Create the chart
    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("<h2 style='color:darkblue'>Statistiques des Clients</h2>");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Create the chart view
    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a widget to hold the chart and details
    QWidget *statsWidget = new QWidget(this);
    statsWidget->setWindowTitle("Statistiques des Clients");
    QVBoxLayout *layout = new QVBoxLayout(statsWidget);

    // Add the chart view
    layout->addWidget(chartView);

    // Add a details section
    QLabel *details = new QLabel(statsWidget);
    details->setText(
        QString("<h3 style='color:darkgreen'>Détails des Statistiques</h3>"
                "<ul>"
                "<li><b>Nombre de Noms:</b> %1</li>"
                "<li><b>Nombre de Prénoms:</b> %2</li>"
                "<li><b>Nombre de Numéros:</b> %3</li>"
                "</ul>")
            .arg(nomCountStr)
            .arg(prenomCountStr)
            .arg(numeroCountStr));
    details->setWordWrap(true);
    layout->addWidget(details);

    // Add a back button
    QPushButton *backButton = new QPushButton("Retour", statsWidget);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, [this, statsWidget]() {
        statsWidget->deleteLater(); // Schedule the stats widget for deletion
        ui->centralwidget->show();  // Immediately show the main UI
    });

    // Set up the stats widget layout
    statsWidget->setLayout(layout);
    statsWidget->resize(800, 600);
    statsWidget->show();

    // Hide the main UI while displaying the stats
    ui->centralwidget->hide();
}
void MainWindow::on_Telecharger_button_clicked()
{
    // Query client data from the database
    QSqlQuery query;
    query.exec("SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription FROM CLIENT");

    // Prompt user for file location
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), "exported_client_data.pdf", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Page setup
    QPageSize pageSize(QPageSize::A2);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, QMarginsF(70,70,70,70)); // Larger margins for better layout
    printer.setPageLayout(pageLayout);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to open PDF for writing."));
        return;
    }

    QTextDocument pdfDoc;
    pdfDoc.setDocumentMargin(15); // Set margins for the document to avoid clipping

    QTextCursor cursor(&pdfDoc);
    QTextCharFormat titleFormat;
    titleFormat.setFontWeight(QFont::Bold);
    titleFormat.setFontPointSize(300); // Larger font size for title

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);
    headerFormat.setFontPointSize(300); // Larger font size for headers

    QTextCharFormat dataFormat;
    dataFormat.setFontPointSize(300); // Larger font size for data

    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(150);
    tableFormat.setCellSpacing(30);
    tableFormat.setHeaderRowCount(40);
    tableFormat.setBorder(10);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setBorderBrush(QBrush(QColor("#D3D3D3")));

    // Insert title for client data
    cursor.insertText("Client Data Report", titleFormat);
    cursor.insertBlock();
    cursor.insertBlock();

    // Insert table for database results
    QTextTable* table = cursor.insertTable(1, 6, tableFormat); // 6 columns for client data (CIN, Nom, Prénom, Numéro, Email, Date)

    // Header Row for table
    QStringList headerRow;
    headerRow << "CIN" << "First Name" << "Last Name" << "Phone Number" << "Email" << "Date of Inscription";

    // Insert header into table
    for (int i = 0; i < headerRow.size(); ++i) {
        QTextCursor cellCursor = table->cellAt(0, i).firstCursorPosition();
        cellCursor.insertText(headerRow[i], headerFormat);
    }

    // Insert data rows from database
    int row = 1;
    while (query.next()) {
        QString cin = query.value("CIN_client").toString();
        QString firstName = query.value("nom_c").toString();
        QString lastName = query.value("prenom_c").toString();
        QString phone = query.value("numero_c").toString();
        QString email = query.value("mail_c").toString();
        QDate dateInscription = query.value("date_inscription").toDate();

        table->insertRows(table->rows(), 1);

        table->cellAt(row, 0).firstCursorPosition().insertText(cin, dataFormat);
        table->cellAt(row, 1).firstCursorPosition().insertText(firstName, dataFormat);
        table->cellAt(row, 2).firstCursorPosition().insertText(lastName, dataFormat);
        table->cellAt(row, 3).firstCursorPosition().insertText(phone, dataFormat);
        table->cellAt(row, 4).firstCursorPosition().insertText(email, dataFormat);
        table->cellAt(row, 5).firstCursorPosition().insertText(dateInscription.toString("dd/MM/yyyy"), dataFormat);

        row++;
    }

    // Finalize and save the PDF
    pdfDoc.drawContents(&painter);
    painter.end();

    // Notify user of successful export
    QMessageBox::information(this, tr("Export Successful"), tr("Client data has been exported to PDF successfully."));
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
