#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include "ui_form.h"
#include "nodedata.h"
class QWidget;
class QMouseEvent;
class QPushButton;

enum DataType{MarkerItem,AttachmentItem,TextItem};

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeWidget(QWidget *parent = 0);
    ~NodeWidget();
signals:

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void addMarkerAttachment();
    void openMarker();
    void openAttachment();
private:
   Ui::Form *_uiNode;
   NodeData *_data;
   QAction *_addAttachmentAction;
   QAction *_addMarkerAction;
};

#endif // NODEWIDGET_H
