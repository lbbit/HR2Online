#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
public slots:
    void reset_nameChecked();   //在用户名编辑框被编辑时就就nameChecked设置为false
public slots:
    void flaseNow();
signals:
    void display(int number);
private slots:
    void on_pushButton_return_clicked();

 //  void on_lineEdit_account_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_register_clicked();

    void on_pushButton_checkname_clicked();

private:
    void updateUser();
    Ui::Register *ui;
    bool nameChecked;       //记录用户是否检测过用户名是否可用
};

#endif // REGISTER_H
