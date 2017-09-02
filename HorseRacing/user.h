#ifndef USER_H
#define USER_H
#include<QString>
#include"timeblock.h"
#include<QDataStream>

//记录用户信息的类
class User
{
public:
    QString userName;   //用户名
    QString userCode;   //密码
    int userExp;    //总局数
    int horseExp;    //总路程
    int topE;       //简单难度最高分
    int topH;       //困难难度最高分
    TimeBlock   TBE[20];    //简单难度下最高分的比赛记录
    TimeBlock   TBH[20];    //困难难度下最高分的比赛记录
    int rankTopE;           //简单难度下最高排名
    int rankTopH;           //困难难度下最高排名
    bool hasHorse[20];      //用户拥有的马
    int totalHorse;         //用有的总的马数目
    int horseKey[20];       //用户拥有的马的序列号
    int Port;               //用户当前使用的头像
    int TopHorseE;          //简单模式下最高分所使用的马儿
    int TopHorseH;          //困难模式下最高分所使用的马儿

    User();
public:
    friend QDataStream & operator <<(QDataStream & stream,const User &user);
    friend QDataStream & operator >>(QDataStream & stream,User &user);
    User & operator =(const User &u);
};

#endif // USER_H
