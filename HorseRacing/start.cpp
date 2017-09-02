#include "start.h"
#include "ui_start.h"
#include <QFile>
#include <QDataStream>
#include "globalvariable.h"
#include <QTextStream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QMessageBox>
#include<QDebug>

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG0.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    ui->pushButton_start->setFocus();
    ui->pushButton_start->setShortcut( QKeySequence::InsertParagraphSeparator );  //设置快捷键为键盘的“回车”键
    ui->pushButton_start->setShortcut(Qt::Key_Enter);  //设置快捷键为enter键
    ui->pushButton_start->setShortcut(Qt::Key_Return); //设置快捷键为小键盘上的enter键
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_start_clicked()
{
    bee.play();
    emit resetBG(1);
    emit display(1);
    loadAll();
    anotice.show();
}


void Start::on_pushButton_exit_clicked()
{
    bee.play();
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"： "+
             "退出游戏...\n";
    logtemp.close();
    exit(0);
}

void Start::on_pushButton_left_clicked()
{
    bee.play();
}

void Start::on_pushButton_clicked()
{
    bee.play();
    ad.show();
}
//连接服务器初始化所有用户信息
void Start::loadAll()
{
    QSqlQuery query,queryhh,queryhk;//分别读取userInf hasHorse horseKey三张表
    QString cmd,cmd1,cmd2;
    cmd="select * from userInf";
    cmd1="select * from hasHorse";
    cmd2="select *from horsekey";
    query.exec(cmd);
    queryhh.exec(cmd1);
    queryhk.exec(cmd2);
    UserNum=query.size();   //记下用户信息总行数
    qDebug()<<UserNum;
    //获取所有用户信息
    int index=0;
    while(query.next())
    {
        queryhh.next();
        queryhk.next();
        userInf[index].userName = query.value(0).toString();
        userInf[index].userCode = query.value(1).toString();
        userInf[index].userExp=query.value(2).toInt();
        userInf[index].horseExp=query.value(3).toInt();
        userInf[index].topE=query.value(4).toInt();
        userInf[index].topH=query.value(5).toInt();
        userInf[index].rankTopE=query.value(6).toInt();
        userInf[index].rankTopH=query.value(7).toInt();
        userInf[index].totalHorse=query.value(8).toInt();
        userInf[index].Port=query.value(9).toInt();
        userInf[index].TopHorseE=query.value(10).toInt();
        userInf[index].TopHorseH=query.value(11).toInt();
        for(int j=0;j<20;j++)
        {
            userInf[index].hasHorse[j]=queryhh.value(j+1).toBool();
            userInf[index].horseKey[j]=queryhk.value(j+1).toInt();
        }
        index++;
    }
    qDebug()<<userInf[0].userName<<userInf[0].totalHorse;
}
