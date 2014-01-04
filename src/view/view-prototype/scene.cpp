#include "scene.h"

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
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
