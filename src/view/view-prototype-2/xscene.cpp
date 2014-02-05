#include "xscene.h"
#include "xrect.h"
#include "xpainterconstant.h"
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
namespace {
inline XRect *createXRect(
        const QPointF &pos, const QRectF &rect,
        const QPen &boundaryPen = XPainterConstant::pen(XPainterConstant::PEN_DEFAULT_BOUNDARY),
        const QBrush &fillBrush = XPainterConstant::brush(XPainterConstant::BRUSH_DEFAULT_FILL)
        )
{
    XRect *xrect = new XRect(rect);
    xrect->setPos(pos);
    xrect->setPen(boundaryPen);
    xrect->setBrush(fillBrush);
    return xrect;
}
}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        mouseEvent->accept();
        return;
    }
    //if (mouseEvent->button() != Qt::LeftButton)
        //return;
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
        _itemIndicator =
                createXRect(scenePos, QRectF(),
                            XPainterConstant::pen(XPainterConstant::PEN_SELECT_BOUNDARY),
                            XPainterConstant::brush(XPainterConstant::BRUSH_SELECT_FILL));
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
    if (mouseEvent->button() == (Qt::LeftButton | Qt::RightButton))
        return; // avoid right-click by mistake
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

XRect *XScene::addXRect(const QPointF &pos, const QRectF &rect)
{
    XRect *xrect = createXRect(pos, rect);
    if (xrect->rect().isEmpty())
        xrect->setRectDefault();
    addItem(xrect);
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
