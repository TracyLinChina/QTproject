#include "MainWindow.h"
#include "Cline.h"
#include "circle.h"
#include "rectangle.h"
#include "polygon.h"
#include "Angle.h"
#include <QDebug>
#include "mod.h"
#include "DockWin.h"
#include "scale.h"

unsigned char CDrawWin::m_curDrawStatus = CDrawWin::DRAW_STATUS_NONE;
unsigned char CDrawWin::m_curMenuStatus = CDrawWin::MENU_STATUS_NONE;
unsigned char CDrawWin::m_curShapestatus = CDrawWin::SHAPE_NONE;
int CDrawWin::countShape = 0;
int CDrawWin::widLine = 5;
CShape* CDrawWin::m_tmp = NULL;
QColor CDrawWin::m_tmpCol(0,0,0);
unsigned int CDrawWin::color_Count = 0;
unsigned int CDrawWin::shape_Count = 0;
QColor CDrawWin::m_curCol(0,0,0);
QColor CDrawWin::m_CirCol(0,0,0);
QColor CDrawWin::m_hitCol(0,0,0);
QColor CDrawWin::m_RectCol(0,0,0);
QColor CDrawWin::m_PolyCol(0,0,0);
QColor CDrawWin::m_AngCol(0,0,0);


CDrawWin::CDrawWin(QWidget *parent)
    :QMainWindow(parent)
{
    setupUi(this);
    m_curShape = NULL;
    maybeSave = false;
    m_image = NULL;
    m_timeText = new QLabel(tr("Time:"));
    m_time = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    statusBar()->addPermanentWidget(m_timeText);
    statusBar()->addPermanentWidget(m_time);

    startTimer(1000);
    delet_image = false;
    m_dock = new QDockWidget(tr("DockWidget2"),this);
    m_widget = new CDockWin;

    m_dock->setWidget(m_widget);

    m_dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_dock->setAllowedAreas(Qt::RightDockWidgetArea);

    m_dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->addDockWidget(Qt::RightDockWidgetArea,m_dock);

    showMaximized();

    centralwidget->setMouseTracking(true);
    this->setMouseTracking(true);
    qDebug()<<__LINE__;

    m_curShape = new CScale;
    m_curShapestatus = SHAPE_SCALE;
    m_shapeStatus.push_back(m_curShapestatus);
    m_shapeList.push_back(m_curShape);
    m_colorList.push_back(m_curShape->scale_pen.color());

}

void CDrawWin::on_acSaveImage_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save Doucument"),
                                                    "",
                                                    tr("*.png;; *.jpg")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else {
        pixmap.save(filename);
        maybeSave = true;
    }
}


void CDrawWin::closeEvent(QCloseEvent *event)
{
    if (!maybeSave&&(m_shapeList.size() > 1)) {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        switch(msgBox.exec()){
        case QMessageBox::Save:
        {
            event->ignore();
        }
            break;
        case QMessageBox::Discard:
        {
            event->accept();
        }
            break;
        case QMessageBox::Cancel:
        {
            event->ignore();
        }
            break;

        }
    } else {
        event->accept();
    }
}

void CDrawWin::timerEvent(QTimerEvent *event)
{
    m_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void CDrawWin::on_acOpen_triggered()
{
    int lodeType;
    int i = 0;
    int ptCount = 0;
    QStringList keys;
    QString file_name = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("*.ini;;*.txt"));
    if (!file_name.isNull())
    {
        QSettings fd(file_name, QSettings::IniFormat);
        keys = fd.childGroups();
        for(i = 0;i < keys.size();i++) {
            lodeType = fd.value(QString("%1/type").arg(keys[i])).toInt();
            switch(lodeType){
            case SHAPE_LINE:
            {
                m_curShape = new CLine;
                qDebug() << "test" <<fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt();
                m_curCol.setRgb(fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorGreen").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorBlue").arg(keys[i])).toInt());

                m_curShape->m_pen.setWidth(fd.value(QString("%1/shapePenwidth").arg(keys[i])).toInt());
                m_curShape->m_pen.setColor(m_curCol);
                for(ptCount = 0;ptCount < fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();ptCount++) {
                    m_curShape->m_ptArray.push_back(fd.value(QString("%1/pt%2").arg(keys[i]).arg(ptCount)).toPoint());
                }

                m_shapeList.push_back(m_curShape);
                m_colorList.push_back(m_curCol);
                m_curShape->countClick = fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();
                update();
            }
                break;
            case SHAPE_ANGLE:
            {
                m_curShape = new CAngle;
                m_AngCol.setRgb(fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorGreen").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorBlue").arg(keys[i])).toInt());

                m_curShape->angle_pen.setWidth(fd.value(QString("%1/shapePenwidth").arg(keys[i])).toInt());
                m_curShape->angle_pen.setColor(m_AngCol);
                for(ptCount = 0;ptCount < fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();ptCount++) {
                    m_curShape->m_ptArray.push_back(fd.value(QString("%1/pt%2").arg(keys[i]).arg(ptCount)).toPoint());
                }
                m_shapeList.push_back(m_curShape);
                m_colorList.push_back(m_AngCol);
                m_curShape->countClick = fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();
                update();
            }
                break;
            case SHAPE_CIRCLE:
            {
                m_curShape = new CCircle;
                m_CirCol.setRgb(fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorGreen").arg(keys[i])).toInt(),
                                fd.value(QString("%1/shapeColorBlue").arg(keys[i])).toInt());
                for(ptCount = 0;ptCount < fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();ptCount++) {
                    m_curShape->m_ptArray.push_back(fd.value(QString("%1/pt%2").arg(keys[i]).arg(ptCount)).toPoint());
                }
                m_curShape->circle_pen.setWidth(fd.value(QString("%1/shapePenwidth").arg(keys[i])).toInt());
                m_curShape->circle_pen.setColor(m_CirCol);
                m_shapeList.push_back(m_curShape);
                m_colorList.push_back(m_CirCol);
                m_curShape->countClick = fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();
                update();
            }
                break;
            case SHAPE_RECTANGLE:
            {
                m_curShape = new CRect;
                m_RectCol.setRgb(fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt(),
                                 fd.value(QString("%1/shapeColorGreen").arg(keys[i])).toInt(),
                                 fd.value(QString("%1/shapeColorBlue").arg(keys[i])).toInt());
                m_curShape->rect_pen.setWidth(fd.value(QString("%1/shapePenwidth").arg(keys[i])).toInt());
                m_curShape->rect_pen.setColor(m_RectCol);
                for(ptCount = 0;ptCount < fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();ptCount++) {
                    m_curShape->m_ptArray.push_back(fd.value(QString("%1/pt%2").arg(keys[i]).arg(ptCount)).toPoint());
                }
                m_shapeList.push_back(m_curShape);
                m_colorList.push_back(m_RectCol);
                m_curShape->countClick = fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();
                update();
            }
                break;
            case SHAPE_POLYGON:
            {
                m_curShape = new CPolygon;
                m_PolyCol.setRgb(fd.value(QString("%1/shapeColorRed").arg(keys[i])).toInt(),
                                 fd.value(QString("%1/shapeColorGreen").arg(keys[i])).toInt(),
                                 fd.value(QString("%1/shapeColorBlue").arg(keys[i])).toInt());
                m_curShape->poly_pen.setWidth(fd.value(QString("%1/shapePenwidth").arg(keys[i])).toInt());
                m_curShape->poly_pen.setColor(m_PolyCol);
                for(ptCount = 0;ptCount < fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();ptCount++) {
                    m_curShape->m_ptArray.push_back(fd.value(QString("%1/pt%2").arg(keys[i]).arg(ptCount)).toPoint());
                }
                m_shapeList.push_back(m_curShape);
                m_colorList.push_back(m_PolyCol);
                m_curShape->countClick = fd.value(QString("%1/ptNumber").arg(keys[i])).toInt();
                update();
            }
                break;

            }
        }
    }
    else{
        return;
    }
}

void CDrawWin::on_acDelete_triggered()
{
    if(m_shapeList.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("No shape.                                 ");
        msgBox.exec();
    }else {
        m_curMenuStatus = CDrawWin::MENU_STATIS_DEL;
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }
}

void CDrawWin::on_acImage_triggered()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty()){
        return;
    }
    else {
        m_image = new QImage;

        if(! ( m_image->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete m_image;
            return;
        }
    }
}

void CDrawWin::on_ac_New_triggered()
{
    if(maybeSave|| m_shapeList.size() == 1) {
        CShape *m_tmp;
        m_tmp = m_shapeList[0];
        m_shapeList.clear();
        m_shapeList.push_back(m_tmp);
        update();
    }else {
        QMessageBox msgBox;
        msgBox.setText("The document has not been saved.");
        msgBox.setInformativeText("Do you want to save the document or just drop it?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        switch(msgBox.exec()) {
        case QMessageBox::Save:
        {
            QString filename = QFileDialog::getSaveFileName(this,
                                                            tr("Save Doucument"),
                                                            "",
                                                            tr("*.ini;; *.txt;;*.jpg;;*.png")); //选择路径
            if(filename.isEmpty())
            {
                return;
            }
            else {
                QSettings fd(filename,QSettings::IniFormat);
                QVector<CShape*>::iterator it = m_shapeList.begin();
                for(;it != m_shapeList.end();it++) {
                    (*it)->save(fd);
                }
                CShape *m_tmp;
                m_tmp = m_shapeList[0];
                m_shapeList.clear();
                m_shapeList.push_back(m_tmp);
                update();
            }
            maybeSave = true;
        }
            break;
        case QMessageBox::Discard:
        {
            if(m_shapeList.isEmpty()) {
                break;
            }else {
                CShape *m_tmp;
                m_tmp = m_shapeList[0];
                m_shapeList.clear();
                m_shapeList.push_back(m_tmp);
                update();
            }
        }
            break;
        default:
            break;
        }
    }
    maybeSave = false;
}

void CDrawWin::on_acDrawLine_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_LINE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
}
void CDrawWin::on_acDrawCircle_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_CIRCLE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
}
void CDrawWin::on_acDrawRectange_triggered()
{

    m_curMenuStatus = CDrawWin::MENU_STATUS_RECTANGE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
}
void CDrawWin::on_acDrawPolygon_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_POLYGON;
    QApplication::setOverrideCursor(Qt::CrossCursor);
}
void CDrawWin::on_acDrawAngle_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_ANGLE;
    QApplication::setOverrideCursor(Qt::CrossCursor);
}
void CDrawWin::on_acSelect_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_NONE;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
void CDrawWin::on_acSet_color_triggered()
{
    m_curMenuStatus = CDrawWin::MENU_STATUS_NONE;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QPalette palette = this->palette();
    const QColor& color
            = QColorDialog::getColor(palette.color(QPalette::Base), this);
    if(color.isValid())
    {
        palette.setColor(QPalette::Base, color);
        this->setPalette(palette);
    }
    m_curCol = m_CirCol = m_RectCol = m_PolyCol = m_AngCol = color;

}


void CDrawWin::on_ac_Save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save Doucument"),
                                                    "",
                                                    tr("*.ini;; *.txt")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else {
        QSettings fd(filename,QSettings::IniFormat);
        QVector<CShape*>::iterator it = m_shapeList.begin();
        for(;it != m_shapeList.end();it++) {
            (*it)->save(fd);
        }
        maybeSave = true;
    }
}



void CDrawWin::paintEvent(QPaintEvent *event)
{

    if(m_image == NULL) {
        QPainter pt(this);
        QVector<CShape *>::iterator it = m_shapeList.begin();
        for(;it != m_shapeList.end();it++) {
            (*it)->drawShape(pt);
            (*it)->drawInfo(pt);
        }
    } else {
        QPainter pt(this);
        QImage image = *m_image;
        pixmap = QPixmap::fromImage(image.scaled(size(), Qt::IgnoreAspectRatio));
        // 缓存画家
        QPainter pt_image(&pixmap);
        QVector<CShape *>::iterator it = m_shapeList.begin();
        for(; it != m_shapeList.end(); it++){
            // 画图形
            (*it)->drawShape(pt_image);
            // 画信息
            (*it)->drawInfo(pt_image);
        }
        pt.drawPixmap(0,0,pixmap);
    }

}

// 鼠标按下捕获器
void CDrawWin::mousePressEvent(QMouseEvent* event)
{
    switch(m_curMenuStatus) {
    case MENU_STATUS_NONE:
    {
        qDebug() << __func__ << " " << __LINE__ ;
        bool bHit,bCtrlHit;
        m_curShape = HitTest(event,bHit,bCtrlHit);
        if(m_curShape != NULL) {
            if(bCtrlHit) {
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
            }else {
                if(bHit) {
                    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
                }
            }

            m_curShape->mousePressEvent(event);
        }

    }
        break;
    case MENU_STATUS_LINE:
    {
        process_line(event);
    }
        break;
    case MENU_STATUS_CIRCLE:
    {
        process_circle(event);
    }
        break;
    case MENU_STATUS_RECTANGE:
    {
        qDebug() << __func__ << " " << __LINE__ ;
        process_rectangle(event);
    }
        break;
    case MENU_STATUS_POLYGON:
    {
        qDebug() << __func__ << " " << __LINE__ ;
        process_polygon(event);
    }
        break;
    case MENU_STATUS_ANGLE:
    {
        process_angle(event);
    }
        break;
    case MENU_STATIS_DEL:
    {
        bool bHit,bCtrlHit;
        m_curShape = HitTest(event,bHit,bCtrlHit);
        if(m_curShape != NULL) {
            if(m_curShape == m_shapeList[0]) {
                QMessageBox msgBox;
                msgBox.setText("Can not delete the scale.");
                msgBox.exec();
                break;
            }
            if(bHit) {
                if(m_curShape == m_shapeList[m_shapeList.size() - 1]) {
                    m_shapeList.pop_back();
                    QApplication::setOverrideCursor(Qt::ArrowCursor);
                    update();
                }else {
                    QVector<CShape*>::iterator it = m_shapeList.begin();
                    for(;it != m_shapeList.end();it++) {
                        if((*it) == m_curShape) {
                            m_shapeList.erase(it);
                            QApplication::setOverrideCursor(Qt::ArrowCursor);
                            update();
                        }
                    }
                }
            }
        }
    }
        break;
    }
}
// 鼠标释放事件捕获器
void CDrawWin::mouseReleaseEvent(QMouseEvent *event)
{

    switch (m_curMenuStatus) {

    case MENU_STATUS_NONE:
    {
        if(m_curShape != NULL) {

            m_curShape->mouseReleaseEvent(event);
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
    }
        break;
    case MENU_STATUS_LINE:
    {

    }
        break;
    default:
        break;
    }
}

void CDrawWin::mouseMoveEvent(QMouseEvent* event)
{

    // 判断当前菜单状态

    switch(m_curMenuStatus)
    {
    case MENU_STATUS_NONE:
    {
        switch(m_curDrawStatus)
        {
        case DRAW_STATUS_DRAG:
        case DRAW_STATUS_CHANGE:
        {
            m_curShape->mouseMoveEvent(event);
            update();
        }
            break;
        default:
        {
            bool bHit,bCtlHit;
            m_curShape = HitTest(event,bHit,bCtlHit);
            if(m_curShape != NULL)
            {
                if(bCtlHit)
                {

                    m_tmp = m_curShape;
                    //                    switch(SHA)
                    m_curShape->m_pen.setColor(m_hitCol);
                    update();
                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                }
                else
                {
                    if(bHit)
                    {
                        qDebug()<<"size = " <<m_shapeList.size()<<" " << m_shapeList.indexOf(m_curShape);
                        QApplication::setOverrideCursor(Qt::OpenHandCursor);
                        qDebug() << __LINE__;
                    }

                }
            }
            else
            {
                if(m_tmp != NULL) {
                    m_shapeList[shape_Count]->m_pen.setColor(m_colorList[color_Count]);
                    update();
                }
                QApplication::setOverrideCursor(Qt::ArrowCursor);
            }
        }
            break;
        }
    }
        break;
    default:
    {
        if(m_curDrawStatus != DRAW_STATUS_NONE)
        {
            // 非无画图状态，我们才处理移动事件
            if(m_curShape != NULL)
            {
                // 把事件传递给具体图元
                m_curShape->mouseMoveEvent(event);
                update();
            }
        }

    }

        break;
    }

}


//直线处理
void CDrawWin::process_line(QMouseEvent *event)
{

    switch(m_curDrawStatus){
    case DRAW_STATUS_NONE:
    {
        m_curShape = new CLine;
        m_curShape->m_pen.setColor(m_curCol);
        m_curShape->m_pen.setWidth(widLine);
        m_curShape->mousePressEvent(event);
        m_curShapestatus = SHAPE_LINE;
        m_shapeList.push_back(m_curShape);
        m_colorList.push_back(m_curCol);
        m_shapeStatus.push_back(m_curShapestatus);
        widLine = m_curShape->m_pen.width();
    }
        break;
    case DRAW_STATUS_DRAWING:
    {
        m_curShape->mousePressEvent(event);
    }
        break;
    default:
        break;
    }
    update();
}

void CDrawWin::process_circle(QMouseEvent *event)
{
    // 根据画图状态来判断
    switch(m_curDrawStatus)
    {
    case DRAW_STATUS_NONE:
    {
        m_curShape = new CCircle;
        m_curShape->circle_pen.setColor(m_CirCol);
        m_curShape->circle_pen.setWidth(widLine);
        m_curShape->mousePressEvent(event);
        m_curShapestatus = SHAPE_CIRCLE;
        m_shapeList.push_back(m_curShape);
        m_colorList.push_back(m_CirCol);
        m_shapeStatus.push_back(m_curShapestatus);
    }
        break;
    case DRAW_STATUS_DRAWING:
    {
        // 把事件传递下去
        m_curShape->mousePressEvent(event);
    }
        break;
    }
    update();
}


void CDrawWin::process_rectangle(QMouseEvent *event)
{
    // 根据画图状态来判断
    switch(m_curDrawStatus)
    {
    case DRAW_STATUS_NONE:
    {
        m_curShape = new CRect;
        m_curShape->rect_pen.setColor(m_RectCol);
        m_curShape->rect_pen.setWidth(widLine);
        m_curShape->mousePressEvent(event);
        m_curShapestatus = SHAPE_RECTANGLE;
        m_shapeList.push_back(m_curShape);
        m_colorList.push_back(m_RectCol);
        m_shapeStatus.push_back(m_curShapestatus);
        //        widLine = m_curShape->m_pen.width();
    }
        break;
    case DRAW_STATUS_DRAWING:
    {
        // 把事件传递下去
        m_curShape->mousePressEvent(event);
    }
        break;
    }
    update();
}

void CDrawWin::process_polygon(QMouseEvent *event)
{
    // 根据画图状态来判断
    switch(m_curDrawStatus)
    {
    case DRAW_STATUS_NONE:
    {
        m_curShape = new CPolygon;
        m_curShape->poly_pen.setColor(m_PolyCol);
        m_curShape->poly_pen.setWidth(widLine);
        m_curShape->mousePressEvent(event);
        m_curShapestatus = SHAPE_POLYGON;
        m_shapeList.push_back(m_curShape);
        m_colorList.push_back(m_PolyCol);
        m_shapeStatus.push_back(m_curShapestatus);
    }
        break;
    case DRAW_STATUS_DRAWING:
    {
        // 把事件传递下去
        m_curShape->mousePressEvent(event);
    }
        break;
    }
    update();
}

void CDrawWin::process_angle(QMouseEvent *event)
{
    switch(m_curDrawStatus)
    {
    case DRAW_STATUS_NONE:
    {
        m_curShape = new CAngle;
        m_curShape->angle_pen.setColor(m_AngCol);
        m_curShape->angle_pen.setWidth(widLine);
        m_curShape->mousePressEvent(event);
        m_curShapestatus = SHAPE_ANGLE;
        m_shapeList.push_back(m_curShape);
        m_colorList.push_back(m_AngCol);
        m_shapeStatus.push_back(m_curShapestatus);
    }
        break;
    case DRAW_STATUS_DRAWING:
    {
        // 把事件传递下去
        m_curShape->mousePressEvent(event);
    }
        break;
    }
    update();
}

void CDrawWin::mouseDoubleClickEvent(QMouseEvent *event)
{
    CMod mod_Dlg;
    if(MENU_STATUS_NONE == m_curMenuStatus) {
        bool bHit,bCtrlHit;
        m_curShape = HitTest(event,bHit,bCtrlHit);
        if(m_curShape != NULL) {
            qDebug()<< " xi" << __LINE__;
            m_curShapestatus = m_shapeStatus[shape_Count];
            qDebug()<< " xi" << __LINE__;
            switch(m_curShapestatus) {
            case SHAPE_LINE:
            {

                mod_Dlg.le_width->setText(QString("%1").arg(m_curShape->m_pen.width()));
                mod_Dlg.mod_color = m_curShape->m_pen.color();
                switch( mod_Dlg.exec()) {
                case QDialog::Accepted:
                {
                    m_curShape->m_pen.setWidth(mod_Dlg.le_width->text().toInt());
                    m_curShape->m_pen.setColor(mod_Dlg.mod_color);
                    m_colorList[color_Count] = mod_Dlg.mod_color;
                    update();
                }
                    break;
                case QDialog::Rejected:
                    break;
                }
            }
                break;
            case SHAPE_CIRCLE:
            {

                mod_Dlg.le_width->setText(QString("%1").arg(m_curShape->circle_pen.width()));
                mod_Dlg.mod_color = m_curShape->circle_pen.color();
                switch( mod_Dlg.exec()) {
                case QDialog::Accepted:
                {
                    m_curShape->circle_pen.setWidth(mod_Dlg.le_width->text().toInt());
                    m_curShape->circle_pen.setColor(mod_Dlg.mod_color);
                    m_colorList[color_Count] = mod_Dlg.mod_color;
                    update();
                }
                    break;
                case QDialog::Rejected:
                    break;
                }
            }
                break;
            case SHAPE_RECTANGLE:
            {


                mod_Dlg.le_width->setText(QString("%1").arg(m_curShape->rect_pen.width()));
                mod_Dlg.mod_color = m_curShape->rect_pen.color();
                switch( mod_Dlg.exec()) {
                case QDialog::Accepted:
                {
                    m_curShape->rect_pen.setWidth(mod_Dlg.le_width->text().toInt());
                    m_curShape->rect_pen.setColor(mod_Dlg.mod_color);
                    m_colorList[color_Count] = mod_Dlg.mod_color;
                    update();
                }
                    break;
                case QDialog::Rejected:
                    break;
                }
            }
                break;
            case SHAPE_POLYGON:
            {

                mod_Dlg.le_width->setText(QString("%1").arg(m_curShape->poly_pen.width()));
                mod_Dlg.mod_color = m_curShape->poly_pen.color();
                switch( mod_Dlg.exec()) {
                case QDialog::Accepted:
                {
                    m_curShape->poly_pen.setWidth(mod_Dlg.le_width->text().toInt());
                    m_curShape->poly_pen.setColor(mod_Dlg.mod_color);
                    m_colorList[color_Count] = mod_Dlg.mod_color;
                    update();
                }
                    break;
                case QDialog::Rejected:
                    break;
                }
            }
                break;
            case SHAPE_ANGLE:
            {

                mod_Dlg.le_width->setText(QString("%1").arg(m_curShape->angle_pen.width()));
                mod_Dlg.mod_color = m_curShape->angle_pen.color();
                switch( mod_Dlg.exec()) {
                case QDialog::Accepted:
                {
                    m_curShape->angle_pen.setWidth(mod_Dlg.le_width->text().toInt());
                    m_curShape->angle_pen.setColor(mod_Dlg.mod_color);
                    m_colorList[color_Count] = mod_Dlg.mod_color;
                    update();
                }
                    break;
                case QDialog::Rejected:
                    break;
                }
            }
                break;
            default:
                break;
            }
        }
    }
}


CShape* CDrawWin::HitTest(QMouseEvent *event,bool &bHit,bool &bCtrlHit)
{
    bHit = bCtrlHit = false;
    CShape *SHit = NULL;
    int i = 0;
    for(i = 0;i < m_shapeList.size();i++) {
        m_shapeList[i]->HitCtrlTest(event,bCtrlHit);
        if(bCtrlHit) {
            qDebug() << "LINE" << __LINE__;
            SHit = m_shapeList[i];
            break;
        } else {
            m_shapeList[i]->HitTest(event,bHit);
            if(bHit) {
                SHit = m_shapeList[i];
                break;
            }
        }
    }
    if(SHit != NULL) {
        color_Count = i;
        shape_Count = i;
    }
    return SHit;
}



