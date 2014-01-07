#include "scene.h"
#include "node.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene (parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(-1000, -1000, 1000, 1000));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
#if 0 //for testing
    QList<QGraphicsItem*> items = selectedItems();
    for (int i=0; i<items.count(); i++)
    {
        if(items.at(i)->isSelected()) {
            qDebug()<<"selected:"<<items.at(i);
        }
    }
#endif
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if (!itemAt(mouseEvent->scenePos(), QTransform()))
        addItem(new Node(mouseEvent->scenePos()));
    else
        QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
