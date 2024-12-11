#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)), totalEntries(0), totalExits(0), currentOccupancy(0) {}

void Arduino::setupSerialConnection(const QString &portName) {
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open port:" << serial->errorString();
        return;
    }

    connect(serial, &QSerialPort::readyRead, this, &Arduino::readSerialData);
}

void Arduino::readSerialData() {
    while (serial->canReadLine()) {
        QByteArray rawData = serial->readLine().trimmed();

        if (rawData.isEmpty()) {
            continue;
        }

        QString data = QString::fromUtf8(rawData);
        qDebug() << "Data received from Arduino:" << data;

        // Parse the received data
        QRegularExpression regex("Status: Total entries: (\\d+), Total exits: (\\d+), Current occupancy: (\\d+)");
        QRegularExpressionMatch match = regex.match(data);

        if (match.hasMatch()) {
            totalEntries = match.captured(1).toInt();
            totalExits = match.captured(2).toInt();
            currentOccupancy = match.captured(3).toInt();

            emit dataUpdated(totalEntries, totalExits, currentOccupancy);
        } else if (data.startsWith("ERROR:")) {
            qDebug() << "Error message received:" << data;
        }
    }
}
