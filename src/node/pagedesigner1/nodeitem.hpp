#ifndef NODEITEM_HPP
#define NODEITEM_HPP

#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QFileDialog>
#include <QGraphicsItemGroup>
#include <QMenu>
#include "attachmentitem.h"

class QAction;
class QActionGroup;
#if 1
class NodeItem :  public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    enum ItemType{Weblink,Attachment,Empty};
    explicit NodeItem(QObject *parent = 0);
    NodeItem(const QPointF &point,QGraphicsScene *scene);
    void DrawNodeItems(const QPointF &point);
    //QList<QGraphicsItemGroup*> m_nodeitem;
    void edit();
    void setSelectedItem(ItemType it);
    bool hasAttachment();
    qint32 get_attachment_num(){return m_attachment_num;}
signals:
    void dirty();
private:
    bool m_mousehold;
    ItemType m_added;
    QPointF m_PosRightMiddle;
    qint32 m_attachment_num;
    void addAttachment();
    QAction *createMenuAction(QMenu *menu, const QIcon &icon,
            const QString &text, bool checked, QActionGroup *group,
            const QVariant &data);
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//  QVariant itemChange(GraphicsItemChange change,
//                                  const QVariant &value);
public slots:
    void addWebLink();

};
#endif
#endif // NODEITEM_HPP
