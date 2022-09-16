#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>

namespace Ui {
class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = nullptr);
    ~SmallWidget();
    void setDate(int);
    int  getDate();

private:
    Ui::SmallWidget *ui;
    void spin();
};

#endif // SMALLWIDGET_H
