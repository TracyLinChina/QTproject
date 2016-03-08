#ifndef __POLYGON_H__
#define __POYYGON_H__
#include "Shape.h"


class CPolygon:public CShape
{
public:
    CPolygon();

public:
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

    enum CHANGE_DRAG{
        C_NULL = 0,
        CHANGE,
        DRAG
    };

public:
    static unsigned char D_or_C;
    double poly_area;
    double poly_perimter;
    static int poly_countClick;
    int p_countClick;
    QPen poly_info_pen;

};




#endif
