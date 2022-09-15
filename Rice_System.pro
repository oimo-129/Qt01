#-------------------------------------------------
#最终的qt
# Project created by QtCreator 2022-03-22T13:42:32
#
#-------------------------------------------------

QT       += core gui serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rice_System
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    findxlsx.cpp \
        main.cpp \
        mainwindow.cpp \
    xlsx.cpp

HEADERS += \
    findxlsx.h \
        mainwindow.h \
    xlsx.h

FORMS += \
        findxlsx.ui \
        mainwindow.ui

RESOURCES += \
    pic.qrc

include(xlsx/qtxlsx.pri)

DISTFILES += \
    ../鼠标动图.gif
