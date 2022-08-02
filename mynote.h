#ifndef MYNOTE_H
#define MYNOTE_H
/*git 提交代码*/
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

    void on_actionSave_triggered();

   // void on_actionExit_triggered(QCloseEvent *event);
//void myClose(QCloseEvent *event);

    void on_actionColor_triggered();

    void on_actionFont_triggered();

private:
    void paintEvent(QPaintEvent *);
    Ui::MyNote *ui;
};
#endif // MYNOTE_H
