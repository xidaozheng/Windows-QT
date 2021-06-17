#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();
public:
    void mousePressEvent(QMouseEvent *e);       //用于返回按钮的特效
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
