#ifndef START_H
#define START_H

#include <QWidget>
#include"aboutdialog.h"
#include"notice.h"
namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);

    ~Start();

signals:
    void display(int number);
    void resetBG(int number);
private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_clicked();

private:
    Notice anotice;     //公告界面
    void loadAll();
    Ui::Start *ui;
    AboutDialog ad;

};

#endif // START_H
