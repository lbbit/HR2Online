#include "quitswitch.h"
#include "ui_quitswitch.h"
#include <QFile>
#include <QDataStream>
#include "globalvariable.h"
#include<QTextStream>

Quitswitch::Quitswitch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Quitswitch)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint); //隐藏 ？ 按钮
    setWindowTitle("                                切换用户 or 退出");
}

Quitswitch::~Quitswitch()
{
    delete ui;
}

void Quitswitch::on_pushButton_switchuser_clicked()
{
    bee.play();

    emit display(1);
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "选择切换用户...\n";
    logtemp.close();
    close();            //关闭当前的对话框
}

void Quitswitch::on_pushButton_quit_clicked()
{
    bee.play();
    exit(0);
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "选择退出游戏...";
    logtemp.close();
}
