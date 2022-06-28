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

protected:
    void resizeEvent(QResizeEvent*) override;

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
    qreal currentZoomFactor;
    qreal totalScaleFactor = 1;

// constants
    const float tolerance = 1E-3;
    const float zoomFactor = 1.2;
    const uint16_t pageWidth = 1024; // equivalent to 210mm on an A4
    const uint16_t pageHeight = 1448; // equivalent to 297mm on an A4
    const float pageAspectRatio = 1.414285714285714; // equivalent to 297/210 of an A4


    QList<QPointF> getControlPoints(float x0, float y0, float x1, float y1, float x2, float y2, float t);
};

#endif // NOTEBOOKBASE_H
