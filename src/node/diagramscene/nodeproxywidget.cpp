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
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable
             |QGraphicsItem::ItemSendsScenePositionChanges
             |QGraphicsItem::ItemSendsGeometryChanges);
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

bool NodeProxyWidget::sceneEvent(QEvent *event)
{
    bool result = QGraphicsProxyWidget::sceneEvent(event);
    if (event->type() == QEvent::GraphicsSceneMousePress
            || event->type() == QEvent::GraphicsSceneMouseRelease
            || event->type() == QEvent::GraphicsSceneMouseMove
            || event->type() == QEvent::GraphicsSceneMouseDoubleClick)
    {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            QGraphicsItem::mouseReleaseEvent((QGraphicsSceneMouseEvent *)(event));
        } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
            QGraphicsItem::mouseMoveEvent((QGraphicsSceneMouseEvent *)(event));
        } else if (event->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsItem::mousePressEvent((QGraphicsSceneMouseEvent *)(event));
        }
        event->setAccepted(true);
        return true;
    }
    return result;
}
