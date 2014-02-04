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
    setItemIndexMethod(NoIndex); // improve the performance
}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    QPointF scenePos = mouseEvent->scenePos();
    if (NORMAL == _mode)
        _mode = items(scenePos).isEmpty()? SELECT : MOVE;
    switch (_mode) {
    case NORMAL:
        Q_ASSERT(!"Never get here!");
        break;
    case SELECT:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case MOVE:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case INS_RECT:
        _itemIndicator = new XRect;
        _itemIndicator->setPos(scenePos);
        //_itemIndicator->setBrush(...);
        addItem(_itemIndicator);
        break;
    case INS_LINE:
        break;
    case INS_OVAL:
        break;
    case INS_TEXT:
        break;
    case INS_CURVE:
        break;
    case INS_POLYGON:
        break;
    default:
        Q_ASSERT(!"Unknow XScene::Mode value!");
    }
    _lastMousePressScenePos = scenePos;
}

void XScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF scenePos = mouseEvent->scenePos();
    if (!_itemIndicator) {
        if (SELECT == _mode) { // set the same selection mode as PPT
            QPainterPath path;
            path.addRect(QRectF(_lastMousePressScenePos, scenePos));
            setSelectionArea(path, Qt::ContainsItemShape);
        }
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    } else {
        if (INS_RECT == _mode) {
            XRect *xrect = qgraphicsitem_cast<XRect *>(_itemIndicator);
            Q_ASSERT(xrect);
            xrect->setRect(QRectF(xrect->mapFromScene(_lastMousePressScenePos),
                                  xrect->mapFromScene(scenePos)).normalized());
        }
    }
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_ASSERT(NORMAL != _mode);
    if (SELECT == _mode || MOVE == _mode)
        _mode = NORMAL;
    if (_itemIndicator) {
        clearSelection();
        if (INS_RECT == _mode) {
            XRect *xrect = qgraphicsitem_cast<XRect *>(_itemIndicator);
            Q_ASSERT(xrect);
            if (xrect->rect().isEmpty())
                xrect->setRectDefault();
            xrect->setSelected(true);
            emit graphicsItemInserted(xrect);
        } else {
            Q_ASSERT(!"Unknown graphics item!");
        }
        //removeItem(_itemIndicator);
        //delete _itemIndicator;
        _itemIndicator = 0;
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
