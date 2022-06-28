#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notebookwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    noteBookWidget* notebookwidget = new noteBookWidget;
    notebookwidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QRect sizeWidget = ui->centralwidget->geometry();
    QRect sizeLayout(0, 0, sizeWidget.width()*0.1, sizeWidget.height()*0.8);
    //ui->twBrowser->resize(200,500);
//    ui->twBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->twBrowser->setFixedWidth(300);

    ui->horizontalLayout->addWidget(notebookwidget);

    ui->horizontalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

