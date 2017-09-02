#include "log.h"
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QDebug>
Log::Log(QString t,QString l)
{
    time=t;
    logs=l;
}
void Log::uploadlog()
{
    QSqlQuery query;
    QString cmd;
    cmd="insert into log values('"+time+"','"+logs+"')";
    query.exec(cmd);
    //qDebug()<<time<<logs;
}
void Log::setTandL(QString t,QString l)
{
    time=t;
    logs=l;
}
void Log::start()
{
    //uploadlog();
}
