#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class NodeWidgetExample;
typedef NodeWidgetExample NodeWidget; // type alias
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
private:
    Ui::NodeWidget *_ui;
};

#endif // NODEWIDGET_H
