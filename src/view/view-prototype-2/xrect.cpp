#include "xrect.h"
#include "xpainterconstant.h"
#include <QPen>
#include <QBrush>
#include <QDebug>

void XRect::init()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setPen(XPainterConstant::pen(XPainterConstant::PEN_DEFAULT_BOUNDARY));
    setBrush(XPainterConstant::brush(XPainterConstant::BRUSH_DEFAULT_FILL));
    qDebug() << "XRect::init() - " << pos();
}

XRect::XRect(QGraphicsItem * parent):
    QGraphicsRectItem(parent)
{
    init();
}

XRect::XRect(const QRectF &rect, QGraphicsItem *parent):
    QGraphicsRectItem(rect, parent)
{
    init();
}

void XRect::setRectDefault()
{
    setRect(QRectF(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT));
}

QDataStream &operator<<(QDataStream &out, const XRect &xrect)
{
    QPointF position = xrect.pos();
    qreal zValue = xrect.zValue();
    QRectF rect = xrect.rect();
    QPen pen = xrect.pen();
    QBrush brush = xrect.brush();
    out << position
        << zValue
        << rect
        << pen
        << brush;
    // recursively save child items.
    foreach (QGraphicsItem *item, xrect.childItems())
        Xmd::writeXGraphicsItem(out, item);
    return out;
}

QDataStream &operator>>(QDataStream &in, XRect &xrect)
{
    QPointF position;
    qreal zValue;
    QRectF rect;
    QPen pen;
    QBrush brush;
    in >> position
       >> zValue
       >> rect
       >> pen
       >> brush;
    xrect.setPos(position);
    xrect.setZValue(zValue);
    xrect.setRect(rect);
    xrect.setPen(pen);
    xrect.setBrush(brush);
    // recursively load child items.
    QGraphicsItem *child;
    while ((child = Xmd::readXGraphicsItem(in)))
        child->setParentItem(&xrect);
    return in;
}
