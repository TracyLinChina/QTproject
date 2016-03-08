#include "Cline.h"
#include <math.h>
#include "MainWindow.h"


CLine::CLine()
{
    m_length = 0;
    m_hitPen.setColor(Qt::red);
    m_hitPen.setWidth(5);
    infoPen.setColor(Qt::blue);
    infoPen.setWidth(3);

    m_shapeType = CDrawWin::SHAPE_LINE;
}


void CLine::drawShape(QPainter &pt)
{
    //    qDebug() << __func__ << " " <<__LINE__ << "CLIne";
    QPoint ltPt_0(m_ptArray[0].x()-2,m_ptArray[0].y()-2);
    QPoint rbPt_0(m_ptArray[0].x()+2,m_ptArray[0].y()+2);
    QPoint ltPt_1(m_ptArray[1].x()-2,m_ptArray[1].y()-2);
    QPoint rbPt_1(m_ptArray[1].x()+2,m_ptArray[1].y()+2);
    QRect rec_0(ltPt_0,rbPt_0);
    QRect rec_1(ltPt_1,rbPt_1);
    pt.setPen(m_hitPen);
    pt.drawRect(rec_0);
    pt.drawRect(rec_1);
    pt.setPen(m_pen);
    pt.drawLine(m_ptArray[0],m_ptArray[1]);
}


void CLine::drawInfo(QPainter &pt)
{
    QPoint midPt = ((m_ptArray[0] + m_ptArray[1]))/2;
    QString str;
    QString str_1 = " Length:";
    QFont myFont;

    QFontMetrics fm(myFont);

    int width = 0;
    int width_1 = 0;
    int height = 0;

    m_length = sqrt(pow(m_ptArray[0].x()-m_ptArray[1].x(),2)+pow(m_ptArray[0].y()-m_ptArray[1].y(),2));

    str.setNum(m_length);
    midPt += QPoint(10,-5);
    width = fm.width(str);
    width_1 = fm.width(str_1);
    height = fm.height() * 3;
    QRect infoRect(midPt.x(),midPt.y(),width + width_1,height);

    pt.setPen(infoPen);
    pt.drawRoundedRect(infoRect,5,5);
    pt.drawText(infoRect,Qt::AlignCenter,QString("%1\n%2%3").arg(" Type:Line ").arg("Length:").arg(m_length));

}

void CLine::mousePressEvent(QMouseEvent *event)
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

void CLine::mouseReleaseEvent(QMouseEvent *event)
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

//鼠标移动
void CLine::mouseMoveEvent(QMouseEvent *event)
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
        qDebug() << __LINE__;
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


void CLine::HitCtrlTest(QMouseEvent *event,bool &bCtrlHit)
{
    bCtrlHit = false;
    int i = 0;
    for(i = 0;i < m_ptArray.size();i++) {
        QPoint ptLt(m_ptArray[i].x() - 5,m_ptArray[i].y() - 5);
        QPoint ptRb(m_ptArray[i].x() + 5,m_ptArray[i].y() + 5);
        QRect recTest(ptLt,ptRb);
        if(recTest.contains(event->pos())) {
            bCtrlHit = true;
            m_ctrlIndex = i;
            qDebug() << "LINE" << __LINE__;
            break;
        } else {
            m_ctrlIndex = -1;
        }
    }
}

void CLine::HitTest(QMouseEvent *event,bool &bHit)
{
    bHit = false;
    double k = 0,b = 0;
    int flag = 0;
    if(m_ptArray[0].x() < m_ptArray[1].x()) {
        if(event->pos().x() > m_ptArray[0].x() && event->pos().x() < m_ptArray[1].x()){
            k = ((double)(m_ptArray[1].y() - m_ptArray[0].y())/(double)(m_ptArray[1].x() - m_ptArray[0].x()));
            b = m_ptArray[0].y() - k*m_ptArray[0].x();

            flag = (event->pos().y() - k*event->pos().x());
            if(flag < b+10 && flag > b-10) {
                bHit = true;
            }
        } else {
            bHit = false;
        }
    }else if(m_ptArray[0].x() > m_ptArray[1].x()) {
        if(event->pos().x() < m_ptArray[0].x() && event->pos().x() > m_ptArray[1].x()) {
            k = ((double)(m_ptArray[1].y() - m_ptArray[0].y())/(double)(m_ptArray[1].x() - m_ptArray[0].x()));
            b = m_ptArray[0].y() - k*m_ptArray[0].x();

            flag = (event->pos().y() - k*event->pos().x());
            if(flag < b+10 && flag > b-10) {
                bHit = true;
            }
        } else {
            bHit = false;
        }
    } else if(m_ptArray[0].x() == m_ptArray[1].x()){
        QPoint ptLt(m_ptArray[0].x() - 5,m_ptArray[0].y());
        QPoint ptRb(m_ptArray[1].x() + 5,m_ptArray[1].y());
        QRect recTest(ptLt,ptRb);
        if(recTest.contains(event->pos())) {
            bHit = true;
        }
    }
}



