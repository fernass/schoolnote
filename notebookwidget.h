#ifndef NOTEBOOKWIDGET_H
#define NOTEBOOKWIDGET_H

#include "notebookbase.h"

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QVBoxLayout>

class noteBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit noteBookWidget(QWidget *parent = nullptr);

private:
    noteBookBase* notebook;
    QVBoxLayout* vl;
    QToolButton* fitZoom;
    QToolButton* zoom;
    QToolButton* pen;
    QToolButton* pan;
    QToolBar* tb;

signals:

};

#endif // NOTEBOOKWIDGET_H
