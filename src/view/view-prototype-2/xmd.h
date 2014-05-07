#ifndef XMD_H
#define XMD_H

class QDataStream;
class QGraphicsItem;
class XRect;

namespace Xmd {
enum IOEnum {
    FILE_FORMAT_IDENTIFIER = 2121039,
    VERSION_NUMBER = 21,
    XGRAPHICSITEM_BEGIN = '{',
    XGRAPHICSITEM_END = '}'
};
enum XTypeEnum {
    XTYPE=0, // DO NOT MODIFY THIS VALUE! New X types are added below.
    XGROUP, XRECT,
    NUM_XTYPES // THIS MUST BE THE LAST ENUM!
};

/// Input/output format: '{' type Object '}'
void writeXGraphicsItem(QDataStream &out, const QGraphicsItem *item);
QGraphicsItem *readXGraphicsItem(QDataStream &in);
} // namespace Xmd

#endif // XMD_H
