#ifndef __MOD_H__
#define __MOD_H__

#include "ui_mod.h"
#include <QtGui>

class CMod:public QDialog,
           public Ui_modDlg

{
    Q_OBJECT
public:
    CMod(QWidget *parent = NULL);

public slots:
    void on_btn_color_clicked();
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();
public:
    QColor mod_color;
};
#endif
