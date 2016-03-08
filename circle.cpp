#include "circle.h"
#include "MainWindow.h"
#include <math.h>
#define Pi 3.142

CCircle::CCircle()
{
    m_radium = 0;
    m_hitPen.setColor(Qt::red);
    m_hitPen.setWidth(5);
    cir_info_pen.setColor(Qt::blue);

    m_shapeType = CDrawWin::SHAPE_CIRCLE;
}


void CCircle::drawShape(QPainter &pt)
{
    pt.setPen(circle_pen);
    //计算出半径
    m_radium =qSqrt
            (
                (m_ptArray[1].y() -  m_ptArray[0].y())*(m_ptArray[1].y() -  m_ptArray[0].y()) +
            (m_ptArray[1].x() -  m_ptArray[0].x())*(m_ptArray[1].x() -  m_ptArray[0].x())
            );
    QPoint ltPt(m_ptArray[0].x()-2,m_ptArray[0].y()-2);
    QPoint rbPt(m_ptArray[0].x()+2,m_ptArray[0].y()+2);
    QRect recCircle(ltPt,rbPt);
    QPoint ltPt_1(m_ptArray[1].x()-2,m_ptArray[1].y()-2);
    QPoint rbPt_1(m_ptArray[1].x()+2,m_ptArray[1].y()+2);
    QRect recCircle_1(ltPt_1,rbPt_1);
    pt.setPen(m_hitPen);
    pt.drawRect(recCircle);
    pt.drawRect(recCircle_1);
    pt.setPen(circle_pen);
    pt.drawEllipse(m_ptArray[0],m_radium,m_radium);
}


void CCircle::drawInfo(QPainter &Pt)
{
    QPoint midPt = m_ptArray[1];
    QString str_rad;
    QString str_area;
    QString str_perimeter;
    QString str_1 = " Radium:";
    QString str_2 = " Area:";
    QString str_3 = " Perimeter:";
    QFont myFont;
    QFontMetrics fm(myFont);
    int width = 0;
    int width_1 = 0;
    int height = 0;

    m_radium = sqrt(pow(m_ptArray[0].x()-m_ptArray[1].x(),2)+pow(m_ptArray[0].y()-m_ptArray[1].y(),2));
    m_area = Pi * m_radium * m_radium;
    m_perimeter = 2 * Pi * m_radium;

    str_rad.setNum(m_radium);
    str_area.setNum(m_area);
    str_perimeter.setNum(m_perimeter);

    width = fm.width(str_perimeter);
    width_1 = fm.width(str_3);
    height = fm.height() * 5;

    QRect infoRect(midPt.x(),midPt.y(),width + width_1,height);
    Pt.setPen(cir_info_pen);
    Pt.drawRoundedRect(infoRect,5,5);
    Pt.drawText(infoRect,Qt::AlignCenter,
                QString("%1\n%2%3\n%4%5\n%6%7").arg(" Type:Circle").arg(str_1).arg(m_radium).arg(str_2).arg(m_area).arg(str_3).arg(m_perimeter));

}

void CCircle::HitTest(QMouseEvent *event,bool &bHit)
{
    bHit = false;
    QPoint ltPt(m_ptArray[0].x()-5,m_ptArray[0].y()-5);
    QPoint rbPt(m_ptArray[0].x()+5,m_ptArray[0].y()+5);
    QRect recCircle(ltPt,rbPt);
    if(recCircle.contains(event->pos())){
        bHit = true;
    }
}

void CCircle::HitCtrlTest(QMouseEvent *event, bool &bCtrlHit)
{
    bCtrlHit = false;
    QPoint ltPt_1(m_ptArray[1].x()-2,m_ptArray[1].y()-2);
    QPoint rbPt_1(m_ptArray[1].x()+2,m_ptArray[1].y()+2);
    QRect recCircle_1(ltPt_1,rbPt_1);
    if(recCircle_1.contains(event->pos())) {
        bCtrlHit = true;
        m_ctrlIndex = 1;
    }else {
        m_ctrlIndex = -1;
    }
}


void CCircle::mousePressEvent(QMouseEvent* event)
{
    switch(countClick)
    {
    case 0:
    {
        m_ptArray.push_back(event->pos());
        // 一开我们故意让两个点重合在一起
        m_ptArray.push_back(event->pos());
        // 点击次数加1
        countClick++;
        // 修改当前画图状态为绘画中
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAWING;
    }
        break;
    case 1:
    {
        // 设置第二个点
        m_ptArray[1] = event->pos();
        // 点击次数加1
        countClick++;
        // 修改当前画图状态为无画图状态
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


void CCircle::mouseReleaseEvent(QMouseEvent *event)
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



void CCircle::mouseMoveEvent(QMouseEvent *event)
{
    switch(CDrawWin::m_curDrawStatus)
    {
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
        qDebug() << __LINE__ << "-->"<<__func__;
        QPoint spanPt = event->pos() - m_lastPt;
        m_ptArray[0] += spanPt;
        m_ptArray[1] += spanPt;

        m_lastPt = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_CHANGE:
    {
        qDebug() << __LINE__;
        m_ptArray[m_ctrlIndex] = event->pos();
    }
        break;
    }
}




