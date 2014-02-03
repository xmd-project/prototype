#ifndef XSCENE_H
#define XSCENE_H

#include <QGraphicsScene>

class XScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit XScene(QObject *parent = 0);

signals:
    void graphicsItemInserted(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

public:
    enum Mode {
        NORMAL,
        INS_RECT, INS_LINE, INS_OVAL, INS_TEXT, INS_CURVE, INS_POLYGON
    };

public slots:
    void setMode(Mode mode = NORMAL) { _mode = mode; }

private:
    Mode _mode;
    QGraphicsItem *_itemIndicator;
    QPointF _lastMousePressScenePos;
};

#endif // XSCENE_H
