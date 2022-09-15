#include "xlsx.h"
#include "xlsxcellrange.h"
#include <QStringList>
xlsx::xlsx()
{

}

//读取第row行数据
QStringList xlsx::readRow(const QXlsx::Document& xlsx, int row){
    QXlsx::CellRange range = xlsx.dimension();
    QStringList list;
    for(int i = range.firstColumn(); i<=range.lastColumn(); i++){
        list << xlsx.read(row, i).toString();
    }
    return list;
}

//读取多行信息，从第rowStart行到第rowEnd行
//注意：指针使用后要释放空间！
QStringList* xlsx::readRows(const QXlsx::Document& xlsx, int rowStart, int rowEnd){
    if(rowStart < 1 || rowEnd < rowStart)
        return nullptr;
    QStringList* plist = new QStringList[rowEnd - rowStart + 1];
    int count = 0;
    for(int i = rowStart; i <= rowEnd; i++){
        plist[count] = readRow(xlsx, i);
        count++;
    }
    return plist;
}

//按行写数据，从第row行第col列开始写
bool xlsx::writeRow(QXlsx::Document& xlsx, QStringList list, int row, int col){
    if(row < 1 || col < 1)
        return false;
    for(int i = 0; i<list.size(); i++)
    {
        xlsx.write(row, col+i, list.at(i));
    }
    return true;
}
