#include "nodeproxywidget.h"
#include "nodewidget.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

NodeProxyWidget::NodeProxyWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags,QPoint pos)
    :QGraphicsProxyWidget(parent,wFlags)
{

    NodeWidget *nodeWidget=new NodeWidget();

    this->setWidget(nodeWidget);
    this->setPos(pos);
    this->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable
                   |QGraphicsItem::ItemSendsScenePositionChanges  //set two to invoke itemchange() when possible
                   |QGraphicsItem::ItemSendsGeometryChanges);

}

bool NodeProxyWidget::sceneEvent(QEvent *event)
{
    bool result=QGraphicsProxyWidget::sceneEvent(event);
    if (event->type() == QEvent::GraphicsSceneMousePress||
        event->type() == QEvent::GraphicsSceneMouseRelease ||
        event->type() == QEvent::GraphicsSceneMouseMove ||
        event->type() == QEvent::GraphicsSceneMouseDoubleClick )
    {
        if (event->type() == QEvent::GraphicsSceneMousePress){
            QGraphicsItem::mousePressEvent((QGraphicsSceneMouseEvent *)event);
        } else if (event->type() == QEvent::GraphicsSceneMouseRelease){
            QGraphicsItem::mouseReleaseEvent((QGraphicsSceneMouseEvent *)(event));
        } else if (event->type() == QEvent::GraphicsSceneMouseMove){
            QGraphicsItem::mouseMoveEvent((QGraphicsSceneMouseEvent *)(event));
        }
        event->setAccepted(true);
        return true;
    }
    return result;
}
