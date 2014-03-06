#include "xrect.h"
#include "xpainterconstant.h"
#include <QPen>
#include <QBrush>

void XRect::init()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setPen(XPainterConstant::pen(XPainterConstant::PEN_DEFAULT_BOUNDARY));
    setBrush(XPainterConstant::brush(XPainterConstant::BRUSH_DEFAULT_FILL));
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
    out << xrect.pos()
        << xrect.zValue()
        << xrect.rect()
        << xrect.pen()
        << xrect.brush();
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
    return in;
}
