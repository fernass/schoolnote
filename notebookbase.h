#ifndef NOTEBOOKBASE_H
#define NOTEBOOKBASE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>


class noteBookBase : public QGraphicsView
{
    Q_OBJECT
public:
    explicit noteBookBase(QWidget* parent = nullptr);
    ~noteBookBase();
public slots:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);
//    void paintEvent(QPaintEvent* e);

private:
    QGraphicsScene* scene;
    QList<QPointF> Points;
    QList<QPainterPath*> path_list;
    QPainterPath* currentPath;

    bool moved;
    QPointF lastPos;
    QPointF currentPos;
    QPointF clickPos;
    const float tolerance = 1E-3;
    const float zoomFactor = 1.5;

    QList<QPointF> getControlPoints(float x0, float y0, float x1, float y1, float x2, float y2, float t);
};

#endif // NOTEBOOKBASE_H
