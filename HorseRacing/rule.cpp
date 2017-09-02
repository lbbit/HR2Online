#include "rule.h"
#include "ui_rule.h"
#include"globalvariable.h"

Rule::Rule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rule)
{
    this->setFocus();
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPixmap bgImages(":/BG/src/BG6.png");
    QPalette this_palette = this->palette();
    this_palette.setBrush(QPalette::Window,QBrush(bgImages));
    this->setPalette(this_palette);
}

Rule::~Rule()
{
    delete ui;
}

void Rule::on_pushButton_return_clicked()
{
    bee.play();
    emit display(3);
    this->setFocus();
}
