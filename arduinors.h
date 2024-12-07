#ifndef ARDUINORS_H
#define ARDUINORS_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

class ArduinoRS {
public:
    ArduinoRS();
    ~ArduinoRS();
    int connectToArduino();
    QByteArray readFromArduino();
    void writeToArduino(const QByteArray &data);
    QSerialPort *getSerial() const;
    int write_to_arduino( QByteArray d);

private:
    QSerialPort *serial;
    QString portName;
    bool isAvailable;
};

#endif // ARDUINORS_H
