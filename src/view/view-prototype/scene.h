#ifndef SCENE_H
#define SCENE_H

#include "global.h"
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QGraphicsLineItem;
class Node;
QT_END_NAMESPACE

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);
    void setShape(ShapeType shape) { _shape = shape; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    QGraphicsLineItem *_edgeIndicator;
    ShapeType _shape;
    Node *_currentNode;

};

#endif // SCENE_H
