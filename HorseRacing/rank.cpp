#include "rank.h"
#include "ui_rank.h"
#include"globalvariable.h"
#include<QFile>
#include<QDataStream>
#include<QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QMessageBox>
#include<QDebug>

#include<iostream>          //zhen
using namespace std;        //zhen

Rank::Rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rank)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG5.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
}

Rank::~Rank()
{
    delete ui;
}

void Rank::on_pushButton_return_clicked()
{
    bee.play();
    emit display(3);
    this->setFocus();
}
void Rank::flashNow()
{
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "查看了排行榜...\n";
    logtemp.close();
    this->setFocus();
    //放置刷新rank榜的相关程序，用来实时更新rank榜
    getRank();//同步服务器数据
    IsHard=false;
    QImage *EH_img;
    EH_img = new QImage(":/Rank/src/EASY_60_40.png");
    ui->label->setPixmap(QPixmap::fromImage(*EH_img));
    delete EH_img;

    ui->label_no1name->setText(rankE[0].UserName);
    ui->label_no1score->setText(QString::number(rankE[0].Score));
    ui->label_no2name->setText(rankE[1].UserName);
    ui->label_no2score->setText(QString::number(rankE[1].Score));
    ui->label_no3name->setText(rankE[2].UserName);
    ui->label_no3score->setText(QString::number(rankE[2].Score));
    ui->label_no4name->setText(rankE[3].UserName);
    ui->label_no4score->setText(QString::number(rankE[3].Score));
    ui->label_no5name->setText(rankE[4].UserName);
    ui->label_no5score->setText(QString::number(rankE[4].Score));
}

//获取服务器数据库中的排行榜信息
void Rank::getRank()
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
        index++;
        if(index==5)
            break;
    }
}

void Rank::on_pushButton_last_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        EH_img = new QImage(":/Rank/src/HARD_60_40.png");
        ui->label->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
        ui->label_no1name->setText(rankH[0].UserName);
        ui->label_no1score->setText(QString::number(rankH[0].Score));
        ui->label_no2name->setText(rankH[1].UserName);
        ui->label_no2score->setText(QString::number(rankH[1].Score));
        ui->label_no3name->setText(rankH[2].UserName);
        ui->label_no3score->setText(QString::number(rankH[2].Score));
        ui->label_no4name->setText(rankH[3].UserName);
        ui->label_no4score->setText(QString::number(rankH[3].Score));
        ui->label_no5name->setText(rankH[4].UserName);
        ui->label_no5score->setText(QString::number(rankH[4].Score));
    }
    else
    {

        EH_img = new QImage(":/Rank/src/EASY_60_40.png");
        ui->label->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
        ui->label_no1name->setText(rankE[0].UserName);
        ui->label_no1score->setText(QString::number(rankE[0].Score));
        ui->label_no2name->setText(rankE[1].UserName);
        ui->label_no2score->setText(QString::number(rankE[1].Score));
        ui->label_no3name->setText(rankE[2].UserName);
        ui->label_no3score->setText(QString::number(rankE[2].Score));
        ui->label_no4name->setText(rankE[3].UserName);
        ui->label_no4score->setText(QString::number(rankE[3].Score));
        ui->label_no5name->setText(rankE[4].UserName);
        ui->label_no5score->setText(QString::number(rankE[4].Score));
    }
    this->setFocus();
}

void Rank::on_pushButton_next_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        EH_img = new QImage(":/Rank/src/HARD_60_40.png");
        ui->label->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
        ui->label_no1name->setText(rankH[0].UserName);
        ui->label_no1score->setText(QString::number(rankH[0].Score));
        ui->label_no2name->setText(rankH[1].UserName);
        ui->label_no2score->setText(QString::number(rankH[1].Score));
        ui->label_no3name->setText(rankH[2].UserName);
        ui->label_no3score->setText(QString::number(rankH[2].Score));
        ui->label_no4name->setText(rankH[3].UserName);
        ui->label_no4score->setText(QString::number(rankH[3].Score));
        ui->label_no5name->setText(rankH[4].UserName);
        ui->label_no5score->setText(QString::number(rankH[4].Score));
    }
    else
    {

        EH_img = new QImage(":/Rank/src/EASY_60_40.png");
        ui->label->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
        ui->label_no1name->setText(rankE[0].UserName);
        ui->label_no1score->setText(QString::number(rankE[0].Score));
        ui->label_no2name->setText(rankE[1].UserName);
        ui->label_no2score->setText(QString::number(rankE[1].Score));
        ui->label_no3name->setText(rankE[2].UserName);
        ui->label_no3score->setText(QString::number(rankE[2].Score));
        ui->label_no4name->setText(rankE[3].UserName);
        ui->label_no4score->setText(QString::number(rankE[3].Score));
        ui->label_no5name->setText(rankE[4].UserName);
        ui->label_no5score->setText(QString::number(rankE[4].Score));
    }
    this->setFocus();
}
