#include "mynote.h"
#include "ui_mynote.h"
//实现点击QAction的对QText的保存，新建,打开字节流文件以及退出
#include<QFileDialog>
#include <Qdebug>
#include <QFile>
#include <QFileInfo>
#include<QTextCodec>
#include<QDebug>
#include<QDateTime>
MyNote::MyNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyNote)
{
    ui->setupUi(this);
}

MyNote::~MyNote()
{
    delete ui;
}


void MyNote::on_actionNew_triggered()
{
    //新建文件功能的实现
    ui->textEdit->clear();
}


void MyNote::on_actionOpen_triggered()
{
    QString files = QFileDialog::getOpenFileName(this,"打开新的文本文件","/我的文件");
    qDebug()<<files;
    ui->lineEdit->setText(files);
  QTextCodec *codec = QTextCodec::codecForName("gbk");
QFile file(files);
    file.open(QIODevice::ReadOnly);
    QByteArray array;
    while(!file.atEnd()){
        array +=file.readLine();
    }
    ui->textEdit->setText(array);
    file.close();
    QFileInfo  info(files);

    qDebug() << "文件后缀名:" <<info.suffix() << "文件大小：" <<info.size() <<
                "文件名："<< info.fileName() << "文件路径："<<info.filePath();

    qDebug() << "创建日期：" << info.created().toString("yyyy-MM-dd hh:mm:ss")<<
                "最后修改日期："<<info.lastModified().toString("yyyy/MM/dd hh:mm:ss");
}

