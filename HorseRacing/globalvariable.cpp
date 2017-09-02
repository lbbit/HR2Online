#include"user.h"
#include"rankc.h"
#include"timeblock.h"
#include<QDateTime>
#include<QSound>

int NowUserID=-1;   //当前登录用户的ID
RankC rankE[5];  //简单模式排行榜
RankC rankH[5];  //困哪模式排行榜
User userInf[100];   //所有用户的信息
int UserNum=0;     //注册过的用户数目
//int TotalHorse=20;
int horseLibNum=20; //当前游戏版本中马的种类
int PortNum=10;     //当前游戏版本中头像的种类
int gaming_rival=0;    //游戏过程中的对手，用来从gameselect界面将数据转移到游戏界面
bool gaming_IsHard=false;   //游戏过程中的难度
int gaming_horse=0;        //游戏过程中用的马
QDateTime  dateTime =  QDateTime ::currentDateTime();
QSound bee(":/start/src/5473.wav");
