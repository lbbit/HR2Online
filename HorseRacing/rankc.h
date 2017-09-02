#ifndef RANKC_H
#define RANKC_H
#include<QDataStream>

//记录排行榜信息的类
class RankC
{
public:
    QString UserName;   //上排行榜玩家的名字
    int Score;          //得分
    RankC();
public:
    friend QDataStream & operator <<(QDataStream & stream,const RankC &rankc);
    friend QDataStream & operator >>(QDataStream & stream,RankC &rankc);
};

#endif // RANKC_H
