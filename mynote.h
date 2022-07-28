#ifndef MYNOTE_H
#define MYNOTE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyNote; }
QT_END_NAMESPACE

class MyNote : public QMainWindow
{
    Q_OBJECT

public:
    MyNote(QWidget *parent = nullptr);
    ~MyNote();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MyNote *ui;
};
#endif // MYNOTE_H
