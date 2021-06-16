#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>



class playscene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playscene(QWidget *parent = nullptr);
    playscene(int levelNum);

    int levelIndex;     //内部成员属性 记录所选的关卡

public:
    void paintEvent(QPaintEvent *event);
signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
