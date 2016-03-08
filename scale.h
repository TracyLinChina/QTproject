#ifndef __SCALE_H__
#define __SCALE_H__

#include "Shape.h"

class CScale:public CShape
{
public:
    CScale();

public:
    void drawShape(QPainter &pt);
    void drawInfo(QPainter &Pt);
    void HitTest(QMouseEvent *event, bool &bHit);
    void HitCtrlTest(QMouseEvent *event, bool &bCtrlHit);
    virtual void mousePressEvent(QMouseEvent* event);
    // 鼠标释放事件捕获器
    virtual void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动事件捕获器
    virtual void mouseMoveEvent(QMouseEvent* event);


public:
    double length;
    QString unit;
    QString name;
    QFont myFont;
    double Sx;
    int Sy;
};


#endif
