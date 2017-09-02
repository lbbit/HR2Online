#ifndef GLOBALVARIABLE
#define GLOBALVARIABLE
#include"user.h"
#include"rankc.h"
#include"timeblock.h"
#include<QDateTime>
#include<QSound>

extern int NowUserID;   //当前登录用户的ID
extern RankC rankE[5];  //简单模式排行榜
extern RankC rankH[5];  //困哪模式排行榜
extern User userInf[100];   //所有用户的信息
extern int UserNum;     //注册过的用户数目
extern int horseLibNum;     //当前版本马儿的种类
extern int PortNum;         //当前版本头像的种类
extern int gaming_rival;    //游戏过程中的对手，用来从gameselect界面将数据转移到游戏界面
extern bool gaming_IsHard;   //游戏过程中的难度
extern int gaming_horse;        //游戏过程中用的马
extern QDateTime  dateTime;      //记录当前时间
extern QSound bee;
#endif // GLOBALVARIABLE

