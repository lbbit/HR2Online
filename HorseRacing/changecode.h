#ifndef CHANGECODE_H
#define CHANGECODE_H

#include <QWidget>

namespace Ui {
class ChangeCode;
}

class ChangeCode : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeCode(QWidget *parent = 0);
    ~ChangeCode();
signals:
    void display(int number);
public slots:
    void flashNow();
private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_changecode_clicked();

private:
    void uploadCode();  //将修改的密码存入数据库
    Ui::ChangeCode *ui;
};

#endif // CHANGECODE_H
