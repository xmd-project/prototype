#include "node.h"
#include "edge.h"
#include "nodewidget.h"
#include <QGraphicsSceneMouseEvent>
#include <cassert>

Node::Node(QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent, Qt::Widget)
{
    setWidget(new NodeWidget);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable
             |QGraphicsItem::ItemSendsScenePositionChanges
             |QGraphicsItem::ItemSendsGeometryChanges);
}

void Node::addEdge(Edge *edge)
{
    assert(edge);
    _edges << edge;
    edge->adjust();
}

bool Node::sceneEvent(QEvent *event)
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
#if 0
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
#endif
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        foreach (Edge *edge, _edges)
            edge->adjust();
        break;
    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}
