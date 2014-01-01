#include "dragablelabel.h"
#include <QtWidgets>

DragableLabel::DragableLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
{
}
#if 0
void DragableLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragableLabel::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        const QMimeData *mime = event->mimeData();

        QPoint position = event->pos();
        QPoint hotSpot;

        QList<QByteArray> hotSpotPos = mime->data("application/x-hotspot").split(' ');
        if (hotSpotPos.size() == 2) {
            hotSpot.setX(hotSpotPos.first().toInt());
            hotSpot.setY(hotSpotPos.last().toInt());
        }

        DragableLabel *newLabel = new DragableLabel(this);
        newLabel->move(position - hotSpot);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragableLabel::mousePressEvent(QMouseEvent *event)
{
    QPoint hotSpot = event->pos();

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(this->text());
    mimeData->setData("application/x-hotspot",
                      QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

    QPixmap pixmap(this->size());
    this->render(&pixmap);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction)
        this->close();
}
#endif
