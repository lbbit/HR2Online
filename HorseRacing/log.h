#ifndef LOG_H
#define LOG_H
#include<QString>
#include<QThread>
class Log
{
private:
    QString time;
    QString logs;
public:
    Log(QString t,QString l);
    void setTandL(QString t,QString l);
    void uploadlog();//上传日志到数据库
    void start();
};

#endif // LOG_H
