#include "xgroup.h"
#include <QDebug>

XGroup::XGroup(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    qDebug() << "XGroup::XGroup() - " << pos();
}

void XGroup::addToGroup(QGraphicsItem *item)
{
    Q_ASSERT(item);
    item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    QGraphicsItemGroup::addToGroup(item);
}

void XGroup::removeFromGroup(QGraphicsItem *item)
{
    Q_ASSERT(item);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    QGraphicsItemGroup::removeFromGroup(item);
}

void XGroup::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug() << "XGroup::mouseMoveEvent() pos - " << pos();
    qDebug() << "XGroup::mouseMoveEvent() scenePos - " << scenePos();
    qDebug() << "XGroup::mouseMoveEvent() boundingRect - " << boundingRect();
    QGraphicsItem::mouseMoveEvent(event);
}

void XGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    qDebug() << "XGroup::mouseReleaseEvent() pos - " << pos();
    qDebug() << "XGroup::mouseReleaseEvent() scenePos - " << scenePos();
    qDebug() << "XGroup::mouseReleaseEvent() boundingRect - " << boundingRect();
    foreach (QGraphicsItem* child, childItems()) {
        qDebug() << ">> Child " << child << " pos() = " << child->pos() << " <<";
        qDebug() << "[[ Child " << child << " scenePos() = " << child->scenePos() << " ]]";
    }
}

QDataStream &operator<<(QDataStream &out, const XGroup &xgroup)
{
    QPointF position = xgroup.pos();
    qreal zValue = xgroup.zValue();
    out << position << zValue;
    qDebug() << "operator<<(XGroup) position - " << position;
    // recursively save child items.
    foreach (QGraphicsItem *item, xgroup.childItems())
        Xmd::writeXGraphicsItem(out, item);
    return out;
}

QDataStream &operator>>(QDataStream &in, XGroup &xgroup)
{
    QPointF position;
    qreal zValue;
    in >> position
       >> zValue;
    qDebug() << "operator>>(XGroup) position - " << position;
    xgroup.setPos(position);
    xgroup.setZValue(zValue);
    // recursively load child items.
    QGraphicsItem *child;
    while ((child = Xmd::readXGraphicsItem(in)))
        xgroup.addToGroup(child);
    return in;
}
