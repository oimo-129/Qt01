#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);
    void (QSpinBox:: *spin) (int)=&QSpinBox::valueChanged;
    connect(ui->spinBox,spin,[=](int val ){
        ui->horizontalSlider->setValue(val);
    });
    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int val ){
        ui->spinBox->setValue(val);
    });

    }

//添加相关的功能
int  SmallWidget::getDate()
{
    return ui->horizontalSlider->value();

}

void SmallWidget::setDate(int val)
{
    ui->horizontalSlider->setValue(val);


}

SmallWidget::~SmallWidget()
{
    delete ui;
}