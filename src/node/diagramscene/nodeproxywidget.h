#ifndef NODEPROXYWIDGET_H
#define NODEPROXYWIDGET_H

#include <QGraphicsProxyWidget>
#include <QPointF>

class Arrow;

class NodeProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    enum { Type = UserType + 115 };
    explicit NodeProxyWidget(QGraphicsItem *parent = 0);
    ~NodeProxyWidget() {}
    int type() const { return Type;}

    void removeArrow(Arrow *arrow);
    void removeArrows();
    void addArrow(Arrow *arrow);

signals:

public slots:

protected:
#if 0
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
#endif
private:
    QList<Arrow *> arrows;
    QPointF oldPos;
};

#endif // NODEPROXYWIDGET_H
