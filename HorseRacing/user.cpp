#include "user.h"

User::User()
{
    userName = "---";
    userCode =  "***";
    userExp = 0;
    horseExp = 0;
    topE = 0;
    topH = 0;
    rankTopE = 6;
    rankTopH = 6;
    hasHorse[0]=true;
    hasHorse[1]=true;
    hasHorse[2]=true;
    horseKey[0] = 0;
    horseKey[1]=1;
    horseKey[2]=2;
    totalHorse = 3;
    Port =0;
    TopHorseE = 0;
    TopHorseH = 0;
}

QDataStream & operator <<(QDataStream & stream,const User &user)
{
    stream<<user.userName<<user.userCode<<user.userExp<<user.horseExp<<user.topE
         <<user.topH;
    for(int i=0;i<20;i++)
        stream<<user.TBE[i].mx<<user.TBE[i].tx<<user.TBH[i].mx<<user.TBH[i].tx;
    stream<<user.rankTopE<<user.rankTopH;
    for(int i;i<20;i++)
        stream<<user.hasHorse[i]<<user.horseKey[i];
    stream<<user.totalHorse;
    stream<<user.Port;
    stream<<user.TopHorseE<<user.TopHorseH;
    return stream;
}
QDataStream & operator>>(QDataStream &stream,User &user)
{
    stream>>user.userName;
    stream>>user.userCode;
    stream>>user.userExp;
    stream>>user.horseExp;
    stream>>user.topE;
    stream>>user.topH;
    for(int i=0;i<20;i++)
    {
        stream>>user.TBE[i].mx;
        stream>>user.TBE[i].tx;
        stream>>user.TBH[i].mx;
        stream>>user.TBH[i].tx;
    }
    stream>>user.rankTopE;
    stream>>user.rankTopH;
    for(int i;i<20;i++)
    {
        stream>>user.hasHorse[i];
        stream>>user.horseKey[i];
    }
    stream>>user.totalHorse;
    stream>>user.Port;
    stream>>user.TopHorseE>>user.TopHorseH;
    return stream;
}
User& User::operator =(const User &u1)
{
    this->userName=u1.userName;
    this->userCode=u1.userCode;
    this->userExp=u1.userExp;
    this->horseExp=u1.horseExp;
    this->topE=u1.topE;
    this->topH=u1.topH;
    this->rankTopE=u1.rankTopE;
    this->rankTopH=u1.rankTopH;
    this->totalHorse=u1.totalHorse;
    for(int i=0;i<20;i++)
    {
        this->TBE[i].mx=u1.TBE[i].mx;
        this->TBE[i].tx=u1.TBE[i].tx;
        this->TBH[i].mx=u1.TBH[i].mx;
        this->TBH[i].tx=u1.TBH[i].tx;
    }
    for(int i=0;i<20;i++)
    {
        this->hasHorse[i]=u1.hasHorse[i];
        this->horseKey[i]=u1.horseKey[i];
    }
    return *this;
}
