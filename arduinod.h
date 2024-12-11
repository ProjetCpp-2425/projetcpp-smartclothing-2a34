#ifndef ARDUINOD_H
#define ARDUINOD_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>


class Arduinod
{
public:
    Arduinod();
    int connect_arduinod();
    int close_arduinod();
    int write_to_arduinod( QByteArray );
    QByteArray read_from_arduinod();
    QSerialPort* getserial();
    QString getarduinod_port_name();
private:
    QSerialPort * serial;

    static const quint16 arduinod_uno_vendor_id=9025;
    static const quint16 arduinod_uno_producy_id=67;
    QString arduinod_port_name;
    bool arduinod_is_available;
    QByteArray data;
};


#endif // ARDUINOD_H
