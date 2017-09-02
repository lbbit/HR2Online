#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include"quitswitch.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    Quitswitch *qs;

signals:
    void display(int number);
private slots:
    void on_pushButton_quit_clicked();

    void on_pushButton_management_clicked();

    void on_pushButton_rank_clicked();

    void on_pushButton_rule_clicked();

    void on_pushButtong_game_clicked();

    void on_pushButton_adminset_clicked();

private:
    Ui::Menu *ui;


};

#endif // MENU_H
