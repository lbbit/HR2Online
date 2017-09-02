#include "mainwidget.h"
#include <QApplication>
#include"globalvariable.h"
#include <QTextCodec>
#include <QFileInfo>
#include<QtSql>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //解决库路径问题============info@seatrix.com

    QTextCodec *xcodec = QTextCodec::codecForLocale() ;

    QString exeDir = xcodec->toUnicode( QByteArray(argv[0]) ) ;

    QString BKE_CURRENT_DIR = QFileInfo(exeDir).path() ;

    QStringList  libpath;

    libpath << BKE_CURRENT_DIR+QString::fromLocal8Bit("/plugins/platforms");

    libpath << BKE_CURRENT_DIR <<BKE_CURRENT_DIR+QString::fromLocal8Bit("/plugins/imageformats");

    libpath << BKE_CURRENT_DIR+QString::fromLocal8Bit("/plugins");

    libpath << QApplication::libraryPaths();

    QApplication::setLibraryPaths(libpath) ;

    //=========================
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //设置相应的数据库和账号密码
    db.setHostName("");
    db.setDatabaseName("HR2");  //选择数据库
    db.setUserName("");
    db.setPassword("");
    if(!db.open())
    {
        qDebug()<<db.lastError().text();
        return 1;
    }


    //qDebug()<<"befor mainwidget!"<<endl;
    MainWidget w;
    w.show();
    return a.exec();
}
/*在线版相对于单机版的改动：
 * 开始游戏时读取数据库用户信息
 * 注册时同步数据库
 * 查看排行榜是先从服务器数据库读取数据再显示
 * 游戏过程中对手马儿前进的每一步变为最远距离的平均值，不再使用时间块
 * 游戏结束之后对用户信息的变化与服务器进行同步，并且刷新排行榜
 * 个人中心修改用户名、密码、头像同步数据
 * 游戏日志保存于数据库
 * （公告功能）
  */
