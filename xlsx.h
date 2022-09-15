#ifndef XLSX_H
#define XLSX_H

#include <QString>
#include <QStringList>
#include "xlsxdocument.h"

class xlsx
{
public:
    xlsx();

    //读取第row行数据
    static QStringList readRow(const QXlsx::Document& xlsx, int row);

    //读取多行信息，从第rowStart行到第rowEnd行
    //注意：指针使用后要释放空间！
    static QStringList* readRows(const QXlsx::Document& xlsx, int rowStart, int rowEnd=1);

    //按行写数据，从第row行第col列开始写
    static bool writeRow(QXlsx::Document& xlsx, QStringList list, int row, int col);
};

#endif // XLSX_H
