#include "mynote.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyNote w;
    w.show();
    return a.exec();
}
