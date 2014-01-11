#include "scene.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cassert>

Scene::Scene(QObject *parent) :
    QGraphicsScene (parent), edgeIndicator (0)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(-1000, -1000, 1000, 1000));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->modifiers() == Qt::ShiftModifier
            && mouseEvent->button() == Qt::LeftButton) {
        Node *sourceNode = qgraphicsitem_cast<Node *>(itemAt(mouseEvent->scenePos(), QTransform()));
        if (sourceNode) {
            edgeIndicator = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                                         mouseEvent->scenePos()));
            //edgeIndicator->setPen(QPen(...));
            addItem(edgeIndicator);
        } else {
            return;
        }
    } else {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (edgeIndicator != 0) { // is inserting an edge
        QLineF newLine(edgeIndicator->line().p1(), mouseEvent->scenePos());
        edgeIndicator->setLine(newLine);
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (edgeIndicator != 0) { // insert a new edge
        QList<QGraphicsItem *> sourceItems = items(edgeIndicator->line().p1());
        if (sourceItems.count() && sourceItems.first() == edgeIndicator)
            sourceItems.removeFirst();
        QList<QGraphicsItem *> destItems = items(edgeIndicator->line().p2());
        if (destItems.count() && destItems.first() == edgeIndicator)
            destItems.removeFirst();

        removeItem(edgeIndicator);
        delete edgeIndicator;
        edgeIndicator = 0;

        if (sourceItems.count() > 0 && destItems.count() > 0
                && sourceItems.first() != destItems.first()) { // avoid dangling edge
            Node *sourceNode = qgraphicsitem_cast<Node *>(sourceItems.first());
            Node *destNode = qgraphicsitem_cast<Node *>(destItems.first());
            if (sourceNode && destNode)
                addItem(new Edge(sourceNode, destNode));
        }
    } else {
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
