#include "xview.h"
#include "xzoomwidget.h"
#include <QGraphicsProxyWidget>
#include <limits>

struct XViewImpl
{
    XViewImpl();
    ~XViewImpl();
    QGraphicsProxyWidget *_proxyZoomWidget; ///< always on top
};

XViewImpl::XViewImpl()
    : _proxyZoomWidget(0)
{
}

XViewImpl::~XViewImpl()
{
    if (_proxyZoomWidget)
        delete _proxyZoomWidget;
}

XView::XView(QWidget *parent) :
    QGraphicsView(parent),
    _impl(new XViewImpl)
{
}

XView::~XView()
{
    delete _impl;
}

void XView::setScene(QGraphicsScene *scene)
{
    Q_ASSERT(scene && _impl);
    _impl->_proxyZoomWidget = scene->addWidget(new XZoomWidget);
    // make sure the zoomWidget is always on top of the scene
    _impl->_proxyZoomWidget->setZValue(std::numeric_limits<qreal>::max());
    QGraphicsView::setScene(scene);
}
