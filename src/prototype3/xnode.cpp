#include "xnode.h"
#include "xid.h"
#include "xtextdocument.h"

struct XNodeImpl
{
    XNodeImpl();
    ~XNodeImpl();

    XId *_id;
    XTextDocument *_doc;
    QGraphicsItem *_graphics;
};

XNodeImpl::XNodeImpl() :
    _id(new XId),
    _doc(0),
    _graphics(0)
{
}

XNodeImpl::~XNodeImpl()
{
    delete _id;
    if (_doc)
        delete _doc;
    if (_graphics)
        delete _graphics;

}

XNode::XNode() : _impl(new XNodeImpl)
{
}

void XNode::setGraphics(QGraphicsItem *graphics)
{
    Q_ASSERT(graphics);
    if (_impl->_graphics)
        delete _impl->_graphics; // destroy last graphics
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
