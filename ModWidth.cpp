#include "ModWidth.h"

CModWidth::CModWidth(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
}



void CModWidth::on_btn_ok_clicked()
{
    accept();
}
void CModWidth::on_btn_cancel_clicked()
{
    reject();
}
