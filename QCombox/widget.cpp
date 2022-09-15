#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include "form1.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //对它进行相关的描述
    //connect(ui->comboBox,&QComboBox::activated,[=](){
      //});
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    Form1 *form1=new Form1();
    form1->show();
    QString str= ui->comboBox->font().toString();
    qDebug()<<str;

}

