#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>



#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test){
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection succefull ._\n" "click cancel to exist ."),QMessageBox::Cancel);
    }
    else{

        QMessageBox::critical(nullptr, QObject::tr("databse is not open"),
                              QObject::tr("connection failed.\n" "click cancel to exist."),QMessageBox::Cancel);
    }
    return a.exec();
}
