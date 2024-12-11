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
        qDebug() << "Found port:" << info.portName()
        << "Vendor ID:" << info.vendorIdentifier()
        << "Product ID:" << info.productIdentifier();

        // Update Vendor ID and Product ID based on your Arduino
        if (info.vendorIdentifier() == 0x6790 && info.productIdentifier() == 0x29987) {
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
                return 1;
            } else {
                qDebug() << "Failed to open port:" << serial->errorString();
                return 0;
            }
        }
    }

    // Manual fallback for known port
    portName = "COM6";  // Replace with your COM port if necessary
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    if (serial->open(QIODevice::ReadWrite)) {
        isAvailable = true;
        qDebug() << "Connected to Arduino on port:" << portName;
        return 1;
    }

    qDebug() << "No matching Arduino found.";
    return 0;  // No Arduino found
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
