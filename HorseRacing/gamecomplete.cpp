#include "gamecomplete.h"
#include "ui_gamecomplete.h"

Gamecomplete::Gamecomplete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gamecomplete)
{
    ui->setupUi(this);
}

Gamecomplete::~Gamecomplete()
{
    delete ui;
}

void Gamecomplete::on_pushButton_return_clicked()
{
    emit display(4);
    this->setFocus();
}
