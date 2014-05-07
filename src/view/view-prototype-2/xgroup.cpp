#include "xgroup.h"

XGroup::XGroup(QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
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

QDataStream &operator<<(QDataStream &out, const XGroup &xgroup)
{
    out << xgroup.pos()
        << xgroup.zValue();
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
    xgroup.setPos(position);
    xgroup.setZValue(zValue);
    // recursively load child items.
    QGraphicsItem *child;
    while ((child = Xmd::readXGraphicsItem(in)))
        xgroup.addToGroup(child);
    return in;
}
