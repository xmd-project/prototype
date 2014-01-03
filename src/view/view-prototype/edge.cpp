#include "edge.h"
#include "node.h"
#include <QPainter>
#include <cmath>
using std::acos;
using std::cos;
using std::sin;

namespace
{
static const double PI = 3.14159265358979323846264338327950288419717;
static const double TWO_PI = 2.0 * PI;
}

Edge::Edge(Node *sourceNode, Node *destNode, QGraphicsItem *parent) :
    _source(sourceNode), _dest(destNode),
    _sourcePoint(0,0), _destPoint(0,0),
    _arrowSize(10),
    QGraphicsItem(parent)
{
    setAcceptedMouseButtons(0);
    _source->addEdge(this);
    _dest->addEdge(this);
}

void Edge::adjust()
{
    if (!_source || !_dest)
        return;

    QLineF line(mapFromItem(_source, 0, 0), mapFromItem(_dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        enum {EDGE_OFFSET_FACTOR = 5};
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
