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
    bool viewportEvent(QEvent *event) override;

public slots:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;
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
    qreal totalScaleFactor = 1;

    QList<QPointF> getControlPoints(float x0, float y0, float x1, float y1, float x2, float y2, float t);
};

#endif // NOTEBOOKBASE_H
