#include "changecode.h"
#include "ui_changecode.h"
#include<QMessageBox>
#include"globalvariable.h"
#include<QFile>
#include<QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include"log.h"
ChangeCode::ChangeCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeCode)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG10.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    ui->lineEdit_originalcode->setStyleSheet("background-color:transparent");
    ui->lineEdit_newcode->setStyleSheet("background-color:transparent");
    ui->lineEdit_confirmcode->setStyleSheet("background-color:transparent");
}

ChangeCode::~ChangeCode()
{
    delete ui;
}

void ChangeCode::on_pushButton_return_clicked()
{
    bee.play();
    emit display(7);
    this->setFocus();
}

void ChangeCode::on_pushButton_changecode_clicked()
{
    bee.play();
    if(ui->lineEdit_originalcode->text()!=userInf[NowUserID].userCode)
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("原密码错误!"));
    }
    else
    {
        if(ui->lineEdit_confirmcode->text()!=ui->lineEdit_newcode->text()||ui->lineEdit_newcode->text()==NULL)
        {
            QMessageBox::information(this,
                                     tr("警告"),
                                     tr("请确认两次密码相同且不为空!"));
        }
        else if(ui->lineEdit_newcode->text()==ui->lineEdit_originalcode->text())
            {
                QMessageBox::information(this,
                                         tr("警告"),
                                         tr("新密码不能与原密码相同!"));
            }
            else
            {
                userInf[NowUserID].userCode=ui->lineEdit_newcode->text();
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("密码修改成功!"));
                /*QFile fuserInf_update("userInf.dat");
                fuserInf_update.open(QIODevice::WriteOnly);
                QDataStream in_fuserInf_update(&fuserInf_update);
                for(int i=0;i<UserNum;i++)
                    in_fuserInf_update<<userInf[i];
                fuserInf_update.close();*/
                //输出日志
                uploadCode();
                QFile logtemp("HR_log.txt");
                logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
                QTextStream out_log(&logtemp);
                out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
                         "修改了密码..."<<qSetFieldWidth(1)<<'\n';
                logtemp.close();
                QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString logs=userInf[NowUserID].userName+"修改了密码";
                Log indexLog(time,logs);
                indexLog.start();
            }
    }
}
void ChangeCode::uploadCode()
{
    QSqlQuery query;
    QString cmd;
    cmd="update userInf set code="+userInf[NowUserID].userCode+
            " where name='"+userInf[NowUserID].userName+"'";
    query.exec(cmd);

}
void ChangeCode::flashNow()
{
    ui->lineEdit_confirmcode->setText(NULL);
    ui->lineEdit_newcode->setText(NULL);
    ui->lineEdit_originalcode->setText(NULL);
    this->setFocus();
}
