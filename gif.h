#ifndef GIF_H
#define GIF_H

#include <QDialog>
#include <QMovie>
namespace Ui {
class Gif;
}

class Gif : public QDialog
{
    Q_OBJECT

public:
    explicit Gif(QWidget *parent = nullptr);
    ~Gif();
QMovie *movie;
private:
    Ui::Gif *ui;
};

#endif // GIF_H
