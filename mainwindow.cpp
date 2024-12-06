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
#include <QPainter>
#include <QPdfWriter>
#include <QNetworkAccessManager>  // For sending emails via network
#include <QNetworkRequest>        // For network requests
#include <QNetworkReply>          // For handling network responses
#include <QJsonDocument>          // For working with JSON (if needed)
#include <QUrl>                   // For URLs
#include <QTextStream>            // If you want to handle email bodies as text streams
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QTextStream>
#include <QtNetwork/QSslSocket>
#include <QtCore/QCoreApplication>
#include <QByteArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chartView(nullptr),
    model(new QSqlQueryModel(this)),  // Initialize model
    sortOrderAscending(true) // Default sort order


{
    ui->setupUi(this);

    model->setQuery("SELECT CIN_client, nom_c, prenom_c, numero_c, mail_c, date_inscription, type_client FROM CLIENT");
    ui->tableView_2->setModel(model);
    // Enable clickable headers
    ui->tableView_2->horizontalHeader()->setSectionsClickable(true);
    // Connect comboBox signal to the sorting function
    connect(ui->trier, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::on_trier_activated);
    connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::on_tableView_2_headerClicked);

    // Connect the statistics button to its handler
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statsButton_clicked);
    connect(ui->btnClassify, &QPushButton::clicked, this, &MainWindow::classifyClients);
    connect(ui->envoyer_mail, &QPushButton::clicked, this, &MainWindow::on_envoyer_mail_clicked);


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
    int normalCount = 0, vipCount = 0;

    // Query to get data from CLIENT table
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT");
    if (query.exec()) {
        while (query.next()) {
            int purchasesCount = query.value("purchases_count").toInt();
            QString clientType = query.value("type_client").toString();

            // If client has 10 or more purchases, change their type to VIP
            if (purchasesCount >= 10 && clientType == "Normal") {
                // Update client type to VIP in the database
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE CLIENT SET type_client = 'VIP' WHERE id = :id");
                updateQuery.bindValue(":id", query.value("id"));
                updateQuery.exec();

                clientType = "VIP";  // Update local variable to reflect change
            }

            // Count Normal and VIP clients
            if (clientType == "Normal") normalCount++;
            else if (clientType == "VIP") vipCount++;
        }
    }

    // Calculate total clients
    int totalCount = normalCount + vipCount;

    // Create the pie chart series
    auto *series = new QPieSeries();
    series->setHoleSize(0.35);

    // Add slices with percentage labels
    QPieSlice *normalSlice = series->append("Normal: " + QString::number(normalCount), normalCount);
    QPieSlice *vipSlice = series->append("VIP: " + QString::number(vipCount), vipCount);

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
                "<li><b>Normal Clients:</b> %4</li>"
                "<li><b>VIP Clients:</b> %5</li>"
                "</ul>")
            .arg(normalCount)
            .arg(vipCount));
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

    // Create a PDF writer object
    QPdfWriter writer("Client_Report_Current_Month.pdf");
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

    // End painting
    painter.end();

    // Notify user
    QMessageBox::information(this, "PDF Generated", "The report has been successfully generated as 'Client_Report_Current_Month.pdf'.");
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
}



