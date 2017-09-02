#ifndef NOTICE_H
#define NOTICE_H

#include <QDialog>

namespace Ui {
class Notice;
}

class Notice : public QDialog
{
    Q_OBJECT

public:
    explicit Notice(QWidget *parent = 0);
    ~Notice();

private:
    void getNotice();
    Ui::Notice *ui;
};

#endif // NOTICE_H
