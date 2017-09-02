#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include"start.h"
#include"login.h"
#include"register.h"
#include"menu.h"
#include"gameselect.h"
#include"rank.h"
#include"rule.h"
#include"management.h"
#include"gamestart.h"
#include"quitswitch.h"
#include"gamestop.h"
#include"changecode.h"
#include"changename.h"
#include"gamecomplete.h"
#include"adminwindow.h"
#include<QStackedLayout>
#include"aboutdialog.h"
#include"notice.h"


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void resetSize(int i);
private:
    Start *window_start;    //所以需要显示的窗口指针
    Login *window_login;
    Register *window_register;
    Menu *window_menu;
    GameSelect *window_gameselect;
    Rank *window_rank;
    Rule *window_rule;
    Management *window_management;
    GameStart *window_gamestart;
    ChangeName *window_changename;
    ChangeCode *window_changecode;
    Gamecomplete *window_gamecomplete;
    Adminwindow *window_adminwindow;

    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;

};



#endif // MAINWINDOW_H
