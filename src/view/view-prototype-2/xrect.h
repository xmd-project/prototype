#ifndef XRECT_H
#define XRECT_H

#include "xmd.h"
#include <QGraphicsRectItem>

class XRect : public QGraphicsRectItem
{
public:
    XRect(QGraphicsItem * parent = 0);
    XRect(const QRectF &rect, QGraphicsItem * parent = 0);

    enum { Type = UserType + Xmd::XRECT };
    int type() const { return Type; }
    void setRectDefault();

private:
    void init();

private:
    enum {DEFAULT_WIDTH=90, DEFAULT_HEIGHT=90};
    ///TODO: Attractors
};

/// Object data I/O operations
QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE
QDataStream &operator<<(QDataStream &out, const XRect &xrect);
QDataStream &operator>>(QDataStream &in, XRect &xrect);

#endif // XRECT_H
