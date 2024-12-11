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

    void dataUpdated(int totalEntries, int totalExits, int currentOccupancy);
    void readSerialData();

    QSerialPort *getSerial() const;

private:
    QSerialPort *serial;
    QString portName;
    bool isAvailable;
    int totalEntries;
    int totalExits;
    int currentOccupancy;
};

#endif // ARDUINORS_H
