#ifndef GAMECOMPLETE_H
#define GAMECOMPLETE_H

#include <QWidget>

namespace Ui {
class Gamecomplete;
}

class Gamecomplete : public QWidget
{
    Q_OBJECT

public:
    explicit Gamecomplete(QWidget *parent = 0);
    ~Gamecomplete();
signals:
    void display(int number);
private slots:
    void on_pushButton_return_clicked();

private:
    Ui::Gamecomplete *ui;
};

#endif // GAMECOMPLETE_H
