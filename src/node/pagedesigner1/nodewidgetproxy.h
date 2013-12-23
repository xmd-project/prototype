#ifndef NODEWIDGETPROXY_H
#define NODEWIDGETPROXY_H

#include <QGraphicsProxyWidget>

class XmdNodeWidgetProxy : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    XmdNodeWidgetProxy(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags=0,QPoint pos=QPoint(1,1));

signals:
    void dirty();
public slots:
protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //TODO: use mouseReleaseEvent can let the widget move with mouse, but block the signal/slot of
    //nodewidget,why?
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    bool m_pressed;
};

#endif // NODEWIDGETPROXY_H
