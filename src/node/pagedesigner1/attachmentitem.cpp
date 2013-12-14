#include "attachmentitem.h"
#include "itemtypes.hpp"
#include <QDesktopServices>
#include <QUrl>

AttachmentItem::AttachmentItem(const QPointF &position,QPixmap pic)
{
    //construct function
    setPixmap(pic);
    setPos(position);
}
void AttachmentItem::mousePressEvent(QKeyEvent *event)
{
    //mouse left click open the attachment
    QDesktopServices::openUrl((QUrl::fromLocalFile(this->getFileName())));
}
int AttachmentItem::type() const { return AttachmentItemType; }

bool AttachmentItem::contains(const QPointF &point) const
{
    bool ret=(QRect(QPoint(this->x(),this->y()),this->radius)).contains(point.x(),point.y());
    return ret;
}
void AttachmentItem::openURL()
{
    //open file
    if(this->getFileName().isNull())
        return;
    QDesktopServices::openUrl((QUrl::fromLocalFile(this->getFileName())));
}
