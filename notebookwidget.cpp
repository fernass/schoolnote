#include "notebookwidget.h"

noteBookWidget::noteBookWidget(QWidget *parent)
    : QWidget{parent}
{
    vl = new QVBoxLayout(this);
    fitZoom = new QToolButton;
    fitZoom->setIcon(QIcon(":/icons/zoom-fit.png"));
    zoom = new QToolButton;
    zoom->setIcon(QIcon(":/icons/zoom.png"));
    zoom->setCheckable(true);
    pen = new QToolButton;
    pen->setIcon(QIcon(":/icons/pen.png"));
    pen->setCheckable(true);
    pan = new QToolButton;
    pan->setIcon(QIcon(":/icons/pan.png"));
    pan->setCheckable(true);
    tb = new QToolBar;
    tb->addWidget(fitZoom);
    tb->addWidget(zoom);
    tb->addWidget(pan);
    tb->addWidget(pen);

    vl->addWidget(tb);

    notebook = new noteBookBase;
    vl->addWidget(notebook);
    vl->addStretch();

}
