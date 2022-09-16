/********************************************************************************
** Form generated from reading UI file 'form1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM1_H
#define UI_FORM1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <smallwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Form1
{
public:
    QHBoxLayout *horizontalLayout;
    SmallWidget *widget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btn1;
    QPushButton *btn2;

    void setupUi(QWidget *Form1)
    {
        if (Form1->objectName().isEmpty())
            Form1->setObjectName(QString::fromUtf8("Form1"));
        Form1->resize(402, 123);
        horizontalLayout = new QHBoxLayout(Form1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new SmallWidget(Form1);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(Form1);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btn1 = new QPushButton(widget_2);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        verticalLayout->addWidget(btn1);

        btn2 = new QPushButton(widget_2);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        verticalLayout->addWidget(btn2);


        horizontalLayout->addWidget(widget_2);


        retranslateUi(Form1);

        QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(QWidget *Form1)
    {
        Form1->setWindowTitle(QCoreApplication::translate("Form1", "Form", nullptr));
        btn1->setText(QCoreApplication::translate("Form1", "\350\256\276\347\275\256\345\210\26050", nullptr));
        btn2->setText(QCoreApplication::translate("Form1", "\350\277\224\345\233\236\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM1_H
