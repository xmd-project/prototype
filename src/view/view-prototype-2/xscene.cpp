#include "xscene.h"
#include "xrect.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

XScene::XScene(QObject *parent) :
    QGraphicsScene(parent),
    _mode(NORMAL),
    _itemIndicator(0),
    _lastMousePressScenePos(0,0)
{
}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch (_mode) {
    case INS_RECT:
        _itemIndicator = new XRect;
        _itemIndicator->setPos(mouseEvent->scenePos());
        //_itemIndicator->setBrush(...);
        addItem(_itemIndicator);
        break;
    default:
        Q_ASSERT(_mode == NORMAL);
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
    _lastMousePressScenePos = mouseEvent->scenePos();
}

void XScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (_itemIndicator) {
        if (XRect::Type == _itemIndicator->type()) {
            XRect *xrect = qgraphicsitem_cast<XRect *>(_itemIndicator);
            Q_ASSERT(xrect && _mode == INS_RECT);
            xrect->setRect(QRectF(xrect->mapFromScene(_lastMousePressScenePos),
                                  xrect->mapFromScene(mouseEvent->scenePos())).normalized());
        } else {
            Q_ASSERT(!"Unknown graphics item!");
        }
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (_itemIndicator) {
        // replace an empty graphics item with the default size
        if (XRect::Type == _itemIndicator->type()) {
            XRect *xrect = qgraphicsitem_cast<XRect *>(_itemIndicator);
            Q_ASSERT(xrect && _mode == INS_RECT);
            if (xrect->rect().isEmpty())
                xrect->setRectDefault();
        } else {
            Q_ASSERT(!"Unknown graphics item!");
        }
        //removeItem(_itemIndicator);
        //delete _itemIndicator;
        _itemIndicator = 0;
    }

    if (_mode != NORMAL)
        setMode(NORMAL);

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
