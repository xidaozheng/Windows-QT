#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "mypushbutton.h"
#include <QLabel>
#include <QFont>

//playscene::playscene(QWidget *parent) : QMainWindow(parent)
//{

//}


playscene::playscene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
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

    //显示当前关卡
    QLabel *label = new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(18);
    str = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30, this->height()-50, 120, 50);
}

void playscene::paintEvent(QPaintEvent *event)
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
