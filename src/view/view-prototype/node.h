#ifndef NODE_H
#define NODE_H

#include <QGraphicsProxyWidget>
#include <QList>

QT_BEGIN_NAMESPACE
class QEvent;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Edge;

class Node : public QGraphicsProxyWidget
{
    Q_OBJECT
public:    
    enum { Type = UserType + 1 };
    int type() const { return Type; }
    explicit Node(QGraphicsProxyWidget *parent = 0);
    QList<Edge *> edges() const { return _edges; }
    void addEdge(Edge *edge);

signals:
public slots:
protected:
    bool sceneEvent(QEvent *event);
#if 0
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
#endif
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QList<Edge *> _edges;
};

#endif // NODE_H
