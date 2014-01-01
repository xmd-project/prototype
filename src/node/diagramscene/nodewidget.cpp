#include "nodewidget.h"
#include "ui_nodewidget.h"

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::NodeWidget)
{
    ui->setupUi(this);
}

NodeWidget::~NodeWidget()
{
    delete ui;
}

void NodeWidget::mousePressEvent(QMouseEvent *event)
{
    //event->globalPos();
    //oldPos = mapToGlobal(pos());
    oldPos = event->globalPos();
    //QWidget::mousePressEvent(event);
}

void NodeWidget::mouseMoveEvent(QMouseEvent *event)
{
//    const QPoint current = mapToGlobal(event->pos());
    const QPoint delta = event->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPos();
    //QWidget::mouseMoveEvent(event);
}
