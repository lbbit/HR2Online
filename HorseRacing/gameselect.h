#ifndef GAMESELECT_H
#define GAMESELECT_H

#include <QWidget>

namespace Ui {
class GameSelect;
}

class GameSelect : public QWidget
{
    Q_OBJECT

public:
    explicit GameSelect(QWidget *parent = 0);
    int rivalID;    //所选择的对手的ID
    bool IsHard;
    int thisHorse;
    ~GameSelect();

signals:
    void display(int number);
public slots:
    void flashNow();

private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_rival_last_clicked();

    void on_pushButton_rival_next_clicked();

    void on_pushButton_difficulty_last_clicked();

    void on_pushButton_difficulty_next_clicked();

    void on_pushButton_horse_last_clicked();

    void on_pushButton_horse_next_clicked();

    void on_pushButton_gamestart_clicked();

private:
    Ui::GameSelect *ui;
};

#endif // GAMESELECT_H
