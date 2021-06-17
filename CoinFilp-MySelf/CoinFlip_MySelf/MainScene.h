#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "MyPushButton.h"
#include "ChooseLevelScene.h"

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
public:
    MyPushButton *startBtn = NULL;
    ChooseLevelScene *chooseScene = NULL;

public:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
