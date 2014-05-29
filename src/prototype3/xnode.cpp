#include "xnode.h"
#include "xnodedata.h"

struct XNodeImpl
{
    XNodeImpl();
    ~XNodeImpl();

    QGraphicsItem *_graphics;
    XNodeData *_data;
};

XNodeImpl::XNodeImpl() : _graphics(0), _data(0)
{
}

XNodeImpl::~XNodeImpl()
{
    if (_graphics)
        delete _graphics;
    if (_data)
        delete _data;
}

XNode::XNode() : _impl(new XNodeImpl)
{
}

void XNode::setGraphics(QGraphicsItem *graphics)
{
    Q_ASSERT(graphics);
    if (_impl->_graphics)
        delete _impl->_graphics; // destroy obsolete graphics
    _impl->_graphics = graphics;
}

XNode::~XNode()
{
    delete _impl;
}

QRectF XNode::boundingRect() const
{
    Q_ASSERT(_impl && _impl->_graphics);
    return _impl->_graphics->boundingRect();
}

void XNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_ASSERT(_impl && _impl->_graphics);
    _impl->_graphics->paint(painter, option, widget);
}

QPainterPath XNode::shape() const
{
    Q_ASSERT(_impl && _impl->_graphics);
    return _impl->_graphics->shape();
}
