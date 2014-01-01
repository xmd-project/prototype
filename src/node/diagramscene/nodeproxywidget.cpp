#include "nodeproxywidget.h"
#include "nodewidget.h"
#include "arrow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

NodeProxyWidget::NodeProxyWidget(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent,Qt::Widget)
{
    setWidget(new NodeWidget);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void NodeProxyWidget::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);
    if (index != -1)
        arrows.removeAt(index);
}

void NodeProxyWidget::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        NodeProxyWidget *terminalItem = qgraphicsitem_cast<NodeProxyWidget *>(arrow->startItem());
        if (terminalItem)
            terminalItem->removeArrow(arrow);
        terminalItem = qgraphicsitem_cast<NodeProxyWidget *>(arrow->endItem());
        if (terminalItem)
            terminalItem->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void NodeProxyWidget::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

#if 0
void NodeProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    oldPos = event->pos();
    QGraphicsProxyWidget::mousePressEvent(event);
    //QGraphicsItem::mousePressEvent(event);
    //QGraphicsItem::update();
}

void NodeProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        QGraphicsItem::update();
        return;
    }
    //QGraphicsItem::mouseMoveEvent(event);
    setPos(event->pos());
    QGraphicsProxyWidget::mouseMoveEvent(event);
}

void NodeProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsProxyWidget::mouseReleaseEvent(event);
    //QGraphicsItem::mouseReleaseEvent(event);
    //QGraphicsItem::update();

}
#endif
