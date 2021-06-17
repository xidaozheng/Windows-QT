#include "PlayScene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QFont>
#include <QLabel>
#include <QPropertyAnimation>
#include "MyPushButton.h"
#include "dataconfig.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    this->setFixedSize(320, 588);
    this->setWindowTitle("游戏界面");
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
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav");
    QSound *winSound  = new QSound(":/res/LevelWinSound.wav");

    //创建返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &MyPushButton::clicked, [=](){
        backSound->play();

        QTimer::singleShot(100, this, [=](){
            emit this->chooseSceneBack();
        });
    });

    QLabel *label = new QLabel;
    label->setParent(this);
    label->setGeometry(30, this->height()-50, 120, 50);
    QString str = QString("Level: %1").arg(levelNum);
    label->setText(str);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(16);
    label->setFont(font);

    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int row=0; row<4; row++)
    {
        for(int column=0; column<4; column++)
        {
            this->gameArray[row][column] = config.mData[levelNum][row][column];
        }
    }

    //显示金币背景图案
    for(int row=0; row<4; row++)
    {
        for(int column=0; column<4; column++)
        {
            //绘制背景图片
            QLabel *label = new QLabel(this);
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(57+row*50, 200+column*50);

            //创建金币
            QString str;
            if(this->gameArray[row][column] == 1)
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";

            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+row*50, 204+column*50);

            //更新金币类的属性
            coin->posX = row;
            coin->posY = column;
            coin->flag = this->gameArray[row][column];
            coinBtn[row][column] = coin;

            //点击金币 进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                flipSound->play();

                for(int row=0; row<4; row++)
                {
                    for(int column=0; column<4; column++)
                    {
                        coinBtn[row][column]->isWin = true;
                    }
                }

                //金币翻转实现
                coin->changeFlag();

                this->gameArray[row][column] = this->gameArray[row][column]==0 ? 1:0;

                //翻转周围金币
                QTimer::singleShot(200, this, [=](){
                    //周围的右侧金币翻转条件
                    if(coin->posX+1 <= 3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }

                    //周围的左侧金币翻转条件
                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }

                    //周围的上侧金币翻转条件
                    if(coin->posY+1 <= 3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }

                    //周围的左侧金币翻转条件
                    if(coin->posY-1 >= 0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        //胜利了
                        winSound->play();
                        //将所有按钮的胜利标志改为true
                        for(int i=0; i<4; i++)
                        {
                            for(int j=0; j<4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片弹下来
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始的位置
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        //设置结束的位置
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y()+114, winLabel->width(), winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });
            });
        }
    }
}

//绘制事件 虚函数 可以重写
void PlayScene::paintEvent(QPaintEvent *event)
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

