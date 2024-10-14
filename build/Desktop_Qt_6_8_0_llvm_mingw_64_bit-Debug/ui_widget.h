/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *lbl_HP;
    QLabel *lbl_Health;
    QLabel *lbl_Score;
    QLabel *lbl_Enemy;
    QLabel *lbl_Guide;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(400, 400);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        lbl_HP = new QLabel(Widget);
        lbl_HP->setObjectName("lbl_HP");
        lbl_HP->setGeometry(QRect(40, 360, 40, 25));
        lbl_HP->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 18pt \"Comic Sans MS\";"));
        lbl_Health = new QLabel(Widget);
        lbl_Health->setObjectName("lbl_Health");
        lbl_Health->setGeometry(QRect(300, 360, 81, 25));
        lbl_Health->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 18pt \"Comic Sans MS\";"));
        lbl_Score = new QLabel(Widget);
        lbl_Score->setObjectName("lbl_Score");
        lbl_Score->setGeometry(QRect(310, 6, 38, 38));
        lbl_Score->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 10pt \"Comic Sans MS\";"));
        lbl_Enemy = new QLabel(Widget);
        lbl_Enemy->setObjectName("lbl_Enemy");
        lbl_Enemy->setGeometry(QRect(150, 20, 100, 125));
        lbl_Enemy->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 18pt \"Comic Sans MS\";"));
        lbl_Enemy->setPixmap(QPixmap(QString::fromUtf8(":/sprites/sans/sansspirte.png")));
        lbl_Enemy->setScaledContents(true);
        lbl_Guide = new QLabel(Widget);
        lbl_Guide->setObjectName("lbl_Guide");
        lbl_Guide->setGeometry(QRect(10, 10, 121, 131));
        lbl_Guide->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 8pt \"Comic Sans MS\";"));
        lbl_Guide->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Undertale QtGraphics", nullptr));
        lbl_HP->setText(QCoreApplication::translate("Widget", "HP:", nullptr));
        lbl_Health->setText(QCoreApplication::translate("Widget", "4", nullptr));
        lbl_Score->setText(QCoreApplication::translate("Widget", "score:\n"
"0", nullptr));
        lbl_Enemy->setText(QString());
        lbl_Guide->setText(QCoreApplication::translate("Widget", "Keybinds sheet:\n"
"H -> Show hitboxes\n"
"Arrows -> Move\n"
"Esc-> Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
