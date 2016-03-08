#include "scaleInfo.h"
#include "ScaleSave.h"


CscaleInfo::CscaleInfo(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
}


void CscaleInfo::on_btn_ok_clicked()
{
    accept();
}

void CscaleInfo::on_btn_cancel_clicked()
{
    reject();
}


void CscaleInfo::on_btn_font_clicked()
{
    bool ok;
    const QFont& font = QFontDialog::getFont(&ok,
                                             str_font,
                                             this,
                                             tr("SET FONT"));
    if(ok) {// 如果<确定>,设置字体.
        str_font = font;
    }
}

void CscaleInfo::on_btn_save_clicked()
{
    CScaleSave Save_dlg;
    switch(Save_dlg.exec()) {
    case QDialog::Accepted:
    {
        le_len->setText(Save_dlg.le_len->text());
        le_name->setText(Save_dlg.le_name->text());
        le_unit->setText(Save_dlg.le_unit->text());
    }
        break;
    case QDialog::Rejected:
    {

    }
        break;
    }
}

