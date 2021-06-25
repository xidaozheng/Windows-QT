#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>

namespace Ui {
class SerialPort;
}

class SerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = 0);
    ~SerialPort();

private:
    Ui::SerialPort *ui;
};

#endif // SERIALPORT_H
