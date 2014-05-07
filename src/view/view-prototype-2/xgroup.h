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

/// Object data I/O operations
QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE
QDataStream &operator<<(QDataStream &out, const XGroup &xgroup);
QDataStream &operator>>(QDataStream &in, XGroup &xgroup);

#endif // XGROUP_H
