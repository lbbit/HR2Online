#include "gameover.h"
#include "ui_gameover.h"
#include <QFile>
#include <QDataStream>
#include<QTextStream>
#include "log.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG13.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    //setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint); //隐藏 ？ 按钮
    //setWindowTitle("                              游戏结果");
}

GameOver::~GameOver()
{
    delete ui;
}
void GameOver::SetResult(GameStart *GS)
{
    isnewS=GS->isNewScore;
    myScore_o=GS->myScore;
    rivalScore_o=GS->rivalScore;
    defeat_o=GS->defeat;
    inrank_o=GS->inrank;
    getNewHorse_o=GS->getNewHorse;
    myhorsepath=GS->MyHorsePath0;
    rivalhorsepath=GS->RivalHorsePath0;
}
void GameOver::flash()
{
    this->setFocus();
    QImage *myH = new QImage(myhorsepath);
    QImage *rivalH = new QImage(rivalhorsepath);
    if(isnewS)
        ui->label_isnew->setText("（新纪录）");
    else
        ui->label_isnew->setText(NULL);
    ui->label_myscore->setText(QString::number(myScore_o));
    ui->label_rivalscore->setText(QString::number(rivalScore_o));
    if(defeat_o)
    {
        ui->label_1name->setText(userInf[NowUserID].userName);
        ui->label_2name->setText(userInf[gaming_rival].userName);
        ui->label_firstH->setPixmap(QPixmap::fromImage(*myH));
        ui->label_secondH->setPixmap(QPixmap::fromImage(*rivalH));

    }
    else
    {
        ui->label_2name->setText(userInf[NowUserID].userName);
        ui->label_1name->setText(userInf[gaming_rival].userName);
        ui->label_secondH->setPixmap(QPixmap::fromImage(*myH));
        ui->label_firstH->setPixmap(QPixmap::fromImage(*rivalH));
    }
    if(inrank_o)
        ui->label_inrank->setText("成功进入排行榜！");
    else
        ui->label_inrank->setText(NULL);
    QString time,logs;
    Log indexLog("","");
    switch(getNewHorse_o)
    {
    case -1:
        //没抽到
        ui->label_isnew_2->setText("（未抽中）");
        newhorsepath=":/Gameover/src/horse_PITY.png";
        break;
    case 19:
        //刚集齐所有的马
        ui->label_isnew_2->setText("（新马，集齐）");
        newhorsepath=":/Gameover/src/HORSE0_STAND_120_90.png";
        time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        logs=userInf[NowUserID].userName+"集齐所有皮肤！！！！！！！";
        indexLog.setTandL(time,logs);
        indexLog.start();
        break;
    case 20:
        //之前就集齐
        ui->label_isnew_2->setText("（已集齐）");
        newhorsepath=":/Gameover/src/horse_all.png";
        break;
    default:
        ui->label_isnew_2->setText("（新马）");
        //抽到新马
        newhorsepath=":/Gameover/src/HORSE"+QString::number(getNewHorse_o)+"_STAND_120_90.png";
        time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        logs=userInf[NowUserID].userName+"抽到新皮肤！";
        indexLog.setTandL(time,logs);
        indexLog.start();
        break;
    }
    QImage *newHorse = new QImage(newhorsepath);
    ui->label_newhorsepic->setPixmap(QPixmap::fromImage(*newHorse));
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "完成一局游戏..."<<qSetFieldWidth(1)<<'\n';
    logtemp.close();
    QString time0=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logs0=userInf[NowUserID].userName+"完成一局游戏";
    indexLog.setTandL(time0,logs0);
    indexLog.start();
}
void GameOver::on_pushButton_clicked()
{
    bee.play();
    emit display(4);
    close();
}
