#include "MyPushButton.h"
#include <QPropertyAnimation>
#include <QDebug>


//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pixmap;
    pixmap.load(normalImg);

    //设置图片固定大小
    this->setFixedSize(pixmap.width(), pixmap.height());
    //设置不规则图片样例
    this->setStyleSheet("QPushButton{border:0px};");
    //设置图标
    this->setIcon(pixmap);
    //设置图标尺寸
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
}

void MyPushButton::zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    QPixmap pixmap;
    if(this->pressImgPath != "")    //如果按到需要切换图片的按钮
    {
        pixmap.load(this->pressImgPath);
        //设置图片固定大小
        this->setFixedSize(pixmap.width(), pixmap.height());
        //设置不规则图片样例
        this->setStyleSheet("QPushButton{border:0px};");
        //设置图标
        this->setIcon(pixmap);
        //设置图标尺寸
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }

    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPixmap pixmap;
    if(this->pressImgPath != "")    //如果按到需要切换图片的按钮
    {
        pixmap.load(this->normalImgPath);
        //设置图片固定大小
        this->setFixedSize(pixmap.width(), pixmap.height());
        //设置不规则图片样例
        this->setStyleSheet("QPushButton{border:0px};");
        //设置图标
        this->setIcon(pixmap);
        //设置图标尺寸
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }

    return QPushButton::mouseReleaseEvent(e);
}
