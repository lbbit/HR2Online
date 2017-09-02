#include "mainwidget.h"
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QVBoxlayout>
#include<QHBoxLayout>
#include<QIcon>
#include <QPainter>
#include <QStackedLayout>

#include<QDebug>
#include<QDir>

#include"globalvariable.h"
#include<QFile>

#include<QDesktopWidget>
#include<QApplication>
#include"aboutdialog.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    /*QDir dir;
    qDebug()<<dir.currentPath()<<endl;*/
    setFixedSize(472,622);
    setWindowIcon(QIcon(":Logo/src/LOGO_MAINWIDGET_PAINT.png")); //设置窗口图标
    setWindowTitle("赛马2.0(在线版)");

    //作为主界面，用来放置layout_main,可以解决
    //QLayout: Attempting to add QLayout "" to MainWindow "", which already has a layout
    //的问题

    //实现所有界面对象
    window_start = new Start;           //0
    window_login = new Login;           //1
    window_register = new Register;     //2
    window_menu = new Menu;             //3
    window_gameselect = new GameSelect; //4
    window_rank = new Rank;             //5
    window_rule = new Rule;             //6
    window_management = new Management; //7
    window_gamestart = new GameStart;   //8
    window_changename = new ChangeName; //9
    window_changecode = new ChangeCode; //10
    window_gamecomplete = new Gamecomplete; //11
    window_adminwindow = new Adminwindow;   //12

    //将所有的界面放到布局栈中用于切换
    stackLayout = new QStackedLayout;

    stackLayout->addWidget(window_start);
    stackLayout->addWidget(window_login);
    stackLayout->addWidget(window_register);
    stackLayout->addWidget(window_menu);
    stackLayout->addWidget(window_gameselect);
    stackLayout->addWidget(window_rank);
    stackLayout->addWidget(window_rule);
    stackLayout->addWidget(window_management);
    stackLayout->addWidget(window_gamestart);
    stackLayout->addWidget(window_changename);
    stackLayout->addWidget(window_changecode);
    stackLayout->addWidget(window_gamecomplete);
    stackLayout->addWidget(window_adminwindow);

    //关联切换界面的信号和槽，以及切换背景
    connect(window_start,&Start::display,stackLayout,&QStackedLayout::setCurrentIndex);   //切换页面
    connect(window_login,&Login::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_register,&Register::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_menu,&Menu::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_gameselect,&GameSelect::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_rank,&Rank::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_rule,&Rule::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_management,&Management::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_gamestart,&GameStart::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_changename,&ChangeName::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_changecode,&ChangeCode::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_menu->qs,&Quitswitch::display,stackLayout,&QStackedLayout::setCurrentIndex);    
    connect(window_gamestart->gstop,&Gamestop::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_gamestart->gstop,&Gamestop::continueGame,window_gamestart,&GameStart::on_pushButton_StartandStop_clicked);//关联继续游戏按钮
    connect(window_gamecomplete,&Gamecomplete::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_adminwindow,&Adminwindow::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(window_gamestart->gover,&GameOver::display,stackLayout,&QStackedLayout::setCurrentIndex);

    //切换到游戏界面和之外的菜单界面，发生尺寸改变相关的事件
    connect(window_gamestart->gstop,&Gamestop::display,this,&MainWidget::resetSize);
    connect(window_gameselect,&GameSelect::display,this,&MainWidget::resetSize);
    connect(window_gamecomplete,&Gamecomplete::display,this,&MainWidget::resetSize);
    connect(window_gamestart->gover,&GameOver::display,this,&MainWidget::resetSize);

    //关联进入某个界面，发生的事件
    connect(window_menu,&Menu::display,window_rank,&Rank::flashNow);//menu发出的信号给到Rank中的flashNow()函数
                                                                    //用于刷新Rank榜中的数据
    //在现实某些界面之前需要刷新界面
    connect(window_menu,&Menu::display,window_management,&Management::flashNow);
    connect(window_changename,&ChangeName::display,window_management,&Management::flashNow);
    connect(window_changecode,&ChangeCode::display,window_management,&Management::flashNow);
    connect(window_management,&Management::display,window_changename,&ChangeName::flashNow);
    connect(window_management,&Management::display,window_changecode,&ChangeCode::flashNow);
    connect(window_menu,&Menu::display,window_gameselect,&GameSelect::flashNow);
    connect(window_login,&Login::display,window_adminwindow,&Adminwindow::flashNow);
    connect(window_login,&Login::display,window_register,&Register::flaseNow);
    connect(window_gameselect,&GameSelect::display,window_gamestart,&GameStart::flashNow);
    //  将mainlayout加到mainwidget上去



    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);

    //添加关于菜单



    //初始化全局变量
    //输出日志
    QFile logtemp("HR_log.txt");
    logtemp.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream out_log(&logtemp);
    out_log<<dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"：  打开游戏...\n";
    logtemp.close();

    //先读取UserNum总数
/*    if(!QFile("userNum.dat").exists())
    {
        QFile userInftemp("userInf.dat");
        userInftemp.open(QIODevice::WriteOnly);
        userInftemp.close();

        QFile rankEtemp("rankE.dat");
        rankEtemp.open(QIODevice::WriteOnly);
        QDataStream out_rankEtemp(&rankEtemp);
        RankC temprank1;
        temprank1.UserName="---";
        temprank1.Score=0;
        for(int i=0;i<5;i++)            //给排行榜文件写入初始数据
            out_rankEtemp<<temprank1;
        rankEtemp.close();

        QFile rankHtemp("rankH.dat");
        rankHtemp.open(QIODevice::WriteOnly);
        QDataStream out_rankHtemp(&rankHtemp);
        RankC temprank2;
        temprank2.UserName="---";
        temprank2.Score=0;
        for(int i=0;i<5;i++)            //给排行榜文件写入初始数据
            out_rankHtemp<<temprank2;
        rankHtemp.close();

        QFile userNumtemp("userNum.dat");
        userNumtemp.open(QIODevice::WriteOnly);
        QDataStream out_userNumtemp(&userNumtemp);
        out_userNumtemp<<(int)1;
        userNumtemp.close();
    }
    QFile userNum("userNum.dat");
    userNum.open(QIODevice::ReadOnly);
    QDataStream in_userNm(&userNum);
    in_userNm>>UserNum;
    userNum.close();

    //从userInf.dat中读出UserNum个用户信息到userInf[100]数组中
    if(UserNum!=1)
    {
        QFile fuserInf("userInf.dat");
        fuserInf.open(QIODevice::ReadOnly);
        QDataStream in_userInf(&fuserInf);
        for(int i=0;i<UserNum;i++)
            in_userInf>>userInf[i];
    }
    //强制重置管理员的帐号和密码
    userInf[0].userName="admin";
    userInf[0].userCode="admin";
    userInf[0].totalHorse=20;   //管理员拥有所有的马
    for(int i=0;i<20;i++)
    {
        userInf[0].hasHorse[i]=true;
        userInf[0].horseKey[i]=i;
        userInf[0].TBE[i].mx=30;
        userInf[0].TBH[i].mx=30;
        userInf[0].TBE[i].tx=240;
        userInf[0].TBH[i].tx=240;
    }
    userInf[0].TopHorseE=0;
    userInf[0].TopHorseH=0;
    userInf[0].topE=4800;
    userInf[0].topH=4800;
    userInf[0].horseExp=100;
    userInf[0].userExp=300;
    //读取排行榜内容
    QFile frankE("rankE.dat");
    frankE.open(QIODevice::ReadOnly);
    QDataStream in_rankE(&frankE);
    for(int i=0;i<5;i++)
        in_rankE>>rankE[i];
    frankE.close();

    QFile frankH("rankH.dat");
    frankH.open(QIODevice::ReadOnly);
    QDataStream in_rankH(&frankH);
    for(int i=0;i<5;i++)
        in_rankH>>rankH[i];
    frankH.close();*/
}

void MainWidget::resetSize(int i)
{
    QDesktopWidget* pDw = QApplication::desktop();//获得桌面窗体
    QRect rect = pDw->screenGeometry();//获得分辨率
    if(i==8)
    {
        this->move(rect.width()/2-500,rect.height()/2-362); //设置窗口居中显示
        setFixedSize(1020,642);
    }
    if(i==4)
    {
        this->move(rect.width()/2-236,rect.height()/2-322);
        setFixedSize(472,622);
    }
}
MainWidget::~MainWidget()
{
    delete window_start;    //所以需要显示的窗口指针
    delete window_login;
    delete window_register;
    delete window_menu;
    delete window_gameselect;
    delete window_rank;
    delete window_rule;
    delete window_management;
    delete window_gamestart;
    delete window_changename;
    delete window_changecode;
    delete window_gamecomplete;
    delete window_adminwindow;

    delete stackLayout;
    delete mainLayout;
}

