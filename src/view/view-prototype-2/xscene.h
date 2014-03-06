#ifndef XSCENE_H
#define XSCENE_H

#include "xpainterconstant.h"
#include <QGraphicsScene>

class XRect;

class XScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit XScene(QObject *parent = 0);
    void addItem(QGraphicsItem *item);
    void removeItem(QGraphicsItem *item);
    QGraphicsItemGroup *createItemGroup(const QList<QGraphicsItem *> & items);
    void destroyItemGroup(QGraphicsItemGroup * group);

public slots:
    void clear();

signals:
    void graphicsItemInserted(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

public:
    enum Mode {
        NORMAL, SELECT, MOVE,
        INS_RECT, INS_LINE, INS_OVAL, INS_TEXT, INS_CURVE, INS_POLYGON
    };

public slots:
    void setMode(Mode mode = NORMAL) { _mode = mode; }

public:
    static void sortByZValue(QList<QGraphicsItem *> &items);

public:
    void bringForwardSelectedItems();
    void sendBackwardSelectedItems();
    void group();
    void ungroup();

private:
    void init();
    XRect *createXRect(
            const QPointF &pos, const QRectF &rect,
            const QPen &boundaryPen = XPainterConstant::pen(XPainterConstant::PEN_DEFAULT_BOUNDARY),
            const QBrush &fillBrush = XPainterConstant::brush(XPainterConstant::BRUSH_DEFAULT_FILL)
            );
    XRect *addXRect(const QPointF &pos, const QRectF &rect);
    QGraphicsItem *topItem();
    const QGraphicsItem *topItem() const;
    qreal topZValue() const;

private:
    Mode _mode;
    QGraphicsItem *_itemIndicator;
    QPointF _lastMousePressScenePos;
    QList<QGraphicsItem *> _itemsSortedByZValue; ///! keep track of all items in this scene in terms of zValue

private:
    static const qreal _ZVALUE_INCREMENT; ///! (new item's zValue) = (current top item's zValue) + _ZVALUE_INCREMENT
};

#endif // XSCENE_H
