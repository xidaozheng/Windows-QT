#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "mypushbutton.h"
#include <QTimer>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    setFixedSize(320, 588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    //添加项
    QAction *quit = startMenu->addAction("退出");
    connect(quit, &QAction::triggered, [=](){
        close();
    });

    //创建返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        //使用emit 将信号发出去
        QTimer::singleShot(100, this, [=](){
            emit this->chooseSceneBack();
        });
    });
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap  pix;

    //加载背景
    bool ret = pix.load(":/res/OtherSceneBg.png");
    if(!ret)
    {
        qDebug() << "关卡背景图片加载失败";
        return;
    }
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    ret = pix.load(":/res/Title.png");
    if(!ret)
    {
        qDebug() << "关卡标题图片加载失败";
        return;
    }
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
