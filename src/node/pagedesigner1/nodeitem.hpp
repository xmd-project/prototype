#ifndef NODEITEM_HPP
#define NODEITEM_HPP

#include <QGraphicsItemGroup>
#if 1
class NodeItem :  public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit NodeItem(QObject *parent = 0);
    NodeItem(const QPoint point,QGraphicsScene *scene);
    QList<QGraphicsItemGroup*> m_nodeitem;
signals:

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:

};
#endif
#endif // NODEITEM_HPP
