#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "PlayScene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

public:
    void paintEvent(QPaintEvent *event);

public:
    PlayScene *play = NULL;
signals:
    void chooseSceneBack();

public slots:
};



#endif // CHOOSELEVELSCENE_H
