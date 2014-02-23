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
    enum {_DEFAULT_WIDTH=90, _DEFAULT_HEIGHT=90};
    ///TODO: Attractors
};

#endif // XRECT_H
