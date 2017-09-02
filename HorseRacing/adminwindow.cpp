#include "adminwindow.h"
#include "ui_adminwindow.h"
#include"globalvariable.h"
#include<QMessageBox>
#include<iostream>
#include<QFile>
#include<QDebug>
using namespace std;
Adminwindow::Adminwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Adminwindow)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG12.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    IDtoView=0;
}

Adminwindow::~Adminwindow()
{
    delete ui;
}

void Adminwindow::on_pushButton_return_clicked()
{
    emit display(1);
}
void Adminwindow::flashNow(int S)
{
    //qDebug()<<UserNum;
    if(S==12)
    {
        //qDebug()<<UserNum;
        ui->comboBox->clear();
        ui->comboBox->addItem("---");
        for(int i=1;i<UserNum;i++)
        {
            ui->comboBox->addItem(userInf[i].userName);
        }
        ui->label_username->setText("---");
        ui->label_usercode->setText("---");
        IDtoView=0;
    }
}

void Adminwindow::on_comboBox_currentIndexChanged(int index)
{
    if(index<=0)
    {
        ui->label_username->setText("---");
        ui->label_usercode->setText("---");
        IDtoView=0;
    }
    else
    {
        ui->label_username->setText(userInf[index].userName);
        ui->label_usercode->setText(userInf[index].userCode);
        IDtoView=index;
    }
}

void Adminwindow::on_pushButton_delete_clicked()
{
    switch( QMessageBox::warning(this, "warning","确认删除该用户吗？",
                                 QMessageBox::Yes | QMessageBox::Escape,
                                 QMessageBox::No | QMessageBox::Default ))
    {
    case QMessageBox::Yes:
        break;
    case QMessageBox::No:
        return;
    }
    if(IDtoView!=0)
    {
        if(IDtoView==UserNum-1)
        {

        }
        else
        {
            userInf[IDtoView]=userInf[UserNum-1];
        }
        userInf[UserNum-1].userName="---";
        userInf[UserNum-1].userCode="***";
        userInf[UserNum-1].hasHorse[0]=true;
        userInf[UserNum-1].hasHorse[1]=true;
        userInf[UserNum-1].hasHorse[2]=true;
        for(int i=3;i<20;i++)
        {
            userInf[UserNum-1].hasHorse[i]=false;
            userInf[UserNum-1].horseKey[i]=0;
        }
        userInf[UserNum-1].horseExp=0;
        userInf[UserNum-1].horseKey[0]=0;
        userInf[UserNum-1].horseKey[1]=1;
        userInf[UserNum-1].horseKey[2]=2;
        userInf[UserNum-1].rankTopE=6;
        userInf[UserNum-1].rankTopH=6;
        userInf[UserNum-1].topE=0;
        userInf[UserNum-1].topH=0;
        userInf[UserNum-1].totalHorse=3;
        userInf[UserNum-1].userExp=0;
        for(int i=0;i<20;i++)
        {
            userInf[UserNum-1].TBE[i].mx=0;
            userInf[UserNum-1].TBE[i].tx=0;
            userInf[UserNum-1].TBH[i].mx=0;
            userInf[UserNum-1].TBH[i].tx=0;
        }

        UserNum-=1;
        //将更新的用户数据写到文件中防止游戏意外退出
        QFile userNumtemp("userNum.dat");
        userNumtemp.open(QIODevice::WriteOnly);
        QDataStream in_userNumtemp(&userNumtemp);
        in_userNumtemp<<UserNum;
        userNumtemp.close();

        QFile fuserInf_update("userInf.dat");
        fuserInf_update.open(QIODevice::WriteOnly);
        QDataStream in_fuserInf_update(&fuserInf_update);
        for(int i=0;i<UserNum;i++)
            in_fuserInf_update<<userInf[i];
        fuserInf_update.close();
        flashNow(12);
    }
}
