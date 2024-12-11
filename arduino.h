#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QRegularExpression>

class Arduino : public QObject {
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);

    void setupSerialConnection(const QString &portName);

signals:
    void dataUpdated(int totalEntries, int totalExits, int currentOccupancy);

private slots:
    void readSerialData();

private:
    QSerialPort *serial;
    int totalEntries;
    int totalExits;
    int currentOccupancy;
};

#endif // ARDUINO_H
