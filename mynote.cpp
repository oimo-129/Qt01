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
#include<QPushButton>
#include<QMessageBox>
#include<QCloseEvent>
QString FileContent;
MyNote::MyNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyNote)
{
    ui->setupUi(this);
    //进行相关的测试演示
//    connect(ui->actionExit,ui->actionExit->triggered(),this,myClose(event));

//   }
    connect(ui->actionExit,QAction::triggered,[=](){this->close();});
}

MyNote::~MyNote()
{
    delete ui;
}

//New File
void MyNote::on_actionNew_triggered()
{
    //新建文件功能的实现
    ui->textEdit->clear();
    //对退出事件单独定义槽事件

}

//Open File
void MyNote::on_actionOpen_triggered()
{
    QString files = QFileDialog::getOpenFileName(this,"打开新的文本文件","/我的文件");
    qDebug()<<files;
    ui->lineEdit->setText(files);
  QTextCodec *codec = QTextCodec::codecForName("gbk");
  //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
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

//Save File
void MyNote::on_actionSave_triggered()
{
    QFileDialog myfiledialog;
    QString fileName=myfiledialog.getSaveFileName(this,tr("保存文件"),"",tr("Text File(*.txt)"));
    if(fileName=="")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QString str=ui->textEdit->toPlainText();
        textStream<<str;
        QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
       FileContent=str;
        file.close();
    }

}
//Exit
//这个功能要重写
//void MyNote::on_actionExit_triggered(QCloseEvent *event)
//{
// //对保存文件的判断
//    if(ui->textEdit->toPlainText()==FileContent){
//      event->accept();
//    }
//    else{
//        if(QMessageBox::warning(this,tr("警告"),tr("文件还未保存，确认退出？"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
//            event->accept();
//        }
//        else{
//            event->ignore();
//        }

//    }
//    close();
//}

//void MyNote::myClose(QCloseEvent *event){
//    if(ui->textEdit->toPlainText()==FileContent){
//        event->accept();
//      }
//      else{
//          if(QMessageBox::warning(this,tr("警告"),tr("文件还未保存，确认退出？"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
//              event->accept();
//          }
//          else{
//              event->ignore();
//          }

//      }
//      close();
//}


