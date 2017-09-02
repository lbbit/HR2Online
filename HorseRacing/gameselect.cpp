#include "gameselect.h"
#include "ui_gameselect.h"
#include"globalvariable.h"
#include <QFile>
#include <QDataStream>
#include<QTextStream>
#include"log.h"

GameSelect::GameSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSelect)
{
    this->setFocus();
    IsHard=false;
    thisHorse=1;
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG4.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);

}

GameSelect::~GameSelect()
{
    delete ui;
}

void GameSelect::on_pushButton_return_clicked()
{
    bee.play();
    emit display(3);
}

void GameSelect::flashNow()
{
    this->setFocus();
    rivalID=qrand()%UserNum;
    IsHard=false;
    thisHorse=qrand()%userInf[NowUserID].totalHorse;
    ui->label_select_rival->setText(userInf[rivalID].userName);
    QImage *EH_img;
    EH_img = new QImage(":/Gameselect/src/EASY_90_40.png");
    ui->label_select_difficulty->setPixmap(QPixmap::fromImage(*EH_img));
    EH_img->load(":Horselib/src/HORSE"+QString::number(userInf[NowUserID].horseKey[thisHorse])+"_STAND_120_90.png");
    ui->label_select_horse->setPixmap(QPixmap::fromImage(*EH_img));
    delete EH_img;
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "进入游戏准备界面...\n";
    logtemp.close();
    QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logs=userInf[NowUserID].userName+"进入游戏准备界面";
    Log indexLog(time,logs);
    indexLog.start();
}

void GameSelect::on_pushButton_rival_last_clicked()
{
    bee.play();
    rivalID=(rivalID-1);
    if(rivalID==-1)
        rivalID=UserNum-1;
    ui->label_select_rival->setText(userInf[rivalID].userName);
}

void GameSelect::on_pushButton_rival_next_clicked()
{
    bee.play();
    rivalID=(rivalID+1)%UserNum;
    ui->label_select_rival->setText(userInf[rivalID].userName);
}

void GameSelect::on_pushButton_difficulty_last_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        EH_img = new QImage(":/Gameselect/src/HARD_90_40.png");
        ui->label_select_difficulty->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    else
    {
        EH_img = new QImage(":/Gameselect/src/EASY_90_40.png");
        ui->label_select_difficulty->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
}

void GameSelect::on_pushButton_difficulty_next_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        EH_img = new QImage(":/Gameselect/src/HARD_90_40.png");
        ui->label_select_difficulty->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    else
    {
        EH_img = new QImage(":/Gameselect/src/EASY_90_40.png");
        ui->label_select_difficulty->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
}

void GameSelect::on_pushButton_horse_last_clicked()
{
    bee.play();
    QImage *Horse_img;
    QString horsePath;
    thisHorse=thisHorse-1;
    if(thisHorse==-1)
        thisHorse=userInf[NowUserID].totalHorse-1;
    horsePath=":Horselib/src/HORSE"+QString::number(userInf[NowUserID].horseKey[thisHorse])+"_STAND_120_90.png";
    Horse_img = new QImage(horsePath);
    ui->label_select_horse->setPixmap(QPixmap::fromImage(*Horse_img));
    delete Horse_img;
}

void GameSelect::on_pushButton_horse_next_clicked()
{
    bee.play();
    QImage *Horse_img;
    QString horsePath;
    thisHorse=(thisHorse+1)%userInf[NowUserID].totalHorse;
    horsePath=":Horselib/src/HORSE"+QString::number(userInf[NowUserID].horseKey[thisHorse])+"_STAND_120_90.png";
    Horse_img = new QImage(horsePath);
    ui->label_select_horse->setPixmap(QPixmap::fromImage(*Horse_img));
    delete Horse_img;
}

void GameSelect::on_pushButton_gamestart_clicked()
{
    bee.play();
    //将用户的选记录下来，在游戏界面中提现出来
    gaming_rival=rivalID;
    gaming_IsHard=IsHard;
    gaming_horse=userInf[NowUserID].horseKey[thisHorse];
    display(8);
}
