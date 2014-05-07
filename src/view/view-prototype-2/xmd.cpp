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

/// Load a XGraphicsItem into destItem.
/// Return destItem.
template <typename T>
inline QGraphicsItem *readXItem(QDataStream &in, T *destItem)
{
    Q_ASSERT(destItem);
    in >> *destItem;
    return destItem;
}

/// Return a pointer of the loaded XGraphicsItem.
/// Return 0 if no item.
QGraphicsItem *readXGraphicsItem(QDataStream &in)
{
    int itemDelimiter;
    in >> itemDelimiter;
    if (XGRAPHICSITEM_END == itemDelimiter)
        return 0;
    Q_ASSERT(XGRAPHICSITEM_BEGIN == itemDelimiter || !"Unknown file format");
    int itemType;
    in >> itemType;
    switch (itemType) {
    case XRect::Type: return readXItem(in, new XRect);
    default: Q_ASSERT(!"Read unknown data type!");
    }
    // recursively load child items.

    Q_ASSERT(XGRAPHICSITEM_END == itemDelimiter || !"Unknown file format");
}
} // namespace Xmd
