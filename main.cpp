#include "mynote.h"
#include<QDate>
#include<QTime>
#include<QString>
#include <QApplication>
/*添加相关的表格处理模块*/
#include "xlsxdocument.h"
int main(int argc, char *argv[])
{
    //添加相关的表格处理功能
    QXlsx::Document xlsx;
    xlsx.write("A1","Hello Qt!");
    xlsx.write("A2", 12345);
    xlsx.write("A3", "=44+33");
    xlsx.write("A4", true);
    xlsx.write("A5", "http://qt-project.org");
    xlsx.write("A6", QDate(2013, 12, 27));
    xlsx.write("A7", QTime(6, 30));
    QString xlsxname="日志输入.xlsx";

    xlsx.saveAs(xlsxname);
    QApplication a(argc, argv);
    MyNote w;
    w.show();
    return a.exec();
}
