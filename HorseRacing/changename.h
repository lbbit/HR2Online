#ifndef CHANGENAME_H
#define CHANGENAME_H

#include <QWidget>

namespace Ui {
class ChangeName;
}

class ChangeName : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeName(QWidget *parent = 0);
    bool nameChecked; //记录是否检测过用户名可用
    ~ChangeName();
signals:
    void display(int number);
public slots:
    void flashNow();
private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_checkname_clicked();

    void on_pushButton_changename_clicked();

    void resetNameChecked();

private:
    void updateName();  //将修改的名字与数据库同步
    QString originalName;
    Ui::ChangeName *ui;
};

#endif // CHANGENAME_H
