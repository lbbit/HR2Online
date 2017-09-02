#include "gamestop.h"
#include "ui_gamestop.h"

Gamestop::Gamestop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gamestop)
{
    this->setFocus();
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    //setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint); //隐藏 ？ 按钮
    //setWindowTitle("                                暂停");
    ui->pushButton_continue->setFocus();
    ui->pushButton_continue->setShortcut(Qt::Key_Space);
}

Gamestop::~Gamestop()
{
    delete ui;
}

void Gamestop::on_pushButton_quittogameselect_clicked()
{
    emit display(4);
    close();
}

void Gamestop::on_pushButton_continue_clicked()
{
    continueGame();
    close();
}
