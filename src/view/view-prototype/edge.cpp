#include "edge.h"
#include "node.h"
#include <QPainter>
#include <cmath>
#include <cassert>
using std::acos;
using std::cos;
using std::sin;

namespace
{
static const double PI = 3.14159265358979323846264338327950288419717;
static const double TWO_PI = 2.0 * PI;
}

Edge::Edge(Node *sourceNode, Node *destNode, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    _source(sourceNode), _dest(destNode),
    _sourcePoint(0,0), _destPoint(0,0),
    _arrowSize(10)

{
    setAcceptedMouseButtons(0);
    _source->addEdge(this);
    _dest->addEdge(this);
}

void Edge::adjust()
{
    if (!_source || !_dest)
        return;
    adjustTerminalPoints();
    prepareGeometryChange();

}

QPointF Edge::findTerminalPoint(const Node *node) const
{
    assert(node==_source || node==_dest);
    const Node *endNode = node==_source ? _dest : _source;
    QPointF nodePos = mapFromItem(node, node->boundingRect().center());
    QPointF endNodePos = mapFromItem(endNode, endNode->boundingRect().center());
    QLineF centerLine(nodePos,endNodePos);
    QPolygonF boundingPolygon = mapFromItem(endNode, endNode->boundingRect());
    QPointF p1 = boundingPolygon.first();
    QPointF p2;
    QPointF intersectPoint;
    for (int i = 1; i < boundingPolygon.count(); ++i) {
        p2 = boundingPolygon.at(i);
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    return intersectPoint;
}

void Edge::adjustTerminalPoints()
{
    QLineF line(findTerminalPoint(_source), findTerminalPoint(_dest));
    qreal length = line.length();
    enum {SHORTEST_EDGE_LENTH = 20};
    if (length > qreal(SHORTEST_EDGE_LENTH)) {
        enum {EDGE_OFFSET_FACTOR = 3};
        QPointF edgeOffset((line.dx() * EDGE_OFFSET_FACTOR) / length,
                           (line.dy() * EDGE_OFFSET_FACTOR) / length);
        _sourcePoint = line.p1() + edgeOffset;
        _destPoint = line.p2() - edgeOffset;
    } else {
        _sourcePoint = _destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    if (!_source || !_dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + _arrowSize) / 2.0;

    return QRectF(_sourcePoint, QSizeF(_destPoint.x() - _sourcePoint.x(),
                                       _destPoint.y() - _sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!_source || !_dest)
        return;

    QLineF line(_sourcePoint, _destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
    double angle = acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TWO_PI - angle;

    QPointF sourceArrowP1 = _sourcePoint + QPointF(sin(angle + PI / 3) * _arrowSize,
                                                   cos(angle + PI / 3) * _arrowSize);
    QPointF sourceArrowP2 = _sourcePoint + QPointF(sin(angle + PI - PI / 3) * _arrowSize,
                                                   cos(angle + PI - PI / 3) * _arrowSize);
    QPointF destArrowP1 = _destPoint + QPointF(sin(angle - PI / 3) * _arrowSize,
                                               cos(angle - PI / 3) * _arrowSize);
    QPointF destArrowP2 = _destPoint + QPointF(sin(angle - PI + PI / 3) * _arrowSize,
                                               cos(angle - PI + PI / 3) * _arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
