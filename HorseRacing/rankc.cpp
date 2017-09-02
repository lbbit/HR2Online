#include "rankc.h"
#include<QDataStream>
RankC::RankC()
{
    UserName = "---";
    Score = 0;


}
QDataStream & operator <<(QDataStream & stream,const RankC &rankc)
{
    stream<<rankc.UserName<<rankc.Score;
    return stream;
}
QDataStream & operator >>(QDataStream & stream,RankC &rankc)
{
    stream>>rankc.UserName>>rankc.Score;
    return stream;
}
