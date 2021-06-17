#include "MainScene.h"
#include "ui_mainscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QSound>


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    this->setFixedSize(320, 588);
    this->setWindowTitle("翻金币界面");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建开始菜单栏
    QMenuBar *myBar = menuBar();
    this->setMenuBar(myBar);     //添加
    QMenu *startMenu = myBar->addMenu("开始");
    QAction *actQuit = startMenu->addAction("退出");
    connect(actQuit, &QAction::triggered, [=](){
        this->close();
    });

    //开始按钮
    startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,
                   this->height()*0.7);

    chooseScene = new ChooseLevelScene(this);

    QSound *startSound = new QSound(":res/TapButtonSound.wav");

    connect(startBtn, &MyPushButton::clicked, [=](){
        //设置绝对位置
        chooseScene->setGeometry(this->geometry());
        //播放音效
        startSound->play();
        //形成上下弹跳效果
        startBtn->zoom1();
        startBtn->zoom2();

        //延时切入到关卡选择场景
        QTimer::singleShot(100, this, [=](){
            this->hide();
            chooseScene->show();
        });
    });

    //选择关卡界面点击返回按钮，切到主界面
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });
}

//绘制事件 虚函数 可以重写
void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap  pixmap;

    //绘制背景
    pixmap.load(":res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    //绘制标题
    pixmap.load(":/res/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.5, pixmap.height()*0.5);    //重新定义标题尺寸
    painter.drawPixmap(10, 30, pixmap.width(), pixmap.height(), pixmap);
}

MainScene::~MainScene()
{
    delete ui;
}
