#ifndef __MODWIDTH_H__
#define __MODWIDTH_H__

#include "ui_ModWidth.h"
#include <QtGui>

class CModWidth:public QDialog,
                public Ui_modWidth
{
    Q_OBJECT
public:
    CModWidth(QWidget *parent = NULL);

public slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();


};


#endif
