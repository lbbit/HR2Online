#ifndef QUITSWITCH_H
#define QUITSWITCH_H

#include <QDialog>

namespace Ui {
class Quitswitch;
}

class Quitswitch : public QDialog
{
    Q_OBJECT

public:
    explicit Quitswitch(QWidget *parent = 0);
    ~Quitswitch();
signals:
    void display(int number);

private slots:
    void on_pushButton_switchuser_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::Quitswitch *ui;
};

#endif // QUITSWITCH_H
