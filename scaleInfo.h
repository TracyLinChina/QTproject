#ifndef __SCALEINFO_H__
#define __SCALEINFO_H__

#include "ui_scaleInfo.h"
#include <QtGui>
class CscaleInfo:public QDialog,
                public Ui_DlgInfo
{
    Q_OBJECT
public:
    CscaleInfo(QWidget *parent = NULL);

public slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();
    void on_btn_font_clicked();
    void on_btn_save_clicked();
public:
    QFont str_font;
};


#endif
