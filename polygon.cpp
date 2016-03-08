#include "polygon.h"
#include "MainWindow.h"
#include <math.h>

int CPolygon::poly_countClick = 0;
unsigned char CPolygon::D_or_C = CPolygon::C_NULL;

CPolygon::CPolygon()
{
    qDebug() << __func__ << " DRAG = " <<DRAG;
    poly_area = 0;
    poly_perimter = 0;
    m_hitPen.setColor(Qt::red);
    m_hitPen.setWidth(5);
    m_shapeType = CDrawWin::SHAPE_POLYGON;
    poly_info_pen.setColor(Qt::blue);
}

void CPolygon::drawShape(QPainter &pt)
{
    QPolygon pts(m_ptArray);
    int i = 0;
    for(i = 0;i < m_ptArray.size();i++) {
        QPoint ltPt_0(m_ptArray[i].x()-2,m_ptArray[i].y()-2);
        QPoint rbPt_0(m_ptArray[i].x()+2,m_ptArray[i].y()+2);
        QRect rec_0(ltPt_0,rbPt_0);
        m_hitPen.setColor(Qt::red);
        pt.setPen(m_hitPen);
        pt.drawRect(rec_0);
        if(i > 0) {
            m_hitPen.setColor(Qt::green);
            pt.setPen(m_hitPen);
            if(i == m_ptArray.size()-1) {
                QPoint centrlPt = (m_ptArray[i] + m_ptArray[i-1])/2;
                QPoint centrlPt_1 = (m_ptArray[0] + m_ptArray[i])/2;
                QPoint ptLt(centrlPt.x()-2,centrlPt.y()-2);
                QPoint ptRb(centrlPt.x()+2,centrlPt.y()+2);
                QPoint ptLt_1(centrlPt_1.x()-2,centrlPt_1.y()-2);
                QPoint ptRb_1(centrlPt_1.x()+2,centrlPt_1.y()+2);
                QRect rectText(ptLt,ptRb);
                QRect rectText_1(ptLt_1,ptRb_1);
                pt.drawRect(rectText_1);
                pt.drawRect(rectText);
            }
            QPoint centrlPt = (m_ptArray[i] + m_ptArray[i-1])/2;
            QPoint ptLt(centrlPt.x()-2,centrlPt.y()-2);
            QPoint ptRb(centrlPt.x()+2,centrlPt.y()+2);
            QRect rectText(ptLt,ptRb);
            pt.drawRect(rectText);

        }

    }
    pt.setPen(poly_pen);
    pt.drawConvexPolygon(pts);
}

void CPolygon::drawInfo(QPainter &pt)
{
    QPoint midPt = m_ptArray[0];
    QString str_area;
    QString str_perimter;
    QString str_1 = " Area:";
    QString str_2 = " Perimter:";
    int i = 0;
    int size = m_ptArray.size();
    int width = 0;
    int width_1 = 0;
    int height = 0;
    QFont myFont;
    QFontMetrics fm(myFont);
    for(i = 0;i < size;i++) {
        poly_area = poly_area + (m_ptArray[i].x()*m_ptArray[(i+1)%size].y()-m_ptArray[(i+1)%size].x()*m_ptArray[i].y());
    }
    poly_area = fabs(0.5 * poly_area);

    str_area.setNum(poly_area);
    width = fm.width(str_area);
    width_1 = fm.width(str_1);
    height = fm.height() * 4;
    QRect infoRect(midPt.x(),midPt.y(),width + width_1,height);

    pt.setPen(poly_info_pen);
    pt.drawRoundedRect(infoRect,5,5);
    pt.drawText(infoRect,Qt::AlignCenter,QString("%1\n%2%3").arg(" Type:Polygon").arg(str_1).arg(poly_area));
}


void CPolygon::HitTest(QMouseEvent *event,bool &bHit)
{
    bHit = false;
    int i = 0;
    for(i = 1;i < m_ptArray.size();i++) {
        if(i == m_ptArray.size()-1) {
            QPoint centrlPt = (m_ptArray[i] + m_ptArray[i-1])/2;
            QPoint centrlPt_1 = (m_ptArray[0] + m_ptArray[i])/2;
            QPoint ptLt(centrlPt.x()-2,centrlPt.y()-2);
            QPoint ptRb(centrlPt.x()+2,centrlPt.y()+2);
            QPoint ptLt_1(centrlPt_1.x()-2,centrlPt_1.y()-2);
            QPoint ptRb_1(centrlPt_1.x()+2,centrlPt_1.y()+2);
            QRect rectText(ptLt,ptRb);
            QRect rectText_1(ptLt_1,ptRb_1);
            if(rectText.contains(event->pos())|| rectText_1.contains(event->pos())){
                bHit = true;
                D_or_C = DRAG;
            }
        }else {
            QPoint centrlPt = (m_ptArray[i] + m_ptArray[i-1])/2;
            QPoint ptLt(centrlPt.x()-2,centrlPt.y()-2);
            QPoint ptRb(centrlPt.x()+2,centrlPt.y()+2);
            QRect rectText(ptLt,ptRb);
            if(rectText.contains(event->pos())) {
                bHit = true;
                D_or_C = DRAG;
            }
        }
    }

}


void CPolygon::HitCtrlTest(QMouseEvent *event, bool &bCtrlHit)
{
    bCtrlHit = false;
    int i = 0;
    for(i = 0;i < m_ptArray.size();i++) {
        QPoint ltPt_0(m_ptArray[i].x()-2,m_ptArray[i].y()-2);
        QPoint rbPt_0(m_ptArray[i].x()+2,m_ptArray[i].y()+2);
        QRect rec_0(ltPt_0,rbPt_0);
        if(rec_0.contains(event->pos())) {
            bCtrlHit = true;
            m_ctrlIndex = i;
            D_or_C = CHANGE;
            qDebug() << "m_index = " << m_ctrlIndex;
            break;
        } else {
            m_ctrlIndex = -1;
        }
    }

}



void CPolygon::mousePressEvent(QMouseEvent* event)
{
    qDebug() <<__LINE__ <<"countclick = "<< countClick;
    switch (countClick) {
    case 0:
    {
        m_ptArray.push_back(event->pos());
        m_ptArray.push_back(event->pos());
        poly_countClick++;
        countClick++;
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAWING;
    }
        break;
    default:
    {
        if(CDrawWin::m_curDrawStatus == CDrawWin::DRAW_STATUS_NONE) {
            if(D_or_C == DRAG){
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAG;
                m_lastPt = event->pos();
                break;
            }else if(D_or_C == CHANGE) {
                CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_CHANGE;
                break;
            }

        }

        if(event->button() == Qt::RightButton){
            CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
            poly_countClick = 0;
            break;
        }
        m_ptArray.push_back(event->pos());
        m_ptArray[poly_countClick] = event->pos();
        poly_countClick++;
        countClick++;
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAWING;

    }
        break;
    }
}
// 鼠标释放事件捕获器
void CPolygon::mouseReleaseEvent(QMouseEvent *event)
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
// 鼠标移动事件捕获器
void CPolygon::mouseMoveEvent(QMouseEvent* event)
{
    int i = 0;
    switch(CDrawWin::m_curDrawStatus){
    case CDrawWin::DRAW_STATUS_NONE:
        break;
    case CDrawWin::DRAW_STATUS_DRAWING:
    {\
        qDebug() << __func__<<"count = "<<poly_countClick;
        // 设置第n个点
        m_ptArray[poly_countClick] = event->pos();
    }
        break;
    case CDrawWin::DRAW_STATUS_DRAG:
    {
        QPoint spanPt = event->pos() - m_lastPt;
        for(i = 0;i < m_ptArray.size();i++) {
            m_ptArray[i] += spanPt;
        }
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
