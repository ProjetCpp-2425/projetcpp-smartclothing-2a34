#include "arduinors.h"
#include <QDebug>

ArduinoRS::ArduinoRS() : serial(new QSerialPort), isAvailable(false) {}

ArduinoRS::~ArduinoRS() {
    if (serial && serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

int ArduinoRS::connectToArduino() {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

        if (info.vendorIdentifier() == 0x2341 && info.productIdentifier() == 0x0043) {  // Vendor ID and Product ID for Arduino Uno
            portName = info.portName();
            serial->setPortName(portName);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite)) {
                isAvailable = true;
                qDebug() << "Connected to Arduino on port:" << portName;
                return 1;  // Successful connection
            } else {
                qDebug() << "Failed to open port:" << serial->errorString();
                return 0;  // Failed to open port
            }
        }
    }
    qDebug() << "No matching Arduino found.";
    return 0;  // No matching Arduino found
}

QByteArray ArduinoRS::readFromArduino() {
    if (serial->canReadLine()) {
        return serial->readLine();  // Read a line of data
    }
    return QByteArray();  // Return empty if nothing to read
}

void ArduinoRS::writeToArduino(const QByteArray &data) {
    if (serial->isWritable()) {
        serial->write(data);  // Send data to Arduino
        qDebug() << "Data written to Arduino:" << data;
    } else {
        qDebug() << "Cannot write to Arduino: port not writable";
    }
}

QSerialPort* ArduinoRS::getSerial() const {
    return serial;
}
