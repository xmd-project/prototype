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
#if 0
void XmdNodeWidgetProxy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //m_pressed=true;
    QGraphicsItem::mousePressEvent(event);
}


void XmdNodeWidgetProxy::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //m_pressed=false;
    QGraphicsItem::mouseReleaseEvent(event);
}
#endif
void XmdNodeWidgetProxy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if(m_pressed)
        this->setPos(event->scenePos());
    QGraphicsItem::mouseMoveEvent(event);
}

