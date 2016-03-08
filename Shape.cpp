#include "Shape.h"
#include "MainWindow.h"

int CShape::m_shapeCount = 0;
//double CShape::scale_length = 0;

CShape::CShape()
{
    countClick = 0;
    m_ctrlIndex = -1;

    m_shapeIndex = m_shapeCount++;
    qDebug() << __func__<<m_pen.color().red();
}


void CShape::save(QSettings &fd)
{
    int i = 0;
    QString groupN = QString("shape-%1").arg(m_shapeIndex);

    fd.setValue(QString("%1/type").arg(groupN),m_shapeType);

    fd.setValue(QString("%1/ptNumber").arg(groupN),countClick);
    for(i = 0;i != m_ptArray.size();i++){
        fd.setValue(QString("%1/pt%2").arg(groupN).arg(i),m_ptArray[i]);
    }
    switch(m_shapeType) {
    case CDrawWin::SHAPE_LINE:
    {
        fd.setValue(QString("%1/shapeColorRed").arg(groupN),m_pen.color().red());
        fd.setValue(QString("%1/shapeColorGreen").arg(groupN),m_pen.color().green());
        fd.setValue(QString("%1/shapeColorBlue").arg(groupN),m_pen.color().blue());
        fd.setValue(QString("%1/shapePenwidth").arg(groupN),m_pen.width());
        qDebug() << fd.value(QString("%1/shapeColorRed").arg(groupN));
    }
        break;
    case CDrawWin::SHAPE_RECTANGLE:
    {
        fd.setValue(QString("%1/shapeColorRed").arg(groupN),rect_pen.color().red());
        fd.setValue(QString("%1/shapeColorGreen").arg(groupN),rect_pen.color().green());
        fd.setValue(QString("%1/shapeColorBlue").arg(groupN),rect_pen.color().blue());
        fd.setValue(QString("%1/shapePenwidth").arg(groupN),rect_pen.width());
    }
        break;
    case CDrawWin::SHAPE_CIRCLE:
    {
        fd.setValue(QString("%1/shapeColorRed").arg(groupN),circle_pen.color().red());
        fd.setValue(QString("%1/shapeColorGreen").arg(groupN),circle_pen.color().green());
        fd.setValue(QString("%1/shapeColorBlue").arg(groupN),circle_pen.color().blue());
        fd.setValue(QString("%1/shapePenwidth").arg(groupN),circle_pen.width());
    }
        break;
    case CDrawWin::SHAPE_ANGLE:
    {
        fd.setValue(QString("%1/shapeColorRed").arg(groupN),angle_pen.color().red());
        fd.setValue(QString("%1/shapeColorGreen").arg(groupN),angle_pen.color().green());
        fd.setValue(QString("%1/shapeColorBlue").arg(groupN),angle_pen.color().blue());
        fd.setValue(QString("%1/shapePenwidth").arg(groupN),angle_pen.width());
    }
        break;
    case CDrawWin::SHAPE_POLYGON:
    {
        fd.setValue(QString("%1/shapeColorRed").arg(groupN),poly_pen.color().red());
        fd.setValue(QString("%1/shapeColorGreen").arg(groupN),poly_pen.color().green());
        fd.setValue(QString("%1/shapeColorBlue").arg(groupN),poly_pen.color().blue());
        fd.setValue(QString("%1/shapePenwidth").arg(groupN),poly_pen.width());
    }
        break;
    }
}
