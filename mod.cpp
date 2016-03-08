#include "mod.h"

CMod::CMod(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);

//    btn_color->setFlat(true);
}


void CMod::on_btn_color_clicked()
{
    QPalette palette = this->palette();
    const QColor& color = QColorDialog::getColor(palette.color(QPalette::Base), this);
    if(color.isValid())
    {
        palette.setColor(QPalette::Base, color);
        this->setPalette(palette);
    }

    mod_color = color;
}
void CMod::on_btn_ok_clicked()\
{
    accept();
}
void CMod::on_btn_cancel_clicked()
{
    reject();
}
