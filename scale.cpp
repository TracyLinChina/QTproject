#include "scale.h"
#include "MainWindow.h"
#include "scaleInfo.h"


CScale::CScale()
{
    unit = "Inch";
    name = "Scale";
    Sx = 0;
    m_ptArray.push_back(QPoint(20,50));
    m_ptArray.push_back (QPoint(20,70));
    m_ptArray.push_back(QPoint(20,60));
    m_ptArray.push_back(QPoint(120,60));
    m_ptArray.push_back(QPoint(120,50));
    m_ptArray.push_back(QPoint(120,70));
    length = (double)(m_ptArray[4].x() - m_ptArray[0].x());
}


void CScale::drawShape(QPainter &pt)
{
    QPainterPath path;
    scale_pen.setColor(Qt::red);
    scale_pen.setWidth(5);
    pt.setPen(scale_pen);
    path.moveTo(m_ptArray[0]);
    path.lineTo(m_ptArray[1]);
    path.moveTo(m_ptArray[2]);
    path.lineTo(m_ptArray[3]);
    path.moveTo(m_ptArray[4]);
    path.lineTo(m_ptArray[5]);
    pt.drawPath(path);
}

void CScale::drawInfo(QPainter &Pt)
{

    QString str_len;
    int x = m_ptArray[3].x();
    m_ptArray[3].setX(x+Sx);
    m_ptArray[4].setX(x+Sx);
    m_ptArray[5].setX(x+Sx);
    Sx = 0;

    str_len.setNum(length);
    QFontMetrics fm(myFont);
    int width = 0;
    int width1 = 0;
    int width2 = 0;
    int height = 0;
    width = fm.width(name);
    width1 = fm.width(str_len);
    width2 = fm.width(unit)*2;
    height = fm.height()*2;

    QRect rectScale(m_ptArray[0].x()+10,m_ptArray[0].y()-20,width+width1+width2,height);
    Pt.drawText(rectScale,Qt::AlignCenter,QString("%1:%2%3").arg(name).arg(length).arg(unit));
}

void CScale::HitTest(QMouseEvent *event, bool &bHit)
{
    bHit = false;
    QRect hitRect(m_ptArray[0],m_ptArray[5]);

    if(hitRect.contains(event->pos())) {
        bHit = true;
    }
}

void CScale::HitCtrlTest(QMouseEvent *event, bool &bCtrlHit)
{
    bCtrlHit = false;
}

void CScale::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton) {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        CscaleInfo dlgInfo;
        double tmp = 0;
        tmp = length;
        dlgInfo.te_Info->setText(QString("Name:%1\nLength:%2\nUnit:%3").arg(name).arg(length).arg(unit));
        switch(dlgInfo.exec()){
        case QDialog::Accepted:
        {
            if(dlgInfo.le_name->text() != NULL) {
                name = dlgInfo.le_name->text();
            }
            if(dlgInfo.le_len->text() != NULL) {
                Sx = dlgInfo.le_len->text().toDouble() - tmp;
                length = dlgInfo.le_len->text().toDouble();
            }
            if(dlgInfo.le_unit->text() != NULL) {
                unit = dlgInfo.le_unit->text();
            }
            myFont = QFont(dlgInfo.str_font);
        }
            break;
        case QDialog::Rejected:
        {

        }
            break;
        }
    } else {
        CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_DRAG;
        m_lastPt = event->pos();
    }
}
// 鼠标释放事件捕获器
void CScale::mouseReleaseEvent(QMouseEvent *event)
{
    CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
// 鼠标移动事件捕获器
void CScale::mouseMoveEvent(QMouseEvent* event)
{
    int i = 0;
    switch(CDrawWin::m_curDrawStatus) {
    case CDrawWin::DRAW_STATUS_DRAG:
    {
        QPoint spanPt = event->pos() - m_lastPt;
        for(i = 0;i < m_ptArray.size();i++) {
            m_ptArray[i] += spanPt;
        }

        m_lastPt = event->pos();
    }
        break;
    default:
        break;
    }
}



