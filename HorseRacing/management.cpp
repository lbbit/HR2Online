#include "management.h"
#include "ui_management.h"
#include"globalvariable.h"
#include<QFile>
#include<QFile>
#include<QDataStream>
#include<QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QMessageBox>
#include"log.h"
Management::Management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Management)
{
    ui->setupUi(this);
    IsHard=false;
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG7.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
}

Management::~Management()
{
    delete ui;
}

void Management::on_pushButton_return_clicked()
{
    bee.play();
    //保存头像的更改
    /*QFile fuserInf_update("userInf.dat");
    fuserInf_update.open(QIODevice::WriteOnly);
    QDataStream in_fuserInf_update(&fuserInf_update);
    for(int i=0;i<UserNum;i++)
        in_fuserInf_update<<userInf[i];
    fuserInf_update.close();*/
    savePort();


    emit display(3);
}
void Management::savePort()
{
    QSqlQuery query;
    QString cmd;
    cmd="update userInf set Port="+QString::number(userInf[NowUserID].Port)+
            " where name='"+userInf[NowUserID].userName+"'";
    query.exec(cmd);
}

void Management::on_pushButton_changename_clicked()
{
    bee.play();
    emit display(9);
    this->setFocus();
}

void Management::on_pushButton_changecode_clicked()
{
    bee.play();
    emit display(10);
    this->setFocus();
}
void Management::flashNow()
{
    //刷新个人信息
    ui->label_gametime->setText(QString::number(userInf[NowUserID].userExp)+"秒");
    ui->label_horsehave->setText(QString::number(userInf[NowUserID].totalHorse));
    if(userInf[NowUserID].rankTopE>5)
        ui->label_toprank->setText("从未上榜");
    else
        ui->label_toprank->setText(QString::number(userInf[NowUserID].rankTopE));
    ui->label_topscore->setText(QString::number(userInf[NowUserID].topE));
    ui->label_username->setText(userInf[NowUserID].userName);
    IsHard=false;
    QImage *img = new QImage(":/Management/src/EASY_50_30.png");
    ui->label_switchEH->setPixmap(QPixmap::fromImage(*img));
    img->load(":/Portraitlib/src/PORTRAIT"+QString::number(userInf[NowUserID].Port)+".png");
    ui->label_photo->setPixmap(QPixmap::fromImage(*img));
    delete img;
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "查看了个人中心...\n";
    logtemp.close();
    QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logs=userInf[NowUserID].userName+"查看了个人中心";
    Log indexLog(time,logs);
    indexLog.start();
    
}

//切换显示难度
void Management::on_pushButton_up_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        if(userInf[NowUserID].rankTopH>5)
            ui->label_toprank->setText("从未上榜");
        else
            ui->label_toprank->setText(QString::number(userInf[NowUserID].rankTopH));
        ui->label_topscore->setText(QString::number(userInf[NowUserID].topH));
        EH_img = new QImage(":/Management/src/HARD_50_30.png");
        ui->label_switchEH->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    else
    {
        if(userInf[NowUserID].rankTopE>5)
            ui->label_toprank->setText("从未上榜");
        else
            ui->label_toprank->setText(QString::number(userInf[NowUserID].rankTopE));
        ui->label_topscore->setText(QString::number(userInf[NowUserID].topE));
        ui->label_username->setText(userInf[NowUserID].userName);
        EH_img = new QImage(":/Management/src/EASY_50_30.png");
        ui->label_switchEH->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    this->setFocus();
}

void Management::on_pushButton_down_clicked()
{
    bee.play();
    QImage *EH_img;
    IsHard=!IsHard;
    if(IsHard)
    {
        if(userInf[NowUserID].rankTopH>5)
            ui->label_toprank->setText("从未上榜");
        else
            ui->label_toprank->setText(QString::number(userInf[NowUserID].rankTopH));
        ui->label_topscore->setText(QString::number(userInf[NowUserID].topH));
        EH_img = new QImage(":/Management/src/HARD_50_30.png");
        ui->label_switchEH->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    else
    {
        if(userInf[NowUserID].rankTopE>5)
            ui->label_toprank->setText("从未上榜");
        else
            ui->label_toprank->setText(QString::number(userInf[NowUserID].rankTopE));
        ui->label_topscore->setText(QString::number(userInf[NowUserID].topE));
        ui->label_username->setText(userInf[NowUserID].userName);
        EH_img = new QImage(":/Management/src/EASY_50_30.png");
        ui->label_switchEH->setPixmap(QPixmap::fromImage(*EH_img));
        delete EH_img;
    }
    this->setFocus();
}

void Management::on_pushButton_left_clicked()
{
    bee.play();
    QImage *img;
    QString PortPath;
    userInf[NowUserID].Port= userInf[NowUserID].Port-1;
    if( userInf[NowUserID].Port==-1)
        userInf[NowUserID].Port=PortNum-1;
    PortPath=":/Portraitlib/src/PORTRAIT"+QString::number(userInf[NowUserID].Port)+".png";
    img = new QImage(PortPath);
    ui->label_photo->setPixmap(QPixmap::fromImage(*img));
    delete img;
    this->setFocus();
}

void Management::on_pushButton_right_clicked()
{
    bee.play();
    QImage *img;
    QString PortPath;
    userInf[NowUserID].Port= userInf[NowUserID].Port+1;
    if( userInf[NowUserID].Port==PortNum)
        userInf[NowUserID].Port=0;
    PortPath=":/Portraitlib/src/PORTRAIT"+QString::number(userInf[NowUserID].Port)+".png";
    img = new QImage(PortPath);
    ui->label_photo->setPixmap(QPixmap::fromImage(*img));
    delete img;
    this->setFocus();
}
