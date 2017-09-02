#include "menu.h"
#include "ui_menu.h"
#include"globalvariable.h"

#include <QFile>
#include <QDataStream>
#include<QTextStream>
#include"log.h"
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{

    qs = new Quitswitch;
    qs->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口
    qs->setFixedSize(400,150);                  //Dialog固定大小

        qs->setAutoFillBackground(true);        //设置QS的背景图
        QPixmap qsbg(":/BG/src/BG20.png");
        QPalette qs_palette = qs->palette();
        qs_palette.setBrush(QPalette::Window,QBrush(qsbg));
        qs->setPalette(qs_palette);

    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG3.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    this->setFocus();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_quit_clicked()
{
    bee.play();
    qs->show();
    this->setFocus();
}

void Menu::on_pushButton_management_clicked()
{
    bee.play();
    emit display(7);
    this->setFocus();
}

void Menu::on_pushButton_rank_clicked()
{
    bee.play();
    emit display(5);
    this->setFocus();
}

void Menu::on_pushButton_rule_clicked()
{
    bee.play();
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+userInf[NowUserID].userName+
             "查看了规则...\n";
    logtemp.close();
    QString time=dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logs=userInf[NowUserID].userName+"查看了规则";
    Log indexLog(time,logs);
    indexLog.start();
    emit display(6);
    this->setFocus();
}

void Menu::on_pushButtong_game_clicked()
{
    bee.play();
    emit display(4);
    this->setFocus();
}

void Menu::on_pushButton_adminset_clicked()
{
    bee.play();
    if(NowUserID==0)
        emit display(12);
    this->setFocus();
}
