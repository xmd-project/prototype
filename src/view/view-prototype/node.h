#ifndef NODE_H
#define NODE_H

#include <QGraphicsProxyWidget>
#include <QList>
#include <limits>

QT_BEGIN_NAMESPACE
class QEvent;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Edge;
//global var
const qreal MAX_VALUE=std::numeric_limits<double>::max();
class Node : public QGraphicsProxyWidget
{
    Q_OBJECT
    void init();
public:    
    enum { Type = UserType + 1 };
    int type() const { return Type; }
    explicit Node(QGraphicsProxyWidget *parent = 0);
    Node(const QPointF &position, QGraphicsProxyWidget *parent = 0);
    ~Node();
    QList<Edge *> edges() const { return _edges; }
    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);
signals:
public slots:
    void showSnapShot(QString imagefilename);
    void closeSnapShot();
protected:
    bool sceneEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //hoverEnterEvent(QGraphicsSceneHoverEvent *event);
#if 0
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
#endif
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QList<Edge *> _edges;
    QGraphicsPixmapItem *_snapshotimage; //temp var to show snapshot pic
};

#endif // NODE_H
