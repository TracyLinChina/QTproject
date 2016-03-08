#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Shape.h"

class CCircle:public CShape
{
public:
    CCircle();
    void drawShape(QPainter &pt);
    void drawInfo(QPainter &Pt);
    void HitTest(QMouseEvent *event,bool &bHit);
    void HitCtrlTest(QMouseEvent *event, bool &bCtrlHit);
    // 鼠标按下捕获器
    virtual void mousePressEvent(QMouseEvent* event);
    // 鼠标释放事件捕获器
    virtual void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动事件捕获器
    virtual void mouseMoveEvent(QMouseEvent* event);
public:
    double m_radium;
    double m_area;
    double m_perimeter;
    QPen cir_info_pen;
};




#endif
