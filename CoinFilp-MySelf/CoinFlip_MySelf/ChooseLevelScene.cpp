#include "ChooseLevelScene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "MyPushButton.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320, 588);
    this->setWindowTitle("关卡选择界面");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建开始菜单栏
    QMenuBar *myBar = menuBar();
    this->setMenuBar(myBar);     //添加
    QMenu *startMenu = myBar->addMenu("开始");
    QAction *actQuit = startMenu->addAction("退出");
    connect(actQuit, &QAction::triggered, [=](){
        this->close();
    });

    QSound *backSound = new QSound(":/res/BackButtonSound.wav");
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav");
    //创建返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &MyPushButton::clicked, [=](){
        //播放音效
        backSound->play();
        //使用emit将返回信号发出去
        QTimer::singleShot(100, this, [=](){
            emit this->chooseSceneBack();
        });
    });


    //创建20关卡入口
    for(int i=0; i<20; i++)
    {
        MyPushButton *btn =  new MyPushButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(25+i%4*70, 130+i/4*70);

        connect(btn, &MyPushButton::clicked, [=](){
            chooseSound->play();
            this->hide();
            //进入对应的关卡游戏界面
            play = new PlayScene(i+1);
            //必须放在show前面
            play->setGeometry(this->geometry());
            play->show();
            connect(play, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(play->geometry());
                delete play;
                play = NULL;
                this->show();
            });
        });

        //在关卡上创建数字
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(btn->width(), btn->height());
        label->move(25+i%4*70, 130+i/4*70);
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap  pixmap;

    //绘制背景
    pixmap.load(":res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    //绘制标题
    pixmap.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pixmap.width())*0.5, 30, pixmap.width(), pixmap.height(), pixmap);
}
