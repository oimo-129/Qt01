#include "findxlsx.h"
#include "ui_findxlsx.h"

//实现对表格进行操作
#include "xlsx.h"
#include<QDebug>
#include<QFileDialog>
#include<QDir>
#include<mainwindow.h>
#include<QString>
#include <QPainter>
#include <QPaintEvent>
FindXlsx::FindXlsx(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindXlsx)
{
    len=0;
    len1=0;
    ui->setupUi(this);
    QPalette pal;

    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/picture/bg3 (2).jpg")));
    this->setPalette(pal);
    //创建从机表格
    ui->tableWidget->setColumnCount(12);
    QStringList header_cong;
    header_cong<<"北京时间"<<"IGBT1温度"<<"IGBT2温度"<<"IGBT浪涌保护";
    header_cong<<"工作步骤"<<"工作时间"<<"顶部温度"<<"检锅蜂鸣";
    header_cong<<"IGBT过流保护"<<"底部温度"<<"IGBT反压保护"<<"协议报";
    ui->tableWidget->setHorizontalHeaderLabels(header_cong);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(11,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setFont(QFont("黑体",10));
    //ui->tableWidget->horizontalHeader()->setBackgroundRole
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    //9.13d对从机表格进行修正
    ui->tableWidget->setWindowTitle("从机查询");
    ui->tableWidget->setFont(QFont("黑体",8));
    //ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();


    //创建主机信息表格
    ui->tableWidget_2->setColumnCount(12);
    QStringList header_zhu;
    header_zhu<<"北京时间"<<"工作时间"<<"模式"<<"顶部加热状态";
    header_zhu<<"R角IGBT感温包AD值"<<"底部IGBT感温包AD"<<"顶部感温包AD值"<<"底部线盘加热状态";
    header_zhu<<"R角线盘状态"<<"饭煲状态"<<"侧加热状态"<<"协议报";
    ui->tableWidget_2->setHorizontalHeaderLabels(header_zhu);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(11,QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setFont(QFont("黑体",10));
    ui->tableWidget_2->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");

}

FindXlsx::~FindXlsx()
{
    delete ui;
}



void FindXlsx::on_pushButton_pressed()
{   

    qDebug()<<"14:17:23；14：20：42";
    QString findTime=ui->timeEdit->text();
    //从机表格查询
    int n=1;
    QString filename;
    filename="从机数据"+QString::number(n)+".xlsx";
    QFileInfo fi(filename);
    while(fi.isFile()){

        QXlsx::Document xlsx(filename);
        QXlsx::CellRange range = xlsx.dimension();
        int row=range.lastRow()-range.firstRow();
        for(int i=2;i<=row;i++){
            QString chart_time=xlsx.read(i,1).toString().left(8);
            if(findTime==chart_time){
                QTableWidgetItem *item[13];
                int nCount;
                nCount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(nCount);
                item[0]=new QTableWidgetItem(chart_time);
                ui->tableWidget->setItem(len,0,item[0]);
                for(int k=2;k<=12;k++){
                    QString value=xlsx.read(i,k).toString();
                    item[k]=new QTableWidgetItem(value);
                    ui->tableWidget->setItem(len,k-1,item[k]);
                }

                len++;
            }else{
                QMessageBox::information(this,"提示","这个时刻的数据未被监测");
                break;
            }
        }
        n++;
        filename="从机数据"+QString::number(n)+".xlsx";
        fi.setFile(filename);
    }
    n=1;
    //主机表格查询
    int m=1;
    QString filename1;
    filename1="主机数据"+QString::number(m)+".xlsx";
    QFileInfo fi1(filename1);
    while(fi1.isFile()){

        QXlsx::Document xlsx(filename1);
        QXlsx::CellRange range1 = xlsx.dimension();
        int row1=range1.lastRow()-range1.firstRow();

        for(int i=2;i<=row1;i++){
            QString chart_time1=xlsx.read(i,1).toString().left(8);
            if(findTime==chart_time1){
                QTableWidgetItem *item1[13];
                int nCount1;
                nCount1=ui->tableWidget_2->rowCount();
                ui->tableWidget_2->insertRow(nCount1);
                item1[0]=new QTableWidgetItem(chart_time1);
                ui->tableWidget_2->setItem(len1,0,item1[0]);
                for(int k=2;k<=12;k++){
                    QString value1=xlsx.read(i,k).toString();
                    item1[k]=new QTableWidgetItem(value1);
                    ui->tableWidget_2->setItem(len1,k-1,item1[k]);
                }
                len1++;
            }else{
                QMessageBox::information(this,"提示","这个时刻的数据未被监测");
                break;
            }

        }
        m++;
        filename1="主机数据"+QString::number(m)+".xlsx";
        fi1.setFile(filename);
    }
    m=1;

}

