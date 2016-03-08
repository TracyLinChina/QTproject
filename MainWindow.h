#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "ui_MainWindow.h"
#include "Shape.h"
#include <QtGui>

class CDockWin;

class CDrawWin:public QMainWindow,
               public Ui_Mainwin
{
    Q_OBJECT
public:
    CDrawWin(QWidget *parent = NULL);

    // 画图状态定义
    enum DRAW_STATUS{
        // 无画图状态
        DRAW_STATUS_NONE = 0,
        // 绘画当中
        DRAW_STATUS_DRAWING,
        // 移动
        DRAW_STATUS_DRAG,
        // 改变图元
        DRAW_STATUS_CHANGE
    };


    // 当前的菜单选择
    enum MENU_STATUS{
        // 无画图菜单
        MENU_STATUS_NONE = 0,
        // 画直线菜单
        MENU_STATUS_LINE,
        // 画圆菜单
        MENU_STATUS_CIRCLE,
        // 画矩形菜单
        MENU_STATUS_RECTANGE,
        MENU_STATUS_POLYGON,
        MENU_STATUS_ANGLE,
        MENU_STATIS_DEL
    };

     //定义当前创建的图形
    enum SHAPE_STATUS{
        SHAPE_NONE = 0,
        SHAPE_LINE,
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_POLYGON,
        SHAPE_ANGLE,
        SHAPE_SCALE
    };
public:
    //碰撞
    CShape *HitTest(QMouseEvent *event,bool &bHit,bool &bCtrlHit);
    //画图
    void paintEvent(QPaintEvent *event);
    void process_line(QMouseEvent *event);
    void process_circle(QMouseEvent *event);
    void process_rectangle(QMouseEvent *event);
    void process_polygon(QMouseEvent *event);
    void process_angle(QMouseEvent *event);
    // 鼠标按下捕获器
    void mousePressEvent(QMouseEvent* event);
    // 鼠标释放事件捕获器
    void mouseReleaseEvent(QMouseEvent *event);
    // 鼠标移动事件捕获器
    void mouseMoveEvent(QMouseEvent* event);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

    void timerEvent(QTimerEvent *event);
public slots:
    void on_acOpen_triggered();
    void on_acDrawLine_triggered();
    void on_acDrawCircle_triggered();
    void on_acDrawRectange_triggered();
    void on_acSelect_triggered();
    void on_acSet_color_triggered();
    void on_acDrawPolygon_triggered();
    void on_acDrawAngle_triggered();
    void on_ac_Save_triggered();
    void on_ac_New_triggered();
    void on_acImage_triggered();
    void on_acDelete_triggered();
    void on_acSaveImage_triggered();
public:
    static int countShape;
    static int widLine;
    static unsigned char m_curMenuStatus;
    static unsigned char m_curDrawStatus;
    static unsigned char m_curShapestatus;
    QVector<CShape *> m_shapeList;
    QVector<QColor>m_colorList;
    QVector<unsigned char> m_shapeStatus;
    CShape *m_curShape;
    static CShape *m_tmp;
    static QColor m_hitCol;
    static QColor m_curCol;
    static QColor m_CirCol;
    static QColor m_RectCol;
    static QColor m_PolyCol;
    static QColor m_AngCol;
    static QColor m_tmpCol;
    static unsigned int color_Count;
    static unsigned int shape_Count;
    QLabel *m_time;
    QLabel *m_timeText;
    QDockWidget *m_dock;
    CDockWin *m_widget;
    bool maybeSave;
    QImage *m_image;
    QPixmap pixmap;
    bool delet_image;
};



#endif
