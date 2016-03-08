#ifndef __SCALESAVE_H__
#define __SCALESAVE_H__

#include "ui_ScaleSave.h"
#include "CSinfo.h"
#include <QtGui>


class CScaleSave:public QDialog,
                 public Ui_Dialog
{
    Q_OBJECT
public:
    CScaleSave(QWidget *parent = NULL);

public:
   void add_stuInfo_2_ui(CS &Info);
   void Load_info_from_ini();

public slots:
    void on_btn_add_clicked();
    void on_btn_saveinfo_clicked();
    void on_tb_info_cellClicked(int row,int col);
    void on_btn_mod_clicked();
    void on_btn_del_clicked();
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

public:
    QVector<CS> scale_list;
    int m_curSelect;
    static int m_count;
    CS del_index;

};


#endif
