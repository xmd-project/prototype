#include "xmd.h"
#include "xrect.h"

namespace Xmd {
void writeXGraphicsItem(QDataStream &out, const QGraphicsItem *item)
{
    int type = item->type();
    out << XGRAPHICSITEM_BEGIN << type;
    switch (type) {
    case XRect::Type:
        out << *static_cast<const XRect *>(item); break;
    //case XGroup::Type:
        //out << *static_cast<XGroup *>(item); break;
    default: Q_ASSERT(!"Unknown item type found!");
    }
    out << XGRAPHICSITEM_END;
}

/// Return loaded XGraphicsItem pointer; return 0 if no item.
QGraphicsItem *readXGraphicsItem(QDataStream &in)
{
    int itemDelimiter, itemType;
    in >> itemDelimiter;
    if (XGRAPHICSITEM_END == itemDelimiter)
        return 0;
    in >> itemType;
    Q_ASSERT(XGRAPHICSITEM_BEGIN==itemDelimiter || !"Unknown file format");
    switch (itemType) {
    case XRect::Type: {
        XRect *xrect = new XRect;
        in >> *xrect;
        return xrect;
    }
    default:
        Q_ASSERT(!"Read unknown data type!");
    }
    // recursively load child items.

    Q_ASSERT(XGRAPHICSITEM_END==itemDelimiter || !"Unknown file format");
}
} // namespace Xmd
