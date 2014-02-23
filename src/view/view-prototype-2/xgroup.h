#ifndef XGROUP_H
#define XGROUP_H

#include "xmd.h"
#include <QGraphicsItemGroup>

class XGroup : public QGraphicsItemGroup
{
public:
    XGroup(QGraphicsItem *parent=0);

    enum { Type = UserType + Xmd::XGROUP };
    int type() const { return Type; }
};

#endif // XGROUP_H
