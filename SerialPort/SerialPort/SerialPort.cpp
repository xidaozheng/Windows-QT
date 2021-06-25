#include "SerialPort.h"
#include "ui_SerialPort.h"

SerialPort::SerialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
}

SerialPort::~SerialPort()
{
    delete ui;
}
