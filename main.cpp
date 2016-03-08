#include <QApplication>
#include <QtGui>
#include <QDebug>
#include "MainWindow.h"




int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    CDrawWin win;
    win.show();

    return app.exec();
}


