#include "xrect.h"
#include "xpainterconstant.h"

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
    setRect(QRectF(0, 0, _DEFAULT_WIDTH, _DEFAULT_HEIGHT));
}
