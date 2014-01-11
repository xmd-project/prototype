#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

QT_BEGIN_NAMESPACE
class QLineF;
QT_END_NAMESPACE

class Edge : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }
    Edge(Node *sourceNode, Node *destNode, QGraphicsItem *parent = 0);
    Node *sourceNode() const { return _source; }
    Node *destNode() const { return _dest; }
    void adjust();
private:
    QPointF findTerminalPoint(const Node *node) const;
    void adjustTerminalPoints();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Node *_source, *_dest; ///! terminal nodes
    QPointF _sourcePoint, _destPoint; ///! terminal points
    qreal _arrowSize;
};

#endif // EDGE_H
