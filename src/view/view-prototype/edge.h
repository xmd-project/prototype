#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }
    Edge(Node *sourceNode, Node *destNode, QGraphicsItem *parent = 0);
    Node *sourceNode() const { return _source; }
    Node *destNode() const { return _dest; }
    void adjust();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Node *_source, *_dest;
    QPointF _sourcePoint, _destPoint;

    qreal _arrowSize;
};

#endif // EDGE_H
