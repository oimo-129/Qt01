#include "gif.h"
#include "ui_gif.h"

Gif::Gif(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gif)
{
    ui->setupUi(this);
    this->movie=new QMovie( ":Image/mario.gif");
    ui->label->setMovie(this->movie);
    this->movie->start();
}

Gif::~Gif()
{
    delete ui;
}
