#include "gamestart.h"
#include "ui_gamestart.h"
#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include<QTextStream>
#include<QIcon>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QMessageBox>
#include"log.h"
GameStart::GameStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameStart)
{
    this->setFocus();
    gstop = new Gamestop;
    gstop->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口
    gstop->setFixedSize(400,150);                  //Dialog固定大小
    gstop->setAutoFillBackground(true);        //设置gstop的背景图
    QPixmap gstopbg(":/BG/src/BG20.png");
    QPalette gstop_palette = gstop->palette();
    gstop_palette.setBrush(QPalette::Window,QBrush(gstopbg));
    gstop->setPalette(gstop_palette);

    gover =new GameOver;
    gover->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口


    ui->setupUi(this);

    //初始的设置
    connect(&clockStart,SIGNAL(timeout()),this,SLOT(clockStartOut()));
    connect(&clockGame,SIGNAL(timeout()),this,SLOT(clockGameOut()));

    sixLabels[0]=ui->label_key1;    //把6个显示图片的label放到数组中以便操作
    sixLabels[1]=ui->label_key2;
    sixLabels[2]=ui->label_key3;
    sixLabels[3]=ui->label_key4;
    sixLabels[4]=ui->label_key5;
    sixLabels[5]=ui->label_key6;

    BGmusic0=new QSound(":/music/src/music/0.wav");
    BGmusic1=new QSound(":/music/src/music/1.wav");
    BGmusic2=new QSound(":/music/src/music/2.wav");
    BGmusic3=new QSound(":/music/src/music/3.wav");
    BGmusic4=new QSound(":/music/src/music/4.wav");
    BGMs[0]=BGmusic0;
    BGMs[1]=BGmusic1;
    BGMs[2]=BGmusic2;
    BGMs[3]=BGmusic3;
    BGMs[4]=BGmusic4;


    //背景音乐设置
    withmusic=true;
    QIcon button_ico(":/gamestartLabels/src/withmusic.png");
    ui->pushButton_music->setIcon(button_ico);
    //放置游戏界面背景图相关
    //...
    //设置开始暂停按钮

    //...
}

GameStart::~GameStart()
{
    delete ui;
    delete BGmusic0;
    delete BGmusic1;
    delete BGmusic2;
    delete BGmusic3;
    delete BGmusic4;
}

//进入游戏界面时初始化数据和画面
void GameStart::flashNow(int S)
{
    if(S==8)
    {
        //设计随机背景随机
        int randBG=qrand()%5;
        BGM=randBG;
        BG=qrand()%3;
        this->setAutoFillBackground(true);
        QPixmap bgImages(":/GamestartBG/src/BG9_"+QString::number(BG)+".png");
        QPalette this_palette = this->palette();
        this_palette.setBrush(QPalette::Window,QBrush(bgImages));
        this->setPalette(this_palette);
        //随机背景音乐
        BGMs[BGM]->setLoops(5);
        startBGM();
        //所有数据初始化
        horse1IsRun2=true;
        horse2IsRun2=false;
        inGaming=false;
        duringGame=false;
        defeat=false;
        getNewHorse=-1;

        rivalHorseX=90;
        rivalHorseY=160;
        myHorseX=80;
        myHorseY=220;

        if(!gaming_IsHard)
        {
            RivalHorsePath0=GetStandHorsePath(userInf[gaming_rival].TopHorseE);
            RivalHorsePath1=GetRunHorsePath1(userInf[gaming_rival].TopHorseE);
            RivalHorsePath2=GetRunHorsePath2(userInf[gaming_rival].TopHorseE);
        }
        else
        {
            RivalHorsePath0=GetStandHorsePath(userInf[gaming_rival].TopHorseH);
            RivalHorsePath1=GetRunHorsePath1(userInf[gaming_rival].TopHorseH);
            RivalHorsePath2=GetRunHorsePath2(userInf[gaming_rival].TopHorseH);
        }
        MyHorsePath0=GetStandHorsePath(gaming_horse);
        MyHorsePath1=GetRunHorsePath1(gaming_horse);
        MyHorsePath2=GetRunHorsePath2(gaming_horse);
        ui->label_myHorse->move(myHorseX,myHorseY);
        ui->label_rivalHorse->move(rivalHorseX,rivalHorseY);
        setLabelPic(ui->label_myHorse,MyHorsePath0);
        setLabelPic(ui->label_rivalHorse,RivalHorsePath0);
        //ui->label_name1->setText(userInf[NowUserID].userName);
        //ui->label_name2->setText(userInf[gaming_rival].userName);
        ui->label_score1->setText("0");
        ui->label_score2->setText("0");
        ui->textBrowser_log->clear();
        ui->pushButton_StartandStop->setText("开始");
        ui->horizontalSlider->setValue(0);
        ui->progressBar_process->setValue(0);
        ui->label_lefttime->setText("2.00");
        clockStart.setInterval(1000);
        clockGame.setInterval(50);
        if(gaming_IsHard)
            keyMod=26;
        else
            keyMod=4;
        myScore=0;
        rivalScore=0;
        indexScore=0;
        indexMx=0;
        countdown=3;
        ui->lcdNumber_lefttime->display(countdown);
        remainTime=40;      //游戏总时长
        keyGroup=0;
        keyIndex=0;
        CompleteTime=2.00;  //默认按完一组按键用时2.00s
        correctKeys=0;
        rivalHorseX=0;
        myHorseX=0;
        //初始化界面
        if(gaming_IsHard)
            flashHardLabel();
        else
            flashEasyLabel();
    }
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "进入游戏中...\n";
    logtemp.close();
}
//给一个label贴图
void GameStart::setLabelPic(QLabel *label, QString PicPath)
{
    QImage img(PicPath);
    label->setPixmap(QPixmap::fromImage(img));
}
//简单模式下刷新6个label上的图，并且记录在keys[]数组中
void GameStart::flashEasyLabel()
{
    QString PicPath;
    for(int i=0;i<6;i++)
    {
        keys[i]=qrand()%keyMod;
        PicPath=getEasyPicPath(keys[i]);
        setLabelPic(sixLabels[i],PicPath);
    }
}
//简单模式下获取序列代表的图片的路径
QString GameStart::getEasyPicPath(int randpic)
{
    QString PicPath;
    switch(randpic)
    {
    case 0:
        PicPath=":/gamestartLabels/src/UP.png";
        break;
    case 1:
        PicPath=":/gamestartLabels/src/DOWN.png";
        break;
    case 2:
        PicPath=":/gamestartLabels/src/LEFT.png";
        break;
    case 3:
        PicPath=":/gamestartLabels/src/RIGHT.png";
        break;
    }
    return PicPath;
}
//简单模式下获取序列代表的按键正确后图片的路径
QString GameStart::getEcorrectPath(int index)   //传入的是上下左右代表值
{
    QString PicPath;
    switch(index)
    {
    case 0:
        PicPath=":/gamestartLabels/src/UP_G.png";
        break;
    case 1:
        PicPath=":/gamestartLabels/src/DOWN_G.png";
        break;
    case 2:
        PicPath=":/gamestartLabels/src/LEFT_G.png";
        break;
    case 3:
        PicPath=":/gamestartLabels/src/RIGHT_G.png";
        break;
    }
    return PicPath;
}
//简单模式下获取序列代表的按键错误后图片的路径
QString GameStart::getEwrongPath(int index)   //传入的是上下左右代表值
{
    QString PicPath;
    switch(index)
    {
    case 0:
        PicPath=":/gamestartLabels/src/UP_R.png";
        break;
    case 1:
        PicPath=":/gamestartLabels/src/DOWN_R.png";
        break;
    case 2:
        PicPath=":/gamestartLabels/src/LEFT_R.png";
        break;
    case 3:
        PicPath=":/gamestartLabels/src/RIGHT_R.png";
        break;
    }
    return PicPath;
}
//功能和简单模式下的一样
void GameStart::flashHardLabel()
{
    QString PicPath;
    for(int i=0;i<6;i++)
    {
        keys[i]=qrand()%keyMod;
        PicPath=getHardPicPath(keys[i]);
        setLabelPic(sixLabels[i],PicPath);
    }
}
QString GameStart::getHardPicPath(int randpic)
{
    QString PicPath;
    char i='A';
    i=char(i+randpic);
    PicPath=":/gamestartLabels/src/"+QString(i)+".png";
    return PicPath;
}
QString GameStart::getHcorrectPath(int index)
{
    QString PicPath;
    char i='A';
    i=char(i+index);
    PicPath=":/gamestartLabels/src/"+QString(i)+"_G.png";
    return PicPath;
}
QString GameStart::getHwrongPath(int index)
{
    QString PicPath;
    char i='A';
    i=char(i+index);
    PicPath=":/gamestartLabels/src/"+QString(i)+"_R.png";
    return PicPath;
}

//按下暂停按钮响应，启动和停止计时器
void GameStart::on_pushButton_StartandStop_clicked()
{
    bee.play();
    if(inGaming)
    {
        ui->textBrowser_log->append("暂停游戏...");
        ui->pushButton_StartandStop->setText("开始游戏");
        stopBGM();
        //暂停游戏
        //输出日志
        QFile logtemp("HR_log.txt");
        logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
        QTextStream out_log(&logtemp);
        out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
                 "暂停游戏..."<<qSetFieldWidth(1)<<'\n';
        logtemp.close();
        QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString logs=userInf[NowUserID].userName+"暂停游戏";
        Log indexLog(time,logs);
        indexLog.start();

        inGaming=!inGaming;
        duringGame=false;
        if(clockGame.isActive())
            clockGame.stop();
        if(clockStart.isActive())
            clockStart.stop();
        countdown=3;
        gstop->show();
    }
    else
    {
        ui->textBrowser_log->append("开始游戏...");
        ui->pushButton_StartandStop->setText("暂停游戏");
        startBGM();
        //继续游戏
        //输出日志
        QFile logtemp("HR_log.txt");
        logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
        QTextStream out_log(&logtemp);
        out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
                 "继续游戏..."<<qSetFieldWidth(1)<<'\n';
        logtemp.close();
        QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString logs=userInf[NowUserID].userName+"继续游戏";
        Log indexLog1(time,logs);
        indexLog1.start();

        inGaming=!inGaming;
        ui->lcdNumber_lefttime->setStyleSheet("background-color: yellow;QLCDNumber{color: red}");
        ui->lcdNumber_lefttime->display(888);
        clockStart.start();
    }
    this->setFocus();
}


void GameStart::clockStartOut()
{
    //开始游戏倒计时每隔一秒触发
    ui->lcdNumber_lefttime->display(countdown);    
    countdown--;
    if(countdown<=0)
    {
        clockStart.stop();
        clockGame.start();
        duringGame=true;
        ui->lcdNumber_lefttime->setStyleSheet("QLCDNumber{background-color: yellow;color: green}");
        ui->lcdNumber_lefttime->display(remainTime);
        countdown=3;
    }

}

// 播放音乐
void GameStart::startBGM()
{
    if (withmusic) {
        BGMs[BGM]->play();
    }
}

// 停止播放音乐
void GameStart::stopBGM()
{
    if (withmusic) {
        BGMs[BGM]->stop();
    }
}

//没隔0.05s刷新一次界面
void GameStart::clockGameOut()
{
    //游戏开始之后每隔0.05s刷新一次
    int sliderIndex;    //滑动条上滑块的位置
    double indexTime;   //当前组剩余时间
    sliderIndex=ui->horizontalSlider->value();
    indexTime=2-(sliderIndex+0.0)/50;   //计算当前组剩余的时间
    labelleftValue=2-indexTime;
    ui->label_lefttime->setText(QString::number(indexTime)+"s");
    //刷新马跑的
    if(sliderIndex==13)
    {
        moveMyHorse(myHorseX+1,myHorseY);
        moveRivalHorse(rivalHorseX+1,rivalHorseY);
    }
    if(sliderIndex==25)
    {
        moveMyHorse(myHorseX+2,myHorseY);
        moveRivalHorse(rivalHorseX+2,rivalHorseY);
    }

    if(sliderIndex==39)
    {
        moveMyHorse(myHorseX+3,myHorseY);
        moveRivalHorse(rivalHorseX+3,rivalHorseY);
    }

    if(sliderIndex==52)
    {
        moveMyHorse(myHorseX+4,myHorseY);
        moveRivalHorse(rivalHorseX+4,rivalHorseY);
    }
    if(sliderIndex==65)
    {
        moveMyHorse(myHorseX+5,myHorseY);
        moveRivalHorse(rivalHorseX+5,rivalHorseY);
    }
    if(sliderIndex==78)
    {
        moveMyHorse(myHorseX+6,myHorseY);
        moveRivalHorse(rivalHorseX+6,rivalHorseY);
    }
    if(sliderIndex==91)
    {
        moveMyHorse(myHorseX+7,myHorseY);
        moveRivalHorse(rivalHorseX+7,rivalHorseY);
    }
    //每1s刷新一次
    if(sliderIndex==50)
    {

        remainTime--;
        ui->lcdNumber_lefttime->display(remainTime);
        ui->progressBar_process->setValue(100-int(remainTime*2.5));
    }

    //每2s刷新一次
    if(sliderIndex==100)
    {
        //根据按键的正确情况刷自己马的位置、累积显示积分
        //在edit框中增加这组按键的评分、加分、马前进距离
        //显示对手的马和积分
        DealData();
        //......
        keyGroup++;
        if(keyGroup==19)
        {
            //倒计时颜色改为红色
            ui->lcdNumber_lefttime->setStyleSheet("QLCDNumber{background-color: yellow;color: #FF0088}");

        }
        //游戏完成
        if(keyGroup>=20)
        {
            //关闭音乐
            stopBGM();
            //结算游戏结果，刷新个人最高成绩，刷新排行榜，是否超越对手，是否开到新马
            remainTime--;
            ui->lcdNumber_lefttime->display(remainTime);
            ui->progressBar_process->setValue(100);
            Conclude();

            clockGame.stop();
            //emit display(11);
        }
        //换下一组
        else
        {
            remainTime--;
            ui->lcdNumber_lefttime->display(remainTime);
            ui->progressBar_process->setValue(100-int(remainTime*2.5));
            if(gaming_IsHard)
                flashHardLabel();
            else
                flashEasyLabel();
            keyIndex=0;     //下一组比对的按键序列是第0个
            CompleteTime=2.00;  //默认按完一组按键用时2.00s
            correctKeys=0;  //一组中正确的按键次数也置0
        }
        ui->horizontalSlider->setValue(0);
    }
    else
    {
        ui->horizontalSlider->setValue(sliderIndex+2);
    }
}
//整个界面上的键盘响应，主要在游戏过程中奏效
void GameStart::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space)
        on_pushButton_StartandStop_clicked();
    if(!duringGame)
        return;     //如果游戏还没开始就屏蔽按键
    if(gaming_IsHard)
    {
        if(keyIndex>=6)
        {}
        else
        {
            HDealPress(event);
        }
    }
    else
    {
        if(keyIndex>=6)
        {}
        else
        {
            EDealPress(event);
        }
    }
}
//困难模式下对按键的处理
void GameStart::HDealPress(QKeyEvent *event)
{
    int indexinput; //表示按下按键的值
    QString keytext;
    QChar keyChar;
    keytext=event->text();
    keyChar=keytext.at(0);
    if(!(keyChar>='a'&&keyChar<='z'))
    {
        return;
    }
    indexinput=int(keyChar.unicode()-'a');

    //判断和显示的值是否相同,并且更换图片
    if(indexinput==keys[keyIndex])
    {
        QString correctPath;
        correctPath=getHcorrectPath(keys[keyIndex]);
        setLabelPic(sixLabels[keyIndex],correctPath);
        correctKeys++;
    }
    else
    {
        QString wrongPath;
        wrongPath=getHwrongPath(keys[keyIndex]);
        setLabelPic(sixLabels[keyIndex],wrongPath);
    }
    //比对结束，需要比对的按键序列加1
    if(keyIndex==5)
    {
        CompleteTime=labelleftValue;
    }
    keyIndex++;
}
//简单模式下对按键的处理
void GameStart::EDealPress(QKeyEvent *event)
{
    int indexinput; //表示按下按键的值
    if(event->key()==Qt::Key_Up)
        indexinput=0;
    else if(event->key()==Qt::Key_Down)
        indexinput=1;
    else if(event->key()==Qt::Key_Left)
        indexinput=2;
    else if(event->key()==Qt::Key_Right)
        indexinput=3;
    else
        return;

    //判断和显示的值是否相同,并且更换图片
    if(indexinput==keys[keyIndex])
    {
        QString correctPath;
        correctPath=getEcorrectPath(keys[keyIndex]);
        setLabelPic(sixLabels[keyIndex],correctPath);
        correctKeys++;
    }
    else
    {
        QString wrongPath;
        wrongPath=getEwrongPath(keys[keyIndex]);
        setLabelPic(sixLabels[keyIndex],wrongPath);
    }
    //比对结束，需要比对的按键序列加1
    if(keyIndex==5)
    {
        CompleteTime=labelleftValue;
    }
    keyIndex++;
}
//在一组按键结束后调用，根据用户的正确率积分，刷新界面的内容
void GameStart::DealData()
{
    //计算玩家一组的积分和马跑的距离，写入临时游戏数据数组
    indexScore=fixIndexScore(correctKeys,CompleteTime);
    indexMx=indexScore/8;
    /*gamingTB[keyGroup].tx=indexScore;
     gamingTB[keyGroup].mx=indexMx;*///在线版不使用
    //累计玩家积分，显示积分，累计玩家马跑的距离
    myScore+=indexScore;
    myHorseX+=indexMx;
    ui->label_score1->setText(QString::number(myScore));
    //累计对手积分，显示积分，累计马跑的距离
    if(!gaming_IsHard)
    {
        rivalScore+=userInf[gaming_rival].topE/20;
        rivalHorseX+=userInf[gaming_rival].topE/160;
    }
    else
    {
        rivalScore+=userInf[gaming_rival].topH/20;
        rivalHorseX+=userInf[gaming_rival].topH/160;
    }
    ui->label_score2->setText(QString::number(rivalScore));
    //计算评价
    QString evaluation;
    switch(correctKeys)
    {
    case 6:
        evaluation="perfect!";
        break;
    case 5:
        evaluation="great!";
        break;
    case 4:
        evaluation="good!";
        break;
    case 0:
        evaluation="miss!";
        break;
    default:
        evaluation="bad!";

    }
    //在textbroser框中增加这组按键的评分、加分
    ui->textBrowser_log->append(QString::number(keyGroup)+": "+evaluation+" "+QString::number(CompleteTime)+
                                "s按完!\n"+" 积分+："+QString::number(indexScore));
    //显示玩家马的跑动
    moveMyHorse(myHorseX,myHorseY);
    //显示对手马的跑动
    moveRivalHorse(rivalHorseX,rivalHorseY);

}
int GameStart::fixIndexScore(int cK, double cT)
{
    return int((80.0*cT*cT-400*cT+680)*cK/6);
}

void GameStart::moveMyHorse(int x,int y)
{
    ui->label_myHorse->move(x,y);
    flashMyHorse();
}
void GameStart::moveRivalHorse(int x,int y)
{
    ui->label_rivalHorse->move(x,y);
    flashRivalHorse();
}
void GameStart::flashMyHorse()
{
    if(horse1IsRun2)
        setLabelPic(ui->label_myHorse,MyHorsePath1);
    else
        setLabelPic(ui->label_myHorse,MyHorsePath2);
    horse1IsRun2=!horse1IsRun2;
}
void GameStart::flashRivalHorse()
{
    if(horse2IsRun2)
        setLabelPic(ui->label_rivalHorse,RivalHorsePath1);
    else
        setLabelPic(ui->label_rivalHorse,RivalHorsePath2);
    horse2IsRun2=!horse2IsRun2;
}
QString GameStart::GetStandHorsePath(int index)
{
    return ":/GamestartHorses/src/HORSE"+QString::number(index)+"_STAND_120_90.png";
}
QString GameStart::GetRunHorsePath1(int index)
{
    return ":/GamestartHorses/src/HORSE"+QString::number(index)+"_RUN1_120_90.png";
}
QString GameStart::GetRunHorsePath2(int index)
{
    return ":/GamestartHorses/src/HORSE"+QString::number(index)+"_RUN2_120_90.png";
}
void GameStart::Conclude()
{
    if(gaming_IsHard)
    {
        //刷新最高成绩
        if(myScore>userInf[NowUserID].topH)
        {
            isNewScore=true;
            userInf[NowUserID].topH=myScore;
            userInf[NowUserID].TopHorseH=gaming_horse;
            /*for(int i=0;i<20;i++)
            {
                userInf[NowUserID].TBH[i].mx=gamingTB[i].mx;
                userInf[NowUserID].TBH[i].tx=gamingTB[i].tx;
            }*///在线版不使用
        }
        //刷新排行榜
        refreshH();
        //累计游戏时长
        userInf[NowUserID].userExp+=40;
        //是否击败对手
        if(myScore>rivalScore)
            defeat=true;
        //开马
        OpenHorse();

    }
    else
    {
        //刷新最高成绩
        if(myScore>userInf[NowUserID].topE)
        {
            isNewScore=true;
            userInf[NowUserID].topE=myScore;
            userInf[NowUserID].TopHorseE=gaming_horse;
            /*for(int i=0;i<20;i++)
            {
                userInf[NowUserID].TBE[i].mx=gamingTB[i].mx;
                userInf[NowUserID].TBE[i].tx=gamingTB[i].tx;
            }*///在线版不使用
        }
        //刷新排行榜
        refreshE();
        //累计游戏时长
        userInf[NowUserID].userExp+=40;
        //是否击败对手
        if(myScore>rivalScore)
            defeat=true;
        //开马
        OpenHorse();
    }
    //写入文件，以免意外退出
    /*QFile fuserInf_update("userInf.dat");
    fuserInf_update.open(QIODevice::WriteOnly);
    QDataStream in_fuserInf_update(&fuserInf_update);
    for(int i=0;i<UserNum;i++)
        in_fuserInf_update<<userInf[i];
    fuserInf_update.close();*/

    //同步至数据库
    uploadNowUser();
    //显示结果，击败刷新个人记录、排行榜情况
    if(defeat)
    {
        ui->textBrowser_log->append("恭喜你,超越了"+userInf[gaming_rival].userName+"!!!");
    }
    else
    {
        ui->textBrowser_log->append("很遗憾,没有击败"+userInf[gaming_rival].userName+"!!!");
    }
    if(isNewScore)
    {
        ui->textBrowser_log->append("诞生你的新纪录了!!!");
    }
    else
    {

    }
    if(inrank)
    {
        ui->textBrowser_log->append("进入排行榜了，快去看!!!");
    }
    else
    {
        ui->textBrowser_log->append("未能进入排行榜。");
    }
    //游戏结束，显示结算界面
    gover->SetResult(this);
    gover->flash();
    gover->show();

}
//更新用户数据
void GameStart::uploadNowUser()
{
    QSqlQuery query;
    QString cmd;
    cmd="update userInf set userExp="+QString::number(userInf[NowUserID].userExp)
            +",horseExp="+QString::number(userInf[NowUserID].horseExp)
            +",topE="+QString::number(userInf[NowUserID].topE)
            +",topH="+QString::number(userInf[NowUserID].topH)
            +",rankTopE="+QString::number(userInf[NowUserID].rankTopE)
            +",rankTopH="+QString::number(userInf[NowUserID].rankTopH)
            +",totalHorse="+QString::number(userInf[NowUserID].totalHorse)
            +",TopHorseE="+QString::number(userInf[NowUserID].TopHorseE)
            +",TopHorseH="+QString::number(userInf[NowUserID].TopHorseH)+" where name='"+userInf[NowUserID].userName+"'";
    query.exec(cmd);
    if(getNewHorse!=-1&&getNewHorse!=20)
    {
        cmd="update hasHorse set h"+QString::number(getNewHorse)+
                "=1 where name='"+userInf[NowUserID].userName+"'";
        query.exec(cmd);
        cmd="update horsekey set hk"+QString::number(userInf[NowUserID].totalHorse-1)+
                "="+QString::number(getNewHorse)+" where name='"+userInf[NowUserID].userName+"'";
        query.exec(cmd);
    }
    if(getNewHorse==19)
    {
        cmd="update hasHorse set h19=1 where name='"+userInf[NowUserID].userName+"'";
        query.exec(cmd);
        cmd="update horseKey set h19=20 where name='"+userInf[NowUserID].userName+"'";
        query.exec(cmd);
    }
}

//同步排行榜
void GameStart::getRank()
{
    QSqlQuery query,queryh;
    QString cmd,cmd1;
    cmd="select * from rankE";
    cmd1="select * from rankH";
    query.exec(cmd);
    queryh.exec(cmd1);
    int index=0;
    while(query.next())
    {
        queryh.next();
        rankE[index].UserName=query.value(0).toString();
        rankE[index].Score=query.value(1).toInt();
        rankH[index].UserName=queryh.value(0).toString();
        rankH[index].Score=queryh.value(1).toInt();
        if(index==4)
            break;
    }
}
//上传同步排行榜
void GameStart::uploadRank()
{
    QSqlQuery query,queryh;
    QString cmd,cmd1;
    cmd="delete from rankE";
    cmd1="delete from rankH";
    query.exec(cmd);
    queryh.exec(cmd1);
    for(int i=0;i<5;i++)
    {
        cmd="insert into rankE values('"+rankE[i].UserName+"',"+QString::number(rankE[i].Score)+")";
        cmd1="insert into rankH values('"+rankH[i].UserName+"',"+QString::number(rankH[i].Score)+")";
        query.exec(cmd);
        queryh.exec(cmd1);
    }
}
void GameStart::refreshE()
{
    for(int i=0;i<5;i++)
    {
        inrank=false;
        if(myScore>rankE[i].Score)
        {
            for(int j=4;j>i;j--)
            {
                rankE[j].Score=rankE[j-1].Score;
                rankE[j].UserName=rankE[j-1].UserName;
            }
            rankE[i].Score= myScore;
            rankE[i].UserName=userInf[NowUserID].userName;
            if((i+1)<userInf[NowUserID].rankTopE)
                userInf[NowUserID].rankTopE=i+1;
            inrank=true;
            //保存排行榜
            uploadRank();
            break;
        }
    }
}
void GameStart::refreshH()
{
    for(int i=0;i<5;i++)
    {
        inrank=false;
        if(myScore>rankH[i].Score)
        {
            for(int j=4;j>i;j--)
            {
                rankH[j].Score=rankH[j-1].Score;
                rankH[j].UserName=rankH[j-1].UserName;
            }
            rankH[i].Score= myScore;
            rankH[i].UserName=userInf[NowUserID].userName;
            if((i+1)<userInf[NowUserID].rankTopH)
                userInf[NowUserID].rankTopH=i+1;
            inrank=true;
            //保存排行榜文件
            uploadRank();
            break;
        }
    }
}
void GameStart::OpenHorse()
{
    if(userInf[NowUserID].totalHorse==20)
    {
        //已经拥有了所有的马
        getNewHorse=20;
        ui->textBrowser_log->append("你已经解锁了所有的马儿!!!");
    }
    else
    {
        int randOpen;   //控制开出新马的概率
        int newHorse;   //新马编号
        int i;
        randOpen=qrand()%1;
        if(randOpen==0) //现在控制概率为1
        {
            //从0-18号马中随机抽取一匹，19号马儿在集齐前19匹时自动解锁
            newHorse=qrand()%19;
            //判断马是否已存在
            for(i=0;i<userInf[NowUserID].totalHorse;i++)
            {
                if(newHorse==userInf[NowUserID].horseKey[i])
                    break;
            }
            if(i<userInf[NowUserID].totalHorse) //已经拥有了
            {
                ui->textBrowser_log->append("差一点就解锁新的马儿了!!!");
            }
            else    //未拥有
            {
                //玩家增加一匹马儿
                userInf[NowUserID].totalHorse++;
                userInf[NowUserID].hasHorse[newHorse]=true;
                userInf[NowUserID].horseKey[userInf[NowUserID].totalHorse-1]=newHorse;
                ui->textBrowser_log->append("你成功解锁了你的第"+QString::number(userInf[NowUserID].totalHorse)
                                            +"匹马儿,快去试试吧!!!");
                getNewHorse=newHorse;
                if(userInf[NowUserID].totalHorse==19)   //当集齐19匹马时自动解锁最后一匹
                {
                    //增加最后一匹马的记录
                    userInf[NowUserID].totalHorse++;
                    userInf[NowUserID].hasHorse[19]=true;
                    userInf[NowUserID].horseKey[19]=19;
                    ui->textBrowser_log->append("你已经解锁完19匹马，达成终极成就，“高清无码”传说马儿已送出!!!");
                    getNewHorse=19;
                }
            }
        }
    }
}

void GameStart::on_pushButton_music_clicked()
{
    bee.play();
    if(withmusic)
    {
        QIcon button_ico(":/gamestartLabels/src/withoutmusic.png");
        ui->pushButton_music->setIcon(button_ico);
        BGMs[BGM]->stop();
    }
    else
    {
        QIcon button_ico(":/gamestartLabels/src/withmusic.png");
        ui->pushButton_music->setIcon(button_ico);
        BGMs[BGM]->play();
    }
    withmusic=!withmusic;
    this->setFocus();
}
