#include "DockWin.h"
#include "MainWindow.h"
#include "ModWidth.h"


CDockWin::CDockWin(QWidget *parent)
    :QWidget(parent)
{
    setupUi(this);
    lineEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
    text_Help->setText("此时初始化为无画图菜单状态，可以进行拖动和修改图元。画图时信息框将显示各图元信息。");
}

void CDockWin::on_btn_mouse_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_NONE;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    text_Help->setText("选择鼠标，此时为无画图菜单状态，可以进行拖动和修改图元");
}

void CDockWin::on_btn_width_clicked()
{
    CModWidth mod_width;
    mod_width.LE_width->setText(le_width->text());
    switch(mod_width.exec()) {
    case QDialog::Accepted:
    {
        le_width->setText(mod_width.LE_width->text());
        CDrawWin::widLine = mod_width.LE_width->text().toInt();
    }
        break;
    }
}

void CDockWin::on_btn_drawLine_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_LINE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
    qDebug() << CDrawWin::widLine;
    le_width->setText(QString("%1").arg(CDrawWin::widLine));
    text_Help->setText("选择直线，此时为画直线菜单状态，点击鼠标确定点的坐标，拖动确定下一个点，拖动时将鼠标放置直线上，修改时将鼠标放在红色的点上进行拖动");
}


void CDockWin::on_btn_drawRect_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_RECTANGE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
    text_Help->setText("选择矩形，此时为画矩形菜单状态，使用鼠标确定左上方和右下方顶点画出矩形，拖动时将鼠标放置在中心的绿色点上，修改时将鼠标放在左上角或者右下角的绿色点上");
}
void CDockWin::on_btn_drawCir_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_CIRCLE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
    text_Help->setText("选择圆形，此时为画圆菜单状态，使用鼠标确定圆心和半径画出圆形，拖动时将鼠标点击圆心点位置，修改时将鼠标点击圆上红色点位置");
}
void CDockWin::on_btn_drawPoly_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_POLYGON;
    QApplication::setOverrideCursor(Qt::CrossCursor);
    text_Help->setText("选择多边形，此时为画多边形菜单状态，使用鼠标确定n个点来画出多边形，最后一个点请使用鼠标右键点击确定，拖动时将鼠标点击每条边中心位置的绿色点上，修改时将鼠标点击顶点的红色点上");
}
void CDockWin::on_btn_drawAngle_clicked()
{
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_ANGLE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
    text_Help->setText("选择角度，此时为画角度菜单状态，使用鼠标确定三个点画出一个夹角，拖动时将鼠标点击绿色顶点，修改时鼠标点击红色的点");
}
void CDockWin::on_btn_color_clicked()
{
    int m_red = 0;
    int m_green = 0;
    int m_blue = 0;
    CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_NONE;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QPalette palette = this->palette();
    const QColor& color
            = QColorDialog::getColor(palette.color(QPalette::Base), this);
    if(color.isValid())
    {
        palette.setColor(QPalette::Base, color);
        this->setPalette(palette);
    }

   m_red = color.red();
   m_green = color.green();
   m_blue = color.blue();
   QString str = QString("background-color: rgb(%1, %2, %3);").arg(m_red).arg(m_green).arg(m_blue);
   lineEdit->setStyleSheet(str);
   CDrawWin::m_curCol = CDrawWin::m_CirCol = CDrawWin::m_RectCol = CDrawWin::m_PolyCol = CDrawWin::m_AngCol = color;
}

void CDockWin::on_btn_black_clicked()
{
    CDrawWin::m_curCol.setRgb(0,0,0);
    CDrawWin::m_CirCol.setRgb(0,0,0);
    CDrawWin::m_RectCol.setRgb(0,0,0);
    CDrawWin::m_PolyCol.setRgb(0,0,0);
    CDrawWin::m_AngCol.setRgb(0,0,0);
    lineEdit->setStyleSheet("background-color: rgb(0, 0, 0);");
}

void CDockWin::on_btn_red_clicked()
{
    CDrawWin::m_curCol.setRgb(255,0,0);
    CDrawWin::m_CirCol.setRgb(255,0,0);
    CDrawWin::m_RectCol.setRgb(255,0,0);
    CDrawWin::m_PolyCol.setRgb(255,0,0);
    CDrawWin::m_AngCol.setRgb(255,0,0);
    lineEdit->setStyleSheet("background-color: rgb(255, 0, 0);");
}

void  CDockWin::on_btn_green_clicked()
{
    CDrawWin::m_curCol.setRgb(0,255,0);
    CDrawWin::m_CirCol.setRgb(0,255,0);
    CDrawWin::m_RectCol.setRgb(0,255,0);
    CDrawWin::m_PolyCol.setRgb(0,255,0);
    CDrawWin::m_AngCol.setRgb(0,255,0);
    lineEdit->setStyleSheet("background-color: rgb(0, 255, 0);");
}
void  CDockWin::on_btn_blue_clicked()
{
    CDrawWin::m_curCol.setRgb(0,0,255);
    CDrawWin::m_CirCol.setRgb(0,0,255);
    CDrawWin::m_RectCol.setRgb(0,0,255);
    CDrawWin::m_PolyCol.setRgb(0,0,255);
    CDrawWin::m_AngCol.setRgb(0,0,255);
    lineEdit->setStyleSheet("background-color: rgb(0, 0, 255);");
}
void  CDockWin::on_btn_yellow_clicked()
{
    CDrawWin::m_curCol.setRgb(255,255,0);
    CDrawWin::m_CirCol.setRgb(255,255,0);
    CDrawWin::m_RectCol.setRgb(255,255,0);
    CDrawWin::m_PolyCol.setRgb(255,255,0);
    CDrawWin::m_AngCol.setRgb(255,255,0);
    lineEdit->setStyleSheet("background-color: rgb(255, 255, 0);");
}




