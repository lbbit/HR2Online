#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
signals:
    void display(int number);
public slots:

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
