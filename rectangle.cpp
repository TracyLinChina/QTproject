#include "rectangle.h"
#include "MainWindow.h"
#include <math.h>

CRect::CRect()
{
    rectArea = 0;
    rectLength = 0;
    rectPerimeter = 0;
    rectWidth = 0;
    m_hitPen.setColor(Qt::green);
    m_hitPen.setWidth(5);
    rect_info_pen.setColor(Qt::blue);
    m_ctrlIndex = -1;

    m_shapeType = CDrawWin::SHAPE_RECTANGLE;
    qDebug() <<__LINE__<<"  "<<__func__;
}


void CRect::drawShape(QPainter &pt)
{
    QPoint central = (m_ptArray[0] + m_ptArray[1]) / 2;
    QPoint ltPt_0(m_ptArray[0].x()-2,m_ptArray[0].y()-2);
    QPoint rbPt_0(m_ptArray[0].x()+2,m_ptArray[0].y()+2);
    QPoint ltPt_1(m_ptArray[1].x()-2,m_ptArray[1].y()-2);
    QPoint rbPt_1(m_ptArray[1].x()+2,m_ptArray[1].y()+2);
    QPoint central_lt(central.x()-2,central.y()-2);
    QPoint central_rb(central.x()+2,central.y()+2);
    QRect rec_central(central_lt,central_rb);
    QRect rec_0(ltPt_0,rbPt_0);
    QRect rec_1(ltPt_1,rbPt_1);
    QRect rect(m_ptArray[0],m_ptArray[1]);
    pt.setPen(m_hitPen);
    pt.drawRect(rec_0);
    pt.drawRect(rec_1);
    pt.drawRect(rec_central);
    pt.setPen(rect_pen);
    pt.drawRect(rect);

}


void CRect::drawInfo(QPainter &Pt)
{
    qDebug() <<__LINE__<<"  "<<__func__;
    QPoint midPt = m_ptArray[1];
    QString str_length;
    QString str_area;
    QString str_perimeter;
    QString str_width;
    QString str_1 = " Length:";
    QString str_2 = " Area:";
    QString str_3 = " Perimeter:";
    QString str_4 = " Width:";
    QFont myFont;
    QFontMetrics fm(myFont);
    int width = 0;
    int width_1 = 0;
    int height = 0;

    rectLength = (double)fabs(m_ptArray[1].x() - m_ptArray[0].x());
    rectWidth = (double)fabs(m_ptArray[1].y() - m_ptArray[0].y());
    rectArea = rectLength * rectWidth;
    rectPerimeter = 2 * (rectLength + rectWidth);
    qDebug() <<__LINE__<<"  "<<__func__;
    str_length.setNum(rectLength);
    str_area.setNum(rectArea);
    str_perimeter.setNum(rectPerimeter);
    str_width.setNum(rectWidth);

    width = fm.width(str_3);
    width_1 = fm.width(str_perimeter);
    height = fm.height() * 6;

    QRect infoRect(midPt.x(),midPt.y(),width + width_1,height);
    Pt.setPen(rect_info_pen);
    Pt.drawRoundedRect(infoRect,5,5);
    Pt.drawText(infoRect,Qt::AlignCenter,
                QString("%1\n%2%3 \n%4%5 \n%6%7 \n%8%9 ").arg("Type:Rectangle").arg(str_1).arg(rectLength).arg(str_4).arg(rectWidth).arg(str_2).arg(rectArea).arg(str_3).arg(rectPerimeter));
}


void CRect::HitTest(QMouseEvent *event,bool &bHit)
{
    bHit = false;
    QPoint central = (m_ptArray[0] + m_ptArray[1]) / 2;
    QPoint central_lt(central.x()-2,central.y()-2);
    QPoint central_rb(central.x()+2,central.y()+2);
    QRect rec_central(central_lt,central_rb);
    if(rec_central.contains(event->pos())) {
        bHit = true;
    }
}


void CRect::HitCtrlTest(QMouseEvent *event,bool &bCtrlHit)
{
    bCtrlHit = false;
    int i = 0;
    for(i = 0;i < m_ptArray.size();i++) {
        QPoint ptLt(m_ptArray[i].x() - 2,m_ptArray[i].y() - 2);
        QPoint ptRb(m_ptArray[i].x() + 2,m_ptArray[i].y() + 2);
        QRect recTest(ptLt,ptRb);
        if(recTest.contains(event->pos())) {
            bCtrlHit = true;
            m_ctrlIndex = i;
            break;
        } else {
            m_ctrlIndex = -1;
        }
    }
}


void CRect::mousePressEvent(QMouseEvent* event)
{
    switch(countClick){
    case 0:
    {
        m_ptArray.push_back(event->pos());
        m_ptArray.push_back(event->pos());
        countClick++;
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAWING;
    }
        break;
    case 1:
    {
        m_ptArray[1] = event->pos();
        countClick++;
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
    }
        break;
    default:
    {
        if(countClick == 2) {
            if(m_ctrlIndex != -1) {
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_CHANGE;
            } else {
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAG;
                m_lastPt = event->pos();
            }
        }
    }
        break;
    }
}


void CRect::mouseReleaseEvent(QMouseEvent *event)
{
    switch(CDrawWin::m_curDrawStatus){
    case CDrawWin::DRAW_STATUS_NONE:
    case CDrawWin::DRAW_STATUS_DRAWING:
        break;
    case CDrawWin::DRAW_STATUS_DRAG:
    case CDrawWin::DRAW_STATUS_CHANGE:
    {
        // 修改当前画图状态为无画图状态
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
    }
        break;
    }
}


void CRect::mouseMoveEvent(QMouseEvent *event)
{
    switch(CDrawWin::m_curDrawStatus){
    case CDrawWin::DRAW_STATUS_NONE:
        break;
    case CDrawWin::DRAW_STATUS_DRAWING:
    {
        // 设置第二个点
        m_ptArray[1] = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_DRAG:
    {
        QPoint spanPt = event->pos() - m_lastPt;
        m_ptArray[0] += spanPt;
        m_ptArray[1] += spanPt;

        m_lastPt = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_CHANGE:
    {
        m_ptArray[m_ctrlIndex] = event->pos();
    }
        break;
    default:
        break;
    }
}
