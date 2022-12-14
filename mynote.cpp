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
#include<QPushButton>  //时间按钮
#include<QMessageBox>
#include<QCloseEvent>
#include<QColor>
#include<QFont>
#include<QColorDialog>
#include<QFontDialog>
#include<QPaintEvent>
#include<QPainter>
#include<QCoreApplication>
#include<QApplication>
#include<QDesktopServices>
#include<QUrl>
#include"gif.h"
QString FileContent;
MyNote::MyNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyNote)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Image/OnePiece.png"));

    //进行相关的测试演示
    //    connect(ui->actionExit,ui->actionExit->triggered(),this,myClose(event));

    //   }
    ui->textEdit->setHidden(true);
    this->setMaximumSize(800,800);
    this->setMinimumSize(800,800);

    connect(ui->actionExit,QAction::triggered,[=](){this->close();});
    //Qt功能的介绍
    connect(ui->actionQt,QAction::triggered,qApp,QApplication::aboutQt);
}

MyNote::~MyNote()
{
    delete ui;
}

//New File
void MyNote::on_actionNew_triggered()
{
    //新建文件功能的实现
    ui->textEdit->setHidden(false);
    ui->textEdit->clear();
    //对退出事件单独定义槽事件

}
void MyNote::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/Image/background.jpg"));
}

//Open File
void MyNote::on_actionOpen_triggered()
{
    QString files = QFileDialog::getOpenFileName(this,"打开新的文本文件","/我的文件");
    qDebug()<<files;
    ui->lineEdit->setText(files);
    //QTextCodec *codec = QTextCodec::codecForName("gbk");
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
//8.2日，添加笔记本菜单栏的第二个功能

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



void MyNote::on_actionColor_triggered()
{
    //实现笔记本对于字体颜色的调整
    QColor col=QColorDialog::getColor(Qt::blue,this);
    if(col.isValid())
    {
        ui->textEdit->setTextColor(col);
    }else{
        QMessageBox::information(this,"错误信息","颜色不合法");
        return;
    }
}


void MyNote::on_actionFont_triggered()
{
    //实现笔记本字体的调整
    bool ok;
    QFont font=QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10),this);
    if(ok){
        ui->textEdit->setFont(font);
    }else{
        QMessageBox::information(this,"错误信息","字体不合法");
        return;
    }

}


void MyNote::on_actionDateTime_triggered()
{
    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy-M-dd hh:mm:ss");
//希望能够更改输出的时间的格式
    //time=time.replace(valueRegExp, "<font style='font-size:16px; background-color:white; color:blue;'>\\1</font>");
    ui->textEdit->append(time);
}




void MyNote::on_actionGithub_triggered()
{
  QDesktopServices::openUrl( QUrl("https://github.com/oimo-129"))  ;
}

//显示展示gif的相关功能
void MyNote::on_actionJif_triggered()
{
    Gif *gif=new Gif;
    gif->show();

}

