#ifndef XGROUP_H
#define XGROUP_H

#include <QGraphicsItemGroup>

class XGroup : public QGraphicsItemGroup
{
public:
    XGroup(QGraphicsItem *parent=0);

    enum { Type = UserType + 2 };
    int type() const { return Type; }
};

#endif // XGROUP_H
