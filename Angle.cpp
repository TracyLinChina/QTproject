#include "Angle.h"
#include "MainWindow.h"
#include "math.h"


CAngle::CAngle()
{
    angle = 0;
    m_hitPen.setColor(Qt::red);
    m_hitPen.setWidth(5);

    ang_info_pen.setColor(Qt::blue);

    m_shapeType = CDrawWin::SHAPE_ANGLE;
    qDebug() << __func__ << " " << __LINE__;

}

void CAngle::drawShape(QPainter &pt)
{
    int i = 0;
    QPainterPath path;
    qDebug() << __func__ << " " << __LINE__;
    for(i = 0;i < m_ptArray.size();i++) {
        QPoint ltPt_0(m_ptArray[i].x()-2,m_ptArray[i].y()-2);
        QPoint rbPt_0(m_ptArray[i].x()+2,m_ptArray[i].y()+2);
        QRect rec_0(ltPt_0,rbPt_0);
        m_hitPen.setColor(Qt::red);
        pt.setPen(m_hitPen);
        pt.drawRect(rec_0);
        if(i == 1) {
            QPoint ltPt_0(m_ptArray[i].x()-2,m_ptArray[i].y()-2);
            QPoint rbPt_0(m_ptArray[i].x()+2,m_ptArray[i].y()+2);
            QRect rec_0(ltPt_0,rbPt_0);
            m_hitPen.setColor(Qt::green);
            pt.setPen(m_hitPen);
            pt.drawRect(rec_0);
        }

    }
    pt.setPen(angle_pen);
    path.moveTo(m_ptArray[0]);
    path.lineTo(m_ptArray[1]);
    path.lineTo(m_ptArray[2]);
    qDebug() << __func__ << " " << __LINE__;
    pt.drawPath(path);
}


void CAngle::drawInfo(QPainter &Pt)
{
    QPoint midPt = ((m_ptArray[1] + m_ptArray[2]))/2;
    QString str_angle;
    QString str_1 = " Type:Angle";
    QString str_2 = " Angle:";
    QFont myFont;
    QFontMetrics fm(myFont);
    qDebug() << __func__ << " " << __LINE__;
    int width = 0;
    int width1 = 0;
    int heigh = 0;

    double x1 = m_ptArray[0].x()-m_ptArray[1].x();
    double y1 = m_ptArray[0].y()-m_ptArray[1].y();
    double x2 = m_ptArray[2].x()-m_ptArray[1].x();
    double y2 = m_ptArray[2].y()-m_ptArray[1].y();
    double x = x1*x2 + y1*y2;
    double y = x1*y2 - x2*y1;

    angle = 180 / (M_PI /acos(x / (sqrt(pow(x,2) + pow(y,2)))));

    str_angle.setNum(angle);
    width = fm.width(str_angle);
    width1 = fm.width(str_2);
    heigh = fm.height() * 3;

    QRect rectinfo(midPt.x(),midPt.y(),width + width1,heigh);
    Pt.setPen(ang_info_pen);
    Pt.drawRoundedRect(rectinfo,5,5);
    Pt.drawText(rectinfo,Qt::AlignCenter,QString("%1\n %2%3 ").arg(str_1).arg(str_2).arg(angle));

}


void CAngle::mousePressEvent(QMouseEvent *event)
{
    switch(countClick){
    case 0:
    {
        m_ptArray.push_back(event->pos());
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
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAWING;
    }
        break;
    case 2:
    {
        m_ptArray[2] = event->pos();
        countClick++;
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
    }
        break;
    default:
    {
        if(countClick == 3) {
            if(m_ctrlIndex != -1) {
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_CHANGE;
            }else {
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAG;
                m_lastPt = event->pos();
            }
        }
    }
        break;

    }
}
void CAngle::mouseReleaseEvent(QMouseEvent *event)
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
void CAngle::mouseMoveEvent(QMouseEvent *event)
{
    switch(CDrawWin::m_curDrawStatus){
    case CDrawWin::DRAW_STATUS_NONE:
        break;
    case CDrawWin::DRAW_STATUS_DRAWING:
    {
        // 设置第n个点
        m_ptArray[countClick] = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_DRAG:
    {
        int i = 0;
        QPoint spanPt = event->pos() - m_lastPt;
        for(i = 0;i < m_ptArray.size();i++) {
            m_ptArray[i] += spanPt;
        }
         m_lastPt = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_CHANGE:
    {
        m_ptArray[m_ctrlIndex] = event->pos();
    }
        break;
    }
}

void CAngle::HitCtrlTest(QMouseEvent *event,bool &bCtrlHit)
{
    bCtrlHit = false;
    QPoint ltPt_0(m_ptArray[0].x()-2,m_ptArray[0].y()-2);
    QPoint rbPt_0(m_ptArray[0].x()+2,m_ptArray[0].y()+2);
    QPoint ltPt_1(m_ptArray[2].x()-2,m_ptArray[2].y()-2);
    QPoint rbPt_1(m_ptArray[2].x()+2,m_ptArray[2].y()+2);
    QRect rec_0(ltPt_0,rbPt_0);
    QRect rec_1(ltPt_1,rbPt_1);
    if(rec_0.contains(event->pos())) {
        bCtrlHit = true;
        m_ctrlIndex = 0;
    }else if(rec_1.contains(event->pos())) {
        bCtrlHit = true;
        m_ctrlIndex = 2;
    }else {
        m_ctrlIndex = -1;
    }
}


void CAngle::HitTest(QMouseEvent *event,bool &bHit)
{
    bHit = false;
    QPoint ltPt_0(m_ptArray[1].x()-2,m_ptArray[1].y()-2);
    QPoint rbPt_0(m_ptArray[1].x()+2,m_ptArray[1].y()+2);
    QRect rec_0(ltPt_0,rbPt_0);
    if(rec_0.contains(event->pos())) {
        bHit = true;
    }
}
