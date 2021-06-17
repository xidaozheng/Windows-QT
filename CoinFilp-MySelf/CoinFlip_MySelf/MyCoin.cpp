#include "MyCoin.h"
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pixmap;
    pixmap.load(btnImg);

    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号 并且翻转金币
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if(this->min > this->max)
        {
            this->min = 1;
            timer1->stop();
            isAnimation = false;
        }
    });

    //监听反面翻正面的信号 并且翻转金币
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%8").arg(this->max--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if(this->max < this->min)
        {
            this->max = 8;
            timer2->stop();
            isAnimation = false;
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
        return;
    else
        QPushButton::mousePressEvent(e);
}

//改变标志的方法
void  MyCoin::changeFlag()
{
    if(this->flag)
    {
        //开始正面翻反面的定时器
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
