#ifndef NODEITEM_HPP
#define NODEITEM_HPP

#include <QGraphicsItemGroup>
#if 1
class NodeItem :  public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit NodeItem(QObject *parent = 0);
    NodeItem(const QPointF &point,QGraphicsScene *scene);
    QList<QGraphicsItemGroup*> m_nodeitem;
signals:
    void dirty();
private:
    bool m_mousehold;
protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//  QVariant itemChange(GraphicsItemChange change,
//                                  const QVariant &value);
public slots:

};
#endif
#endif // NODEITEM_HPP
