#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class NodeWidget;
}
QT_END_NAMESPACE

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeWidget(QWidget *parent = 0);
    ~NodeWidget();

signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::NodeWidget *ui;
    QPoint oldPos;
};

#endif // NODEWIDGET_H
