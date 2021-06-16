#include "mycoin.h"
#include <QPixmap>
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;

    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug() << str;
        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号 并且翻转金币
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug() << "金币翻转图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //判断 如果翻完了 将min 重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            timer1->stop();
            isAnimation = false;
        }
    });

    //监听反面翻正面的信号 并且翻转金币
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug() << "银币翻转图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        //判断 如果翻完了 将min 重置为1
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
