/********************************************************************************
** Form generated from reading UI file 'DockDlgO18608.ui'
**
** Created: Thu Nov 12 19:47:17 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DOCKDLGO18608_H
#define DOCKDLGO18608_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QPushButton *btn_mouse;
    QPushButton *btn_drawLine;
    QPushButton *btn_drawRect;
    QPushButton *btn_drawCir;
    QPushButton *btn_drawPoly;
    QPushButton *btn_drawAngle;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *le_Dockwidth;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QPushButton *btn_black;
    QPushButton *btn_red;
    QPushButton *btn_blue;
    QPushButton *btn_green;
    QPushButton *btn_yellow;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *btn_color;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QTextEdit *text_Help;

    void setupUi(QWidget *DockDlg)
    {
        if (DockDlg->objectName().isEmpty())
            DockDlg->setObjectName(QString::fromUtf8("DockDlg"));
        DockDlg->resize(308, 553);
        verticalLayout = new QVBoxLayout(DockDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(DockDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
""));

        horizontalLayout_4->addWidget(label_4);

        btn_mouse = new QPushButton(DockDlg);
        btn_mouse->setObjectName(QString::fromUtf8("btn_mouse"));
        btn_mouse->setStyleSheet(QString::fromUtf8("image: url(:/Mouse/images/SetMouse.jpg);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(btn_mouse);

        btn_drawLine = new QPushButton(DockDlg);
        btn_drawLine->setObjectName(QString::fromUtf8("btn_drawLine"));
        btn_drawLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"image: url(:/DrawShape/images/DrawLine.png);"));

        horizontalLayout_4->addWidget(btn_drawLine);

        btn_drawRect = new QPushButton(DockDlg);
        btn_drawRect->setObjectName(QString::fromUtf8("btn_drawRect"));
        btn_drawRect->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"image: url(:/DrawShape/images/DrawRectangle.png);"));

        horizontalLayout_4->addWidget(btn_drawRect);

        btn_drawCir = new QPushButton(DockDlg);
        btn_drawCir->setObjectName(QString::fromUtf8("btn_drawCir"));
        btn_drawCir->setStyleSheet(QString::fromUtf8("image: url(:/DrawShape/images/DrawCircle.png);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(btn_drawCir);

        btn_drawPoly = new QPushButton(DockDlg);
        btn_drawPoly->setObjectName(QString::fromUtf8("btn_drawPoly"));
        btn_drawPoly->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"image: url(:/DrawShape/images/DrawPolygon.png);"));

        horizontalLayout_4->addWidget(btn_drawPoly);

        btn_drawAngle = new QPushButton(DockDlg);
        btn_drawAngle->setObjectName(QString::fromUtf8("btn_drawAngle"));
        btn_drawAngle->setStyleSheet(QString::fromUtf8("image: url(:/DrawShape/images/DrawAngle.png);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(btn_drawAngle);


        verticalLayout->addLayout(horizontalLayout_4);

        line_3 = new QFrame(DockDlg);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DockDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout_2->addWidget(label);

        le_Dockwidth = new QLineEdit(DockDlg);
        le_Dockwidth->setObjectName(QString::fromUtf8("le_Dockwidth"));

        horizontalLayout_2->addWidget(le_Dockwidth);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(DockDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout_3->addWidget(label_3);

        btn_black = new QPushButton(DockDlg);
        btn_black->setObjectName(QString::fromUtf8("btn_black"));
        btn_black->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(btn_black);

        btn_red = new QPushButton(DockDlg);
        btn_red->setObjectName(QString::fromUtf8("btn_red"));
        btn_red->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        horizontalLayout_3->addWidget(btn_red);

        btn_blue = new QPushButton(DockDlg);
        btn_blue->setObjectName(QString::fromUtf8("btn_blue"));
        btn_blue->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 255);"));

        horizontalLayout_3->addWidget(btn_blue);

        btn_green = new QPushButton(DockDlg);
        btn_green->setObjectName(QString::fromUtf8("btn_green"));
        btn_green->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        horizontalLayout_3->addWidget(btn_green);

        btn_yellow = new QPushButton(DockDlg);
        btn_yellow->setObjectName(QString::fromUtf8("btn_yellow"));
        btn_yellow->setLayoutDirection(Qt::LeftToRight);
        btn_yellow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        horizontalLayout_3->addWidget(btn_yellow);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(DockDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(label_2);

        btn_color = new QPushButton(DockDlg);
        btn_color->setObjectName(QString::fromUtf8("btn_color"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_color->sizePolicy().hasHeightForWidth());
        btn_color->setSizePolicy(sizePolicy1);
        btn_color->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));"));

        horizontalLayout->addWidget(btn_color);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(DockDlg);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(DockDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\275\223\345\211\215\351\242\234\350\211\262\357\274\232\";\n"
"background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout_5->addWidget(label_6);

        lineEdit = new QLineEdit(DockDlg);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_5->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        label_5 = new QLabel(DockDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\350\257\264\346\230\216\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 178, 102, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));"));

        verticalLayout->addWidget(label_5);

        text_Help = new QTextEdit(DockDlg);
        text_Help->setObjectName(QString::fromUtf8("text_Help"));
        text_Help->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(text_Help);


        retranslateUi(DockDlg);

        QMetaObject::connectSlotsByName(DockDlg);
    } // setupUi

    void retranslateUi(QWidget *DockDlg)
    {
        DockDlg->setWindowTitle(QApplication::translate("DockDlg", "Form", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DockDlg", "\345\233\276\345\275\242\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_mouse->setText(QString());
        btn_drawLine->setText(QString());
        btn_drawRect->setText(QString());
        btn_drawCir->setText(QString());
        btn_drawPoly->setText(QString());
        btn_drawAngle->setText(QString());
        label->setText(QApplication::translate("DockDlg", "\347\224\273\347\254\224\345\256\275\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DockDlg", "\351\242\234\350\211\262\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_black->setText(QString());
        btn_red->setText(QString());
        btn_blue->setText(QString());
        btn_green->setText(QString());
        btn_yellow->setText(QString());
        label_2->setText(QApplication::translate("DockDlg", "\345\205\266\344\273\226\351\242\234\350\211\262\357\274\232", 0, QApplication::UnicodeUTF8));
        btn_color->setText(QApplication::translate("DockDlg", "Set Color", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DockDlg", "\345\275\223\345\211\215\351\242\234\350\211\262\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DockDlg", "\350\257\264\346\230\216\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DockDlg: public Ui_DockDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DOCKDLGO18608_H
