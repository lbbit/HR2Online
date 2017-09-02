#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include<QImage>
#include<QPixmap>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle("关于HorseRacing");
    QImage *img = new QImage(":/About/src/LOGO_about.png");
    ui->label_logo->setPixmap(QPixmap::fromImage(*img));
    delete img;
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
