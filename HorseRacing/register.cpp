#include "register.h"
#include "ui_register.h"
#include"globalvariable.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QDebug>
#include"log.h"
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG2.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);

    ui->lineEdit_useraccount->setStyleSheet("background-color:transparent");
    ui->lineEdit_code->setStyleSheet("background-color:transparent");
    ui->lineEdit_codeconfirm->setStyleSheet("background-color:transparent");
    connect(ui->lineEdit_useraccount,&QLineEdit::textChanged,this,&Register::reset_nameChecked);
    QWidget::setTabOrder(ui->lineEdit_useraccount, ui->lineEdit_code);
    QWidget::setTabOrder(ui->lineEdit_code,ui->lineEdit_codeconfirm);
    QWidget::setTabOrder(ui->lineEdit_codeconfirm,ui->pushButton_register);
}

Register::~Register()
{
    delete ui;
}

void Register::reset_nameChecked()
{
    nameChecked=false;
}

void Register::on_pushButton_return_clicked()
{
    bee.play();
    emit display(1);
}

void Register::on_pushButton_register_clicked()
{
    bee.play();
    if(nameChecked==false)
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("请点击检测按钮并确认用户名可用!"));
    }
    else
    {
        if(ui->lineEdit_codeconfirm->text()==ui->lineEdit_code->text()&&ui->lineEdit_code->text()!=NULL)
        {
            QMessageBox::information(this,
                                     tr("通过"),
                                     tr("注册成功,请返回登录!"));
            reset_nameChecked();
            emit display(1);
            userInf[UserNum].userName=ui->lineEdit_useraccount->text();
            userInf[UserNum].userCode=ui->lineEdit_code->text();

            userInf[UserNum].hasHorse[0]=true;
            userInf[UserNum].hasHorse[1]=true;
            userInf[UserNum].hasHorse[2]=true;
            for(int i=3;i<20;i++)
            {
                userInf[UserNum].hasHorse[i]=false;
                userInf[UserNum].horseKey[i]=0;
            }
            userInf[UserNum].horseExp=0;
            userInf[UserNum].horseKey[0]=0;
            userInf[UserNum].horseKey[1]=1;
            userInf[UserNum].horseKey[2]=2;
            userInf[UserNum].rankTopE=6;
            userInf[UserNum].rankTopH=6;
            userInf[UserNum].topE=0;
            userInf[UserNum].topH=0;
            userInf[UserNum].totalHorse=3;
            userInf[UserNum].userExp=0;
            /*for(int i=0;i<20;i++)
            {
                userInf[UserNum].TBE[i].mx=0;
                userInf[UserNum].TBE[i].tx=0;
                userInf[UserNum].TBH[i].mx=0;
                userInf[UserNum].TBH[i].tx=0;
            }*///在线版不使用时间块记录玩家游戏情况
            userInf[UserNum].Port=0;
            userInf[UserNum].TopHorseE=0;
            userInf[UserNum].TopHorseH=0;

            UserNum++;

            //将增加的用户数据写到文件中防止游戏意外退出
            /*
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
            */

            //将新增用户信息添加到数据库
            updateUser();


            //输出日志
            QFile logtemp("HR_log.txt");
            logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream out_log(&logtemp);
            out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"："+ui->lineEdit_useraccount->text()+
                     "注册成功...\n";
            logtemp.close();
            QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString logs=ui->lineEdit_useraccount->text()+"注册成功";
            Log indexLog(time,logs);
            indexLog.start();
        }
        else
        {
            QMessageBox::information(this,
                                     tr("警告"),
                                     tr("请确认两次输入的密码相同且不为空!"));
        }
    }
    this->setFocus();
}

void Register::updateUser()
{
    QSqlQuery query;
    QString cmd;
    cmd="insert into userInf values('"+userInf[UserNum-1].userName+"','"+userInf[UserNum-1].userCode+"',0,0,0,0,6,6,3,0,0,0)";
    query.exec(cmd);
    cmd="insert into hasHorse values('"+userInf[UserNum-1].userName+"',1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)";
    query.exec(cmd);
    cmd="insert into horsekey values('"+userInf[UserNum-1].userName+"',0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)";
    query.exec(cmd);
}

void Register::on_pushButton_checkname_clicked()
{
    bee.play();
    int i;
    for(i=0;i<UserNum;i++)
    {
        if(ui->lineEdit_useraccount->text()==userInf[i].userName||ui->lineEdit_useraccount->text()==NULL)
            break;
    }
    if(i<UserNum)
    {
        if(ui->lineEdit_useraccount->text()==NULL)
            QMessageBox::information(this,
                                     tr("检测失败"),
                                     tr("用户名不能为空!"));
        else
            QMessageBox::information(this,
                                     tr("检测失败"),
                                     tr("用户名已存在!"));
    }
    else
    {
        QMessageBox::information(this,
                                 tr("通过"),
                                 tr("用户名可用!"));
        nameChecked=true;
    }
    this->setFocus();
}
void Register::flaseNow()
{
    this->setFocus();
    reset_nameChecked();
    ui->lineEdit_code->setText(NULL);
    ui->lineEdit_codeconfirm->setText(NULL);
    ui->lineEdit_useraccount->setText(NULL);
}
