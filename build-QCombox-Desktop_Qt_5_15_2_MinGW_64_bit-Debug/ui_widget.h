/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *exit;
    QPushButton *btn;
    QWidget *widget_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cBox1;
    QComboBox *cBox2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(574, 586);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_4 = new QWidget(Widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        exit = new QPushButton(widget_4);
        exit->setObjectName(QString::fromUtf8("exit"));

        verticalLayout_2->addWidget(exit);

        btn = new QPushButton(widget_4);
        btn->setObjectName(QString::fromUtf8("btn"));

        verticalLayout_2->addWidget(btn);


        verticalLayout_3->addWidget(widget_4);

        widget_2 = new QWidget(Widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget = new QWidget(widget_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 65, 64));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(80, 10, 126, 40));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cBox1 = new QComboBox(widget_5);
        cBox1->addItem(QString());
        cBox1->addItem(QString());
        cBox1->setObjectName(QString::fromUtf8("cBox1"));

        horizontalLayout_2->addWidget(cBox1);

        cBox2 = new QComboBox(widget_5);
        cBox2->addItem(QString());
        cBox2->addItem(QString());
        cBox2->setObjectName(QString::fromUtf8("cBox2"));

        horizontalLayout_2->addWidget(cBox2);


        verticalLayout_3->addWidget(widget_2);

        widget_3 = new QWidget(Widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_3->addWidget(widget_3);

        widget_6 = new QWidget(Widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_3 = new QHBoxLayout(widget_6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        spinBox = new QSpinBox(widget_6);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_3->addWidget(spinBox);

        horizontalSlider = new QSlider(widget_6);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider);


        verticalLayout_3->addWidget(widget_6);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\346\216\247\344\273\266\345\212\237\350\203\275\345\256\236\347\216\260", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\345\274\271\345\207\272\346\226\260\347\225\214\351\235\242", nullptr));
        exit->setText(QCoreApplication::translate("Widget", "\347\202\271\345\207\273\345\256\236\347\216\260\351\200\200\345\207\272", nullptr));
        btn->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        radioButton->setText(QCoreApplication::translate("Widget", "\347\224\267\346\200\247", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Widget", "\345\245\263\346\200\247", nullptr));
        cBox1->setItemText(0, QCoreApplication::translate("Widget", "\345\260\217\346\230\216", nullptr));
        cBox1->setItemText(1, QCoreApplication::translate("Widget", "\345\260\217\350\212\261", nullptr));

        cBox2->setItemText(0, QCoreApplication::translate("Widget", "\347\224\267\346\200\247", nullptr));
        cBox2->setItemText(1, QCoreApplication::translate("Widget", "\345\245\263\346\200\247", nullptr));

        label->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\347\250\213\345\272\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\347\241\256\350\256\244", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\215\225\347\213\254\345\256\236\347\216\260\347\254\246\345\220\210\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
