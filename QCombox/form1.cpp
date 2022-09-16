#include "form1.h"
#include "ui_form1.h"
#include<QDebug>
Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
    connect(ui->btn1,&QPushButton::clicked,[=](){
        ui->widget->setDate(50);
    });
    connect(ui->btn2,&QPushButton::clicked,[=](){
        qDebug()<<ui->widget->getDate();
    });
}

Form1::~Form1()
{
    delete ui;
}
