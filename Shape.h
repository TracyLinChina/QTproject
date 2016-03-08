#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <QtGui>

class CShape
{
public:
    CShape();

public:
    // 画图形
    virtual void drawShape(QPainter &pt) = 0;
    virtual void drawInfo(QPainter &Pt) = 0;
    //碰撞
    virtual void HitTest(QMouseEvent *event,bool &bHit) = 0;
    virtual void HitCtrlTest(QMouseEvent *event,bool &bCtrlHit) = 0;
    // 鼠标按下捕获器
    virtual void mousePressEvent(QMouseEvent* event){}
    // 鼠标释放事件捕获器
    virtual void mouseReleaseEvent(QMouseEvent *event){}
    // 鼠标移动事件捕获器
    virtual void mouseMoveEvent(QMouseEvent* event){}

    void save(QSettings &fd);

public:
    QPen m_hitPen;
//    QColor m_curColor;
    // 画笔
    QPen m_pen;
    QPen circle_pen;
    QPen rect_pen;
    QPen poly_pen;
    QPen angle_pen;
    QPen scale_pen;
    // 画刷
    QBrush  m_brush;
    // 点的动态数组
    QVector<QPoint> m_ptArray;
    int countClick;
    QPoint m_lastPt;
    int m_ctrlIndex;
    int m_shapeIndex;
    unsigned char m_shapeType;
    static int m_shapeCount;

};


#endif
