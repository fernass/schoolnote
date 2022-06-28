#include "notebookbase.h"


#include <QGraphicsLineItem>
#include <QtMath>

noteBookBase::noteBookBase(QWidget* parent) :
    QGraphicsView(parent)
{
    QSize viewSize = this->size();
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewSize.rwidth(), viewSize.rwidth()*pageAspectRatio);
    QPixmap pic(":/pics/fcbayern.jpg");
    QSize size(500, 500);
    QPixmap pic_scaled = pic.scaled(size,Qt::KeepAspectRatio);
    scene->addPixmap(pic_scaled);
    this->setScene(scene);
//    this->fitInView(0, 0, viewSize.rwidth(), viewSize.rheight(), Qt::KeepAspectRatio);

    moved = false;
}

noteBookBase::~noteBookBase()
{
    for(auto &path : path_list)
    {
        delete path;
    }
    path_list.clear();
}

void noteBookBase::resizeEvent(QResizeEvent* e)
{
    QSize viewSize = this->size();
    scene->setSceneRect(0, 0, viewSize.rwidth(), viewSize.rwidth()*pageAspectRatio);
    fitInView(0, 0, viewSize.rwidth(), viewSize.rheight(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(e);
}

void noteBookBase::mousePressEvent(QMouseEvent* e)
{
    clickPos = mapToScene(e->pos());
    Points.push_back(clickPos);
    moved = false;
    QPainterPath* path = new QPainterPath();
    path->moveTo(clickPos);
    currentPath = path;
}

void noteBookBase::mouseReleaseEvent(QMouseEvent* e)
{
    if(!moved)
    {
        double rad = .5;
        QPointF pt = mapToScene(e->pos());
        scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2, rad*2, QPen(), QBrush(Qt::SolidPattern));
        moved = false;
    }

    path_list.push_back(currentPath);
    Points.clear();
    moved = false;
}


void noteBookBase::mouseDoubleClickEvent(QMouseEvent* e)
{
    e->ignore();
}

void noteBookBase::mouseMoveEvent(QMouseEvent* e)
{

    moved = true;
    currentPos = mapToScene(e->pos());

    Points.push_back(currentPos);
    if(Points.count() >= 3)
    {
        float t = .5;
        QList<QPointF> controlPoints;
        controlPoints = getControlPoints(Points[0].x(), Points[0].y(), Points[1].x(),Points[1].y(), Points[2].x(), Points[2].y(), t);

        currentPath->cubicTo(controlPoints[0], controlPoints[1], currentPos);
        scene->addPath(*currentPath);

        Points.clear();
    }
}


void noteBookBase::wheelEvent(QWheelEvent* e)
{
    if(e->angleDelta().y() > 0)
        scale(zoomFactor, zoomFactor);
    else if(e->angleDelta().y() < 0)
        scale(1/zoomFactor, 1/zoomFactor);;
}

bool noteBookBase::viewportEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> points = touchEvent->points();
        if (points.count() == 2) {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = points.first();
            const QTouchEvent::TouchPoint &touchPoint1 = points.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.position(), touchPoint1.position()).length()
                    / QLineF(touchPoint0.pressPosition(), touchPoint1.pressPosition()).length();
            if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
                // if one of the fingers is released, remember the current scale
                // factor so that adding another finger later will continue zooming
                // by adding new scale factor to the existing remembered value.
                totalScaleFactor *= currentScaleFactor;
                currentScaleFactor = 1;
            }
            setTransform(QTransform::fromScale(totalScaleFactor * currentScaleFactor,
                                               totalScaleFactor * currentScaleFactor));
        }
        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}
/*
void noteBook::paintEvent(QPaintEvent* e)
{
    QPen myPen(Qt::black);
    QBrush brush;
    QPainter painter(this);
//    QRect dirtyRect = e->rect();
    painter.setPen(myPen);
    painter.setBrush(brush);
    painter.drawPath(*path);
}
*/


QList<QPointF> noteBookBase::getControlPoints(float x0, float y0, float x1, float y1, float x2, float y2, float t)
{
    float d01 = qSqrt(qPow(x1-x0,2)+qPow(y1-y0,2));
    float d12 = qSqrt(qPow(x2-x1,2)+qPow(y2-y1,2));
    float fa = t*d01/(d01+d12);   // scaling factor for triangle Ta
    float fb = t*d12/(d01+d12);   // ditto for Tb, simplifies to fb=t-fa
    float p1x = x1-fa*(x2-x0);    // x2-x0 is the width of triangle T
    float p1y = y1-fa*(y2-y0);    // y2-y0 is the height of T
    float p2x = x1+fb*(x2-x0);
    float p2y = y1+fb*(y2-y0);
    QPointF c1(p1x, p1y);
    QPointF c2(p2x, p2y);
    QList<QPointF> cp;
    cp.push_back(c1);
    cp.push_back(c2);
    return cp;
}
/*
    QPointF pt = mapToScene(e->pos());
    QGraphicsLineItem* ln = new QGraphicsLineItem(lastPos.x(), lastPos.y(), pt.x(), pt.y());
    lastPos = pt;
    scene->addItem(ln);

*/
