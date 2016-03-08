#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Shape.h"

class CRect:public CShape
{
public:
    CRect();

public:
    void drawShape(QPainter &pt);

    void drawInfo(QPainter &Pt);
    //碰撞
    void HitTest(QMouseEvent *event,bool &bHit);
    void HitCtrlTest(QMouseEvent *event,bool &bCtrlHit);
    // 鼠标按下捕获器
    virtual void mousePressEvent(QMouseEvent* event);
    // 鼠标释放事件捕获器
    virtual void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动事件捕获器
    virtual void mouseMoveEvent(QMouseEvent* event);

public:
    double rectLength;
    double rectWidth;
    double rectArea;
    double rectPerimeter;
    QPen rect_info_pen;
};



#endif
