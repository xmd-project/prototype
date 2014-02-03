#ifndef XRECT_H
#define XRECT_H

#include <QGraphicsRectItem>

class XRect : public QGraphicsRectItem
{
public:
    XRect(QGraphicsItem * parent = 0);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

private:
    enum {_DEFAULT_WIDTH=90, _DEFAULT_HEIGHT=90};
public:
    void setRectDefault();
    ///TODO: Attractors
};

#endif // XRECT_H
