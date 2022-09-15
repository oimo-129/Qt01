#ifndef FINDXLSX_H
#define FINDXLSX_H

#include <QWidget>

namespace Ui {
class FindXlsx;
}

class FindXlsx : public QWidget
{
    Q_OBJECT

public:
    explicit FindXlsx(QWidget *parent = nullptr);
    ~FindXlsx();

private slots:
    //void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    int len;
    int len1;
    Ui::FindXlsx *ui;

};

#endif // FINDXLSX_H
