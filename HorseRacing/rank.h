#ifndef RANK_H
#define RANK_H

#include <QWidget>

namespace Ui {
class Rank;
}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = 0);
    bool IsHard;    //当前是否显示困难模式的排行
    ~Rank();

signals:
    void display(int number);
public slots:
    void flashNow();
private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_last_clicked();

    void on_pushButton_next_clicked();

private:
    void getRank();
    Ui::Rank *ui;
};

#endif // RANK_H
