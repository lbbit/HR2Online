#ifndef TIMEBLOCK_H
#define TIMEBLOCK_H
#include<QDataStream>
//用来记录比赛过程的时间块类
class TimeBlock
{
public:
    int tx;     //按完一组键积分
    int mx;     //马儿相应跑动的距离
    TimeBlock();
public:
    friend QDataStream & operator <<(QDataStream & stream,const TimeBlock &timeblock);
    friend QDataStream & operator >>(QDataStream & stream,TimeBlock &timeblock);
};

#endif // TIMEBLOCK_H
