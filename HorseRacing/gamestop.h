#ifndef GAMESTOP_H
#define GAMESTOP_H

#include <QDialog>

namespace Ui {
class Gamestop;
}

class Gamestop : public QDialog
{
    Q_OBJECT

public:
    explicit Gamestop(QWidget *parent = 0);
    ~Gamestop();

private slots:
    void on_pushButton_quittogameselect_clicked();

    void on_pushButton_continue_clicked();

signals:
    void display(int number);
    void continueGame();

private:
    Ui::Gamestop *ui;
};

#endif // GAMESTOP_H
