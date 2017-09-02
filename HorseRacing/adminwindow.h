#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>

namespace Ui {
class Adminwindow;
}

class Adminwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Adminwindow(QWidget *parent = 0);
    ~Adminwindow();
signals:
    void display(int number);
public slots:
    void flashNow(int S);
private slots:
    void on_pushButton_return_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_delete_clicked();

private:
    Ui::Adminwindow *ui;
    int IDtoView;
};

#endif // ADMINWINDOW_H
