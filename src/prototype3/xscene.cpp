#include "xscene.h"
#include "xid.h"

struct XSceneImpl
{
    XSceneImpl();
    ~XSceneImpl();

    XId *_id;
};

XSceneImpl::XSceneImpl() :
    _id(new XId)
{
}

XSceneImpl::~XSceneImpl()
{
    delete _id;
}

XScene::XScene(QObject *parent) :
    QGraphicsScene(parent),
    _impl(new XSceneImpl)
{
}

XScene::~XScene()
{
    delete _impl;
}

void XScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}
void XScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void XScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
