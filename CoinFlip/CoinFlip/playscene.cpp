#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "mypushbutton.h"
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

//playscene::playscene(QWidget *parent) : QMainWindow(parent)
//{

//}


playscene::playscene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav", this);
    //胜利音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav", this);


    //初始化游戏场景
    //设置固定大小
    setFixedSize(320, 588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("游戏场景");

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
        backSound->play();
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


    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());


    //显示金币背景图案
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            //绘制背景图片
            QLabel *label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50, 200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                //显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                //显示银币
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50, 204+j*50);

            //给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //1正面 0反面

            //将金币放入到 金币的二维数组里 以便以后的维护
            coinBtn[i][j] = coin;

            //点击金币 进行翻转
            connect(coin, &MyCoin::clicked, [=](){

                flipSound->play();
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();

                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                //翻转周围硬币

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
                        qDebug() << "胜利了";
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
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

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
