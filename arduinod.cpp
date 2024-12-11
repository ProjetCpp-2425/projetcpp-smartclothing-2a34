#include "arduinod.h"

Arduinod::Arduinod()
{
    data="";
    arduinod_port_name="";
    arduinod_is_available=false;
    serial=new QSerialPort;
}

QString Arduinod::getarduinod_port_name()
{
    return arduinod_port_name;
}

QSerialPort *Arduinod::getserial()
{
    return serial;
}
int Arduinod::connect_arduinod()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduinod_uno_vendor_id && serial_port_info.productIdentifier()
                                                                                     == arduinod_uno_producy_id) {
                arduinod_is_available = true;
                arduinod_port_name=serial_port_info.portName();
            } } }
    qDebug() << "arduinod_port_name is :" << arduinod_port_name;
    if(arduinod_is_available){
        serial->setPortName(arduinod_port_name);
        if(serial->open(QSerialPort::ReadWrite)){
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}

int Arduinod::close_arduinod()
{

    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;

}


QByteArray Arduinod::read_from_arduinod()
{
    if(serial->isReadable()){
        data=serial->readAll();

        return data;
    }
}


int Arduinod::write_to_arduinod( QByteArray d)
{

    if(serial->isWritable()){
        serial->write(d);
    }else{
        qDebug() << "Couldn't write to serial!";
    }

}
