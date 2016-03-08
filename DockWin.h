#ifndef __DOCKWIN_H__
#define __DOCKWIN_H__

#include "ui_DockWin.h"
#include <QtGui>
#include "Shape.h"

class CDockWin:public QWidget,Ui_DockDlg
{
    Q_OBJECT
public:
    CDockWin(QWidget *parent = NULL);


public slots:
    void on_btn_drawLine_clicked();
    void on_btn_drawRect_clicked();
    void on_btn_drawCir_clicked();
    void on_btn_drawPoly_clicked();
    void on_btn_drawAngle_clicked();
    void on_btn_mouse_clicked();
    void on_btn_color_clicked();
    void on_btn_black_clicked();
    void on_btn_red_clicked();
    void on_btn_green_clicked();
    void on_btn_blue_clicked();
    void on_btn_yellow_clicked();
    void on_btn_width_clicked();
};


#endif
