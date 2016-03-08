#ifndef __CLINE_H__
#define __CLINE_H__
#include "Shape.h"

class CLine:public CShape
{
public:
    CLine();

public:
    // 实现自己的图形
    void drawShape(QPainter &pt);
    void drawInfo(QPainter &pt);

    //碰撞
    void HitTest(QMouseEvent *event,bool &bHit);
    void HitCtrlTest(QMouseEvent *event, bool &bCtrlHit);
    // 鼠标按下捕获器
    virtual void mousePressEvent(QMouseEvent* event);
    // 鼠标释放事件捕获器
    virtual void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动事件捕获器
    virtual void mouseMoveEvent(QMouseEvent* event);


public:
    double m_length;
    QPen infoPen;
};





#endif
