#include "xscene.h"
#include "xrect.h"
#include "xgroup.h"
#include <QGraphicsSceneMouseEvent>
#include <QtAlgorithms>
#include <QDebug>

const qreal XScene::_ZVALUE_INCREMENT = qreal(1.0);

XScene::XScene(QObject *parent) :
    QGraphicsScene(parent)
{
    init();
}

void XScene::init()
{
    _mode = NORMAL;
    _itemIndicator = 0;
    _lastMousePressScenePos = QPointF(0,0);

    setItemIndexMethod(NoIndex); // improve the performance
}

void XScene::removeItem(QGraphicsItem *item)
{
    if (!item)
        return;
    QGraphicsScene::removeItem(item);
    // remove item and all its child items
    foreach (QGraphicsItem *child, item->childItems())
        _itemsSortedByZValue.removeOne(child);
    _itemsSortedByZValue.removeOne(item);
}

void XScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
    qDebug() << "addItem(): item->type() = " << item->type() << ", zValue() = " << item->zValue();
    _itemsSortedByZValue << item;
}

void XScene::adjustZValue(QGraphicsItem *item)
{
    item->setZValue(topZValue() + _ZVALUE_INCREMENT);
}

XRect *XScene::createXRectIndicator(
        const QPointF &pos, const QRectF &rect,
        const QPen &boundaryPen, const QBrush &fillBrush)
{
    XRect *xrect = new XRect(rect);
    xrect->setPos(pos);
    xrect->setPen(boundaryPen);
    xrect->setBrush(fillBrush);
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
        _itemIndicator = createXRectIndicator(
                    scenePos, QRectF(),
                    XPainterConstant::pen(XPainterConstant::PEN_SELECT_BOUNDARY),
                    XPainterConstant::brush(XPainterConstant::BRUSH_SELECT_FILL));
        addItem(_itemIndicator);
        adjustZValue(_itemIndicator);
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

void XScene::removeItemIndicator(QGraphicsItem *&indicator)
{
    removeItem(indicator);
    delete indicator;
    indicator = 0;
}

XRect *XScene::createXRect(QGraphicsItem *indicator)
{
    XRect *xrectIndicator = qgraphicsitem_cast<XRect *>(indicator);
    Q_ASSERT(xrectIndicator);
    XRect *xrect = createXRectIndicator(xrectIndicator->pos(),
                                        xrectIndicator->rect());
    Q_ASSERT(xrect);
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
    QGraphicsItem *newItem = 0;
    if (_itemIndicator) { // create and add a real item
        clearSelection();
        switch (_mode) {
        case INS_RECT:
            newItem = createXRect(_itemIndicator);
            removeItemIndicator(_itemIndicator);
            addItem(newItem);
            adjustZValue(newItem);
            qDebug() << "XScene::mouseReleaseEvent() - " << newItem->pos();
            emit graphicsItemInserted(newItem);
            break;
        default:
            Q_ASSERT(!"Unknown graphics item!");
        }
    }
    Q_ASSERT(!_itemIndicator || !"The item indicator must be destroyed"
             " after its corresponding new item is created.");
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

QGraphicsItem *XScene::topItem()
{
    return _itemsSortedByZValue.isEmpty() ? 0 : _itemsSortedByZValue.last();
}

const QGraphicsItem *XScene::topItem() const
{
    return _itemsSortedByZValue.isEmpty() ? 0 : _itemsSortedByZValue.last();
}

qreal XScene::topZValue() const
{
    return topItem() ? topItem()->zValue() : qreal(0.0);
}

inline void swapZValue(QGraphicsItem *item1, QGraphicsItem *item2)
{
    Q_ASSERT(item1 && item2);
    qreal z = item1->zValue();
    item1->setZValue(item2->zValue());
    item2->setZValue(z);
}

inline bool QGraphicsItemZValueLessThan(const QGraphicsItem *item1, const QGraphicsItem *item2)
{
    Q_ASSERT(item1 && item2);
    return item1->zValue() < item2->zValue();
}

/// Items will be sorted from bottom up
void XScene::sortByZValue(QList<QGraphicsItem *> &items)
{
    qSort(items.begin(), items.end(), QGraphicsItemZValueLessThan);
}

void XScene::bringForwardSelectedItems()
{
    QList<QGraphicsItem *> selectedItmesSortedByZValue = selectedItems(); // no specific order
    if (selectedItmesSortedByZValue.isEmpty())
        return;
    Q_ASSERT(!_itemsSortedByZValue.isEmpty());
    sortByZValue(selectedItmesSortedByZValue); // from bottom up
    for (int i = selectedItmesSortedByZValue.size() - 1; i >= 0; --i) {
        QGraphicsItem * const selectedItem = selectedItmesSortedByZValue.at(i);
        if (selectedItem == _itemsSortedByZValue.last())
            continue; // do nothing if the top item is selected
        const int itemIdx = _itemsSortedByZValue.indexOf(selectedItem);
        Q_ASSERT(selectedItem == _itemsSortedByZValue.at(itemIdx));
        const int nextItemIdx = itemIdx + 1;
        Q_ASSERT(0 < nextItemIdx && nextItemIdx < _itemsSortedByZValue.size());
        if (-1 == selectedItmesSortedByZValue.indexOf(_itemsSortedByZValue.at(nextItemIdx))) {
            swapZValue(_itemsSortedByZValue[itemIdx], _itemsSortedByZValue[nextItemIdx]);
            _itemsSortedByZValue.swap(itemIdx, nextItemIdx);
        }
    }
}

void XScene::sendBackwardSelectedItems()
{
    QList<QGraphicsItem *> selectedItmesSortedByZValue = selectedItems(); // no specific order
    if (selectedItmesSortedByZValue.isEmpty())
        return;
    Q_ASSERT(!_itemsSortedByZValue.isEmpty());
    sortByZValue(selectedItmesSortedByZValue); // from bottom up
    for (int i = 0; i < selectedItmesSortedByZValue.size(); ++i) {
        QGraphicsItem * const selectedItem = selectedItmesSortedByZValue.at(i);
        if (selectedItem == _itemsSortedByZValue.first())
            continue; // do nothing if the bottom item is selected
        const int itemIdx = _itemsSortedByZValue.indexOf(selectedItem);
        Q_ASSERT(selectedItem == _itemsSortedByZValue.at(itemIdx));
        const int prevItemIdx = itemIdx - 1;
        Q_ASSERT(0 <= prevItemIdx && prevItemIdx < _itemsSortedByZValue.size());
        if (-1 == selectedItmesSortedByZValue.indexOf(_itemsSortedByZValue.at(prevItemIdx))) {
            swapZValue(_itemsSortedByZValue[itemIdx], _itemsSortedByZValue[prevItemIdx]);
            _itemsSortedByZValue.swap(itemIdx, prevItemIdx);
        }
    }
}

XGroup *XScene::createItemGroup(const QList<QGraphicsItem *> &items)
{
    XGroup *xgroup = new XGroup;
    addItem(xgroup);
    adjustZValue(xgroup);
    qDebug() << "XScene::createItemGroup() - " << xgroup->pos();
    foreach (QGraphicsItem *item, items)
        xgroup->addToGroup(item);
    return xgroup;
}

void XScene::destroyItemGroup(QGraphicsItemGroup *group)
{
    _itemsSortedByZValue.removeOne(group);
    XGroup *xgroup = qgraphicsitem_cast<XGroup *>(group);
    if (xgroup) {
        foreach (QGraphicsItem *item, xgroup->childItems())
            xgroup->removeFromGroup(item);
    }
    QGraphicsScene::destroyItemGroup(group);
}

void XScene::group()
{
    QList<QGraphicsItem *>itemsToBeAdded;
    foreach (QGraphicsItem *item, selectedItems())
        if (!item->parentItem()) // an item is never be added to more than 1 group
            itemsToBeAdded << item;
    if (itemsToBeAdded.size() <= 1)
        return; // never create an empty group or a group with only one item
    clearSelection(); // and unselected all items before grouping them
    QGraphicsItemGroup *group = createItemGroup(itemsToBeAdded);
    group->setSelected(true); // select the new group
}

void XScene::ungroup()
{
    QList<QGraphicsItem *>subitems;
    foreach (QGraphicsItem *item, selectedItems()) {
        XGroup *group = qgraphicsitem_cast<XGroup *>(item);
        if (group) {
            subitems << group->childItems();
            destroyItemGroup(group);
        }
    }
    // select all subitems after dismantling all selected groups
    foreach (QGraphicsItem *subitem, subitems)
        subitem->setSelected(true);
}

void XScene::clear()
{
    // Removes and deletes all items from the scene,
    // but otherwise leaves the state of the scene unchanged.
    QGraphicsScene::clear();
    _itemsSortedByZValue.clear();
}
