#ifndef XSCENE_H
#define XSCENE_H

#include <QGraphicsScene>

struct XSceneImpl;

class XScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit XScene(QObject *parent = 0);
    ~XScene();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:

private:
    XSceneImpl *_impl;
};

#endif // XSCENE_H
