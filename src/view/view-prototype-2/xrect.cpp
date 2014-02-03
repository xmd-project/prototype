#include "xrect.h"

XRect::XRect(QGraphicsItem * parent):
    QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void XRect::setRectDefault()
{
    setRect(QRectF(0, 0, _DEFAULT_WIDTH, _DEFAULT_HEIGHT));
}
