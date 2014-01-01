#include "nodewidgetproxy.h"
#include "nodewidget.h"
#include <QGraphicsSceneMouseEvent>
XmdNodeWidgetProxy::XmdNodeWidgetProxy(QGraphicsItem *parent, Qt::WindowFlags wFlags,QPoint pos)
    :QGraphicsProxyWidget(parent,wFlags)
{

    XmdNodeWidget *nodeWidget=new XmdNodeWidget();
    this->setWidget(nodeWidget);
    this->setPos(pos);
    this->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable
                   |QGraphicsItem::ItemSendsScenePositionChanges
                   |QGraphicsItem::ItemSendsGeometryChanges); //let all move togather

}

bool XmdNodeWidgetProxy::sceneEvent(QEvent *event)
{
        //qDebug()<<"QwidgetProxy POS0:"<<this->scenePos();
    if (event->type() == QEvent::GraphicsSceneMousePress||
            event->type() == QEvent::GraphicsSceneMouseRelease ||
            event->type() == QEvent::GraphicsSceneMouseMove ||
            event->type() == QEvent::GraphicsSceneMouseDoubleClick )
    {
        //qDebug()<<"sceneEvent...";
        //qDebug()<<"QwidgetProxy POS1:"<<this->scenePos();
        QGraphicsProxyWidget::mousePressEvent((QGraphicsSceneMouseEvent *)(event));

        if (event->type() == QEvent::GraphicsSceneMouseRelease)
        {
            QGraphicsItem::mouseReleaseEvent((QGraphicsSceneMouseEvent *)(event));
        }

        else if (event->type() == QEvent::GraphicsSceneMouseMove)
        {
            QGraphicsItem::mouseMoveEvent((QGraphicsSceneMouseEvent *)(event));
        }
        event->setAccepted(true);
        return true;
    }
      return false;
}

