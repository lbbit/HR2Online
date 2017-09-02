#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "gamestart.h"
#include "globalvariable.h"

namespace Ui {
class GameOver;
}
class GameStart;
class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = 0);
    ~GameOver();
    void SetResult(GameStart *GS);  //初始化结算页面
    void flash();

private slots:
    void on_pushButton_clicked();
signals:
    void display(int number);

private:
    QString myhorsepath;
    QString rivalhorsepath;
    QString newhorsepath;
    Ui::GameOver *ui;
    bool isnewS;        //是否新纪录
    int myScore_o;      //玩家得分
    int rivalScore_o;     //对手得分
    bool defeat_o;          //是否击败对手
    bool inrank_o;          //是否进入排行
    int getNewHorse_o;    //抽奖情况 初始为-1表示没抽到 0-18表示抽到的马 19表示刚集齐所有的马 20表示游戏前已经集齐
};

#endif // GAMEOVER_H
