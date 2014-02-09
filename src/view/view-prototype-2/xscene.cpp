#include "xscene.h"
#include "xrect.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

XScene::XScene(QObject *parent) :
    QGraphicsScene(parent),
    _mode(NORMAL),
    _itemIndicator(0), _topItem(0),
    _lastMousePressScenePos(0,0)
{
    setItemIndexMethod(NoIndex); // improve the performance
}

void XScene::removeItem(QGraphicsItem *item)
{
    QGraphicsScene::removeItem(item);
    if (item == _topItem)
        _topItem = items().empty() ? 0 : items().last();
}

void XScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
    Q_ASSERT(item == items().last()); // item is not always on the top
    if (_topItem)
        _topItem->stackBefore(item); // make sure new item is always on the top
    _topItem = item;
}

XRect *XScene::createXRect(
        const QPointF &pos, const QRectF &rect,
        const QPen &boundaryPen, const QBrush &fillBrush)
{
    XRect *xrect = new XRect(rect);
    xrect->setPos(pos);
    xrect->setPen(boundaryPen);
    xrect->setBrush(fillBrush);
    addItem(xrect);
    return xrect;
}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::RightButton) {
        mouseEvent->accept(); // never propagate the event
        return;
    }
    const QPointF scenePos = mouseEvent->scenePos();
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
        _itemIndicator =
                createXRect(scenePos, QRectF(),
                            XPainterConstant::pen(XPainterConstant::PEN_SELECT_BOUNDARY),
                            XPainterConstant::brush(XPainterConstant::BRUSH_SELECT_FILL));
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
    const QPointF scenePos = mouseEvent->scenePos();
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

XRect *XScene::addXRect(const QPointF &pos, const QRectF &rect)
{
    XRect *xrect = createXRect(pos, rect);
    if (xrect->rect().isEmpty())
        xrect->setRectDefault();
    xrect->setSelected(true);
    return xrect;
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    Q_ASSERT(NORMAL != _mode);
    if (SELECT == _mode || MOVE == _mode)
        _mode = NORMAL;
    if (_itemIndicator) { // add real
        clearSelection();
        switch (_mode) {
        case INS_RECT:
            Q_ASSERT(qgraphicsitem_cast<XRect *>(_itemIndicator));
            emit graphicsItemInserted(
                        addXRect(_itemIndicator->pos(), qgraphicsitem_cast<XRect *>(_itemIndicator)->rect()));
            break;
        default:
            Q_ASSERT(!"Unknown graphics item!");
        }
        removeItem(_itemIndicator);
        delete _itemIndicator;
        _itemIndicator = 0;
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
