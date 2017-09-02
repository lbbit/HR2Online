#include "login.h"
#include "ui_login.h"
#include"globalvariable.h"
#include<QMessageBox>
#include<QFile>
#include<QDataStream>
#include<QTextStream>
#include"log.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG1.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    ui->lineEdit_account->setStyleSheet("background-color:transparent");    //账号输入框透明
    ui->lineEdit_code->setStyleSheet("background-color:transparent");       //密码输入框透明
    ui->pushButton_login->setFocus();
    ui->pushButton_login->setShortcut( QKeySequence::InsertParagraphSeparator );  //设置快捷键为键盘的“回车”键
    ui->pushButton_login->setShortcut(Qt::Key_Enter);  //设置快捷键为enter键
    ui->pushButton_login->setShortcut(Qt::Key_Return); //设置快捷键为小键盘上的enter键
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    bee.play();
    int i;
    for(i=0;i<UserNum;i++)
    {
        if(ui->lineEdit_account->text()==userInf[i].userName)
            break;
    }
    if(i<UserNum)
    {
        if(ui->lineEdit_code->text()==userInf[i].userCode)
        {
            NowUserID=i;
           /* if(i==0)
                emit display(12);
            else*/  //取消管理员界面
                emit display(3);
            //输出日志
            QFile logtemp("HR_log.txt");
            logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
            QTextStream out_log(&logtemp);
            out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
                     "成功登录游戏...\n";
            logtemp.close();
            QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString logs=userInf[NowUserID].userName+"成功登录游戏";
            Log indexLog(time,logs);
            indexLog.setTandL(time,logs);
            indexLog.start();
        }
        else
        {
            QMessageBox::information(this,tr("登录失败"),tr("帐号密码错误!"));
        }
    }
    else
    {
        QMessageBox::information(this,tr("登录失败"),tr("帐号密码错误!"));
    }
    this->setFocus();
}
void Login::on_pushButton_register_clicked()
{
    bee.play();
    emit display(2);
    this->setFocus();
}

void Login::on_pushButton_return_clicked()
{
    bee.play();
    emit display(0);
    this->setFocus();
}
