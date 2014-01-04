#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include "nodedata.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class QMouseEvent;
class QPushButton;

namespace Ui {
class NodeWidgetExample;
typedef NodeWidgetExample NodeWidget; // type alias
class Form;
}
QT_END_NAMESPACE

enum DataType{MarkerItem,AttachmentItem,TextItem};

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeWidget(QWidget *parent = 0);
    ~NodeWidget();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void addMarkerAttachment();
    void openMarker();
    void openAttachment();
private:
   //Ui::NodeWidget *_ui;
   Ui::Form *_uiNode;
   NodeData *_data;
   QAction *_addAttachmentAction;
   QAction *_addMarkerAction;
};

#endif // NODEWIDGET_H
