#include "changename.h"
#include "ui_changename.h"
#include"globalvariable.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include"log.h"
ChangeName::ChangeName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeName)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG9.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    connect(ui->lineEdit_newname,&QLineEdit::textChanged,this,&ChangeName::resetNameChecked);
    //每当用户名被编辑时就将nameChecked置为false

    ui->lineEdit_newname->setStyleSheet("background-color:transparent");
    ui->lineEdit_confirmname->setStyleSheet("background-color:transparent");
    nameChecked=false;
}

ChangeName::~ChangeName()
{
    delete ui;
}

void ChangeName::on_pushButton_return_clicked()
{
    bee.play();
    emit display(7);
    this->setFocus();
}

void ChangeName::on_pushButton_checkname_clicked()
{
    bee.play();
    int i;
    for(i=0;i<UserNum;i++)
    {
        if(ui->lineEdit_newname->text()==userInf[i].userName||ui->lineEdit_newname->text()==NULL)
            break;
    }
    if(i<UserNum)
    {
        if(ui->lineEdit_newname->text()==NULL)
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
}

void ChangeName::on_pushButton_changename_clicked()
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
        if(ui->lineEdit_confirmname->text()!=ui->lineEdit_newname->text())
        {
            QMessageBox::information(this,
                                     tr("警告"),
                                     tr("请确认两次输入的用户名相同!"));
        }
        else
        {
            originalName=userInf[NowUserID].userName;
            userInf[NowUserID].userName=ui->lineEdit_newname->text();
            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("用户名修改成功!"));
            //将修改的数据存入文件，防止游戏意外退出
            /*QFile fuserInf_update("userInf.dat");
            fuserInf_update.open(QIODevice::WriteOnly);
            QDataStream in_fuserInf_update(&fuserInf_update);
            for(int i=0;i<UserNum;i++)
                in_fuserInf_update<<userInf[i];
            fuserInf_update.close();*/

            updateName();

            //输出日志
            QFile logtemp("HR_log.txt");
            logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream out_log(&logtemp);
            out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
                     "修改了用户名..."<<qSetFieldWidth(1)<<'\n';
            logtemp.close();
            QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString logs=userInf[NowUserID].userName+"修改了用户名";
            Log indexLog(time,logs);
            indexLog.start();
        }
    }
}
void ChangeName::updateName()
{
    QSqlQuery query;
    QString cmd;
    cmd="update userInf set name="+userInf[NowUserID].userName+
            " where name='"+originalName+"'";
    query.exec(cmd);
}
void ChangeName::resetNameChecked()
{
    nameChecked=false;
}
void ChangeName::flashNow()
{
    ui->lineEdit_newname->setText(NULL);
    ui->lineEdit_confirmname->setText(NULL);
}
