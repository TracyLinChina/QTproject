#ifndef __ANGLE_H__
#define __ANGLE_H__

#include "Shape.h"

class CAngle:public CShape
{
public:
    CAngle();

    void drawShape(QPainter &pt);
    void drawInfo(QPainter &Pt);
    //碰撞
    void HitTest(QMouseEvent *event,bool &bHit);
    void HitCtrlTest(QMouseEvent *event,bool &bCtrlHit);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

public:
    double angle;
    QPen ang_info_pen;
};


#endif
