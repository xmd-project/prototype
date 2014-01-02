#ifndef NODEWIDGETPROXY_H
#define NODEWIDGETPROXY_H

#include <QGraphicsProxyWidget>

class NodeProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    NodeProxyWidget(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags=0,QPoint pos=QPoint(1,1));

signals:
public slots:
protected:
    bool sceneEvent(QEvent *event);
private:
};

#endif // NODEWIDGETPROXY_H
