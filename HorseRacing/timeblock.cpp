#include "timeblock.h"

TimeBlock::TimeBlock()
{
    tx=0;
    mx=0;
}
QDataStream & operator <<(QDataStream & stream,const TimeBlock &timeblock)
{
    stream<<timeblock.tx<<timeblock.mx;
    return stream;
}
QDataStream & operator >>(QDataStream & stream,TimeBlock &timeblock)
{
    stream>>timeblock.tx>>timeblock.mx;
    return stream;
}
