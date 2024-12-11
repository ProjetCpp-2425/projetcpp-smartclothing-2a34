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

    }
    else{

       //
    }
    return a.exec();
}
