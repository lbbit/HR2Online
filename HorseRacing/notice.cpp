#include "notice.h"
#include "ui_notice.h"
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>

Notice::Notice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notice)
{
    setFixedSize(500,300);
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/notice_BG.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint); //隐藏 ？ 按钮
    setWindowTitle("公告");
    ui->label->setWordWrap(true);
    getNotice();

}
void Notice::getNotice()
{
    QString notices;
    QSqlQuery query;
    QString cmd;
    cmd="select content from notice where number=1";
    query.exec(cmd);
    while(query.next())
    {
        notices=query.value(0).toString();
    }
    ui->label->setText(notices);
}
Notice::~Notice()
{
    delete ui;
}
