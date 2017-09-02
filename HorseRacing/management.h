#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QWidget>

namespace Ui {
class Management;
}

class Management : public QWidget
{
    Q_OBJECT

public:
    explicit Management(QWidget *parent = 0);
    bool IsHard;        //表示当前显示的难度
    ~Management();
public slots:

    void flashNow();

signals:
    void display(int number);
private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_changename_clicked();

    void on_pushButton_changecode_clicked();


    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

private:
    void savePort();    //保存头像的更改
    Ui::Management *ui;
};

#endif // MANAGEMENT_H
