#include "node.h"
#include "edge.h"
#include "nodewidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <cassert>

void Node::init()
{
    setWidget(new NodeWidget);
    _snapshotimage=0;
    connect(this->widget(),SIGNAL(showimage(QString)),this,SLOT(showSnapShot(QString)));
    connect(this->widget(),SIGNAL(closeimage()),this,SLOT(closeSnapShot()));
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable
             |QGraphicsItem::ItemSendsScenePositionChanges);
}

Node::Node(QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent, Qt::Widget)
{
    init();
}

Node::Node(const QPointF &position, QGraphicsProxyWidget *parent) :
    QGraphicsProxyWidget(parent, Qt::Widget)
{
    init();
    setPos(position);
}

Node::~Node()
{
    delete _snapshotimage;
}
void Node::showSnapShot(QString imagefilename)
{
    //set scale factor (hard code)
    float scalex=1.8;
    float scaley=1.5;
    int imagewidth;
    int imageheight;
    if(imagefilename.isEmpty())
        return;
    if(!_snapshotimage)
        _snapshotimage =new QGraphicsPixmapItem(this);
    QPixmap pixmaphere;
    pixmaphere.load(imagefilename);
    imagewidth=pixmaphere.width()/scalex;
    imageheight=pixmaphere.height()/scaley;
    pixmaphere= pixmaphere.scaled(imagewidth,imageheight,Qt::IgnoreAspectRatio, Qt::FastTransformation); //or Qt::SmoothTransformation);
    _snapshotimage->setPixmap(pixmaphere);
    //show image in the centre
    _snapshotimage->setPos(QPointF(-imagewidth/2,-imageheight/2));
    this->scene()->addItem((_snapshotimage));
}

void Node::closeSnapShot()
{
    if(!_snapshotimage)
        return;
    this->scene()->removeItem(_snapshotimage);
    delete _snapshotimage;
    _snapshotimage=0;

}

void Node::addEdge(Edge *edge)
{
    assert(edge);
    _edges << edge;
    edge->adjust();
}

bool Node::sceneEvent(QEvent *event)
{
    bool result = QGraphicsProxyWidget::sceneEvent(event);
    if (event->type() == QEvent::GraphicsSceneMousePress
            || event->type() == QEvent::GraphicsSceneMouseRelease
            || event->type() == QEvent::GraphicsSceneMouseMove
            || event->type() == QEvent::GraphicsSceneMouseDoubleClick)
    {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            QGraphicsItem::mouseReleaseEvent((QGraphicsSceneMouseEvent *)(event));
        } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
            QGraphicsItem::mouseMoveEvent((QGraphicsSceneMouseEvent *)(event));
        } else if (event->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsItem::mousePressEvent((QGraphicsSceneMouseEvent *)(event));
        }
        event->setAccepted(true);
        return true;
    }
    return result;
}
#if 0
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
#endif
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //qDebug() << change;
    switch (change)
    {
    case ItemPositionHasChanged:
        foreach (Edge *edge, _edges)
            edge->adjust();
        break;
    default:
        break;
    };
    return QGraphicsProxyWidget::itemChange(change, value);
}
