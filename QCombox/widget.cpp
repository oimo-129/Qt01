#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include "form1.h"
#include<QProcess>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //实现复合功能
    //void (QSpinBox:: *spin) (int)=&QSpinBox::valueChanged;
//    connect(ui->spinBox,spin,[=](int val ){
//        ui->horizontalSlider->setValue(val);
//    });
//   connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int val ){
//        ui->spinBox->setValue(val);
//    });
    //对它进行重载
    void (QSpinBox:: *spin1) (int)=&QSpinBox::valueChanged;
    connect(ui->spinBox,spin1,[=](int val){
        ui->horizontalSlider->setValue(val);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    Form1 *form1=new Form1();
    form1->show();

}

//功能：打开文本框所传字符串功能,需要对这个功能进行进一步的完善
void Widget::on_pushButton_2_clicked()
{
   QString str=ui->lineEdit->text();

   QProcess *prc=new QProcess;
   prc->start(str.trimmed());
}

