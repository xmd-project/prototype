#ifndef XVIEW_H
#define XVIEW_H

#include <QGraphicsView>

struct XViewImpl;

class XView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit XView(QWidget *parent = 0);
    ~XView();
    void setScene(QGraphicsScene *scene);

signals:

public slots:

private:
    XViewImpl *_impl;
};

#endif // XVIEW_H
