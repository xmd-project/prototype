#include "scene.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cassert>

Scene::Scene(QObject *parent) :
    QGraphicsScene (parent), _edgeIndicator (0)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(-1000, -1000, 1000, 1000));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->modifiers() == Qt::ShiftModifier && mouseEvent->button() == Qt::LeftButton) {
        Node *sourceNode = qgraphicsitem_cast<Node *>(itemAt(mouseEvent->scenePos(), QTransform()));
        if (sourceNode) {
            _edgeIndicator = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                                          mouseEvent->scenePos()));
            //edgeIndicator->setPen(QPen(...));
            addItem(_edgeIndicator);
        } else {
            return;
        }
    } else {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (_edgeIndicator != 0) { // is inserting an edge
        QLineF newLine(_edgeIndicator->line().p1(), mouseEvent->scenePos());
        _edgeIndicator->setLine(newLine);
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (_edgeIndicator != 0) { // insert a new edge
        QList<QGraphicsItem *> sourceItems = items(_edgeIndicator->line().p1());
        if (sourceItems.count() && sourceItems.first() == _edgeIndicator)
            sourceItems.removeFirst();
        QList<QGraphicsItem *> destItems = items(_edgeIndicator->line().p2());
        if (destItems.count() && destItems.first() == _edgeIndicator)
            destItems.removeFirst();

        removeItem(_edgeIndicator);
        delete _edgeIndicator;
        _edgeIndicator = 0;

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
    if (!itemAt(mouseEvent->scenePos(), QTransform())){
        _currentNode = new Node(mouseEvent->scenePos());
        addItem(_currentNode);
        //also add a shape attache to the Node
        if (_shape == Rect)
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem(_currentNode);
            rect->setFlags(QGraphicsItem::ItemIsSelectable|
               #if QT_VERSION >= 0x040600
                           QGraphicsItem::ItemSendsGeometryChanges|
               #endif
                           QGraphicsItem::ItemIsMovable|
                           QGraphicsItem::ItemIsFocusable);
            QRect rect_=QRect(0,_currentNode->size().height(),_currentNode->size().width(),80);
            //qDebug()<<"Rect:" << rect_ <<"lastp:"<<_lastPoint << " endP:"<<_endPoint;
            rect->setPos(rect_.center());
            rect->setRect(QRectF(QPointF(-rect_.width() / 2.0,
                                         -rect_.height() / 2.0), rect_.size()));
            clearSelection();
            rect->setSelected(true);
            rect->setFocus();
            addItem(rect);
            //_currentNode = 0;
        }

    }else{
        QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
    }
}
