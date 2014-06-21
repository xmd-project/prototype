#ifndef XNODE_H
#define XNODE_H

#include <QGraphicsItem>
#include <QRectF>

struct XNodeImpl;

class XNode : public QGraphicsItem
{
public:
    XNode();
    ~XNode();
    void setGraphics(QGraphicsItem *graphics);
public: // pure virtual
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
public: // virtual
    QPainterPath shape() const;

private:
    XNodeImpl *_impl;
};

#endif // XNODE_H
