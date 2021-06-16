#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include "mypushbutton.h"
#include "chooselevelscene.h"


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //重新定义大小
    setFixedSize(320, 588);
    //设置主窗口图标
    setWindowIcon(QIcon(":/res/Coin0001"));
    //设置主窗口标题
    setWindowTitle("翻金币界面");
    //设置退出按钮
    connect(ui->actionquit, &QAction::triggered, this, &MainScene::close);

    MyPushButton *StartBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    StartBtn->setParent(this);
    StartBtn->move(this->width()*0.5-StartBtn->width()*0.5, this->height()*0.7);

    ChooseLevelScene *chooseScene = new ChooseLevelScene;
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
        chooseScene->hide();
        this->show();
    });

    connect(StartBtn, &MyPushButton::clicked, [=](){
        qDebug() << "开始按钮被按下";
        StartBtn->zoom1();
        StartBtn->zoom2();

        //延时进入到选择关卡
        QTimer::singleShot(100, this, [=](){
            //自身隐藏
            this->hide();
            //进入到选择关卡场景中
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap  pix;

    //设置背景
    bool ret = pix.load(":/res/PlayLevelSceneBg.png");
    if(!ret)
    {
       qDebug() << "背景图片加载失败";
       return;
    }
    painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);

    //加载标题
    ret = pix.load(":/res/Title.png");
    if(!ret)
    {
        qDebug() << "标题图片加载失败";
        return;
    }
    //缩放图片
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

MainScene::~MainScene()
{
    delete ui;
}
