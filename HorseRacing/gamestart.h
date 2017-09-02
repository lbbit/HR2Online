#ifndef GAMESTART_H
#define GAMESTART_H

#include <QWidget>
#include "gamestop.h"
#include "timeblock.h"
#include "globalvariable.h"
#include <QTimer>
#include <QLabel>
#include "gameover.h"
namespace Ui {
class GameStart;
}
class GameOver;
class GameStart : public QWidget
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = 0);
    ~GameStart();
    Gamestop *gstop;    //暂停界面
    GameOver *gover;    //结束界面
    void keyPressEvent(QKeyEvent *);    //响应用户的按键
    friend GameOver;    //结算页面类作为友元类，得以访问游戏结果
private:
    void getRank();     //同步排行榜
    void uploadRank();  //上传排行榜
    void uploadNowUser();   //将当前玩家记录更新到数据库
    void setLabelPic(QLabel *label,QString PicPath);    //为一个按键标签贴图
    QString getEasyPicPath(int);      //得到一个方向图片的地址
    QString getEcorrectPath(int);     //得到简单模式下按键正确图片地址
    QString getEwrongPath(int);       //得到简单模式下按键错误图片地址
    QString getHardPicPath(int);      //得到一个字母图片地址
    QString getHcorrectPath(int);     //得到困难模式下按键正确图片地址
    QString getHwrongPath(int);       //得到困难模式下按键错误图片地址
    void flashEasyLabel();            //刷新简单难度下的图片
    void flashHardLabel();            //刷新困难模式下的图片
    void HDealPress(QKeyEvent *event);//困难模式下处理按键
    void EDealPress(QKeyEvent *event);//简单模式下处理按键
    void DealData();                   //处理按完一组键之后积分过程
    int fixIndexScore(int correctK,double CompleteT);  //计算一组按键得分
    void moveMyHorse(int x,int y);           //根据马的横坐标移动马
    void moveRivalHorse(int x,int y);        //移动对手的马
    void flashMyHorse();                //在移动的时候调用，刷新马的动作
    void flashRivalHorse();
    QString GetStandHorsePath(int index);   //获取初始马站着的图片路径
    QString GetRunHorsePath1(int index);    //获取马跑动的第一个动作的图片路径
    QString GetRunHorsePath2(int index);    //获取马跑动的第二个动作的图片路径
    void Conclude();        //游戏结算
    void refreshE();        //刷新简单排行榜
    void refreshH();        //刷新困难排行榜
    void OpenHorse();       //开马

signals:
    void display(int number);

private slots:
    void clockStartOut();   //开始倒计时结束调用
    void clockGameOut();    //游戏过程中每隔两秒调用
    void on_pushButton_music_clicked(); //开关音乐
public slots:
    void flashNow(int); //从选择界面进入这个界面时刷新和初始化当前界面和一些变量
    void on_pushButton_StartandStop_clicked();  //开始暂停
private:
    Ui::GameStart *ui;
    //游戏中需要使用的数据
    /*****
     *
     * int gaming_rival //对手ID
     * bool gameing_IsHard  //游戏难度
     * int gaming_horse     //游戏用的马
     *
     * ****/
    QSound *BGmusic0;    //背景音乐
    QSound *BGmusic1;
    QSound *BGmusic2;
    QSound *BGmusic3;
    QSound *BGmusic4;
    QSound *BGMs[5];
    int BGM;             //记录随机背景音乐
    int BG;             //记录随机背景
    bool withmusic;     //是否播放背景音乐
    bool horse1IsRun2;    //马1当前跑动的动作
    bool horse2IsRun2;
    bool defeat;    //是否击败对手
    bool inrank;    //是否进排行榜
    int getNewHorse;    //抽奖情况 初始为-1表示没抽到 0-18表示抽到的马 19表示刚集齐所有的马 20表示游戏前已经集齐
    bool isNewScore;//是否是玩家的新纪录
    int myHorseY;   //自己马儿的纵坐标
    int rivalHorseY;//对手马儿的纵坐标
    bool inGaming;  //是否正在游戏，控制暂停按钮
    bool duringGame;    //游戏是否已经开始，用来屏蔽键盘响应
    QTimer clockStart;  //开始游戏前的倒计时
    QTimer clockGame;   //游戏过程计时
    double labelleftValue;  //滑动条的时间
    int remainTime;     //游戏总的剩余时间，在左边lcd中显示
    int keyMod;     //按键是4种还是26种
    int myScore;    //玩家的得分
    int rivalScore; //对手当前的得分
    TimeBlock gamingTB[20]; //当前的比赛记录
    int indexScore; //当前这组按键的得分
    int indexMx;    //当前这组按键马儿跑得距离
    int countdown;  //玩家开始玩游戏之前的三秒倒计时
    int keyGroup;   //当前所按按键的组数（0~20）
    int keys[6];    //记录6个按键的值
    int inputKey;   //用户按下的按键
    int keyIndex;   //当前按键的比对序列号(1~6)
    int correctKeys;//当前组按键的正确个数
    double CompleteTime;    //按完一组按键用时
    int rivalHorseX;//对手马儿当前的横坐标
    int myHorseX;   //自己马儿当前的横坐标
    QLabel * sixLabels[6]; //记录6个按键标签的地址
    QString MyHorsePath0;   //玩家马初始状态的图片地址
    QString MyHorsePath1;   //玩家马动作一的图片地址
    QString MyHorsePath2;   //玩家马动作而得图片地址
    QString RivalHorsePath0;//意义同上
    QString RivalHorsePath1;
    QString RivalHorsePath2;


};

#endif // GAMESTART_H
