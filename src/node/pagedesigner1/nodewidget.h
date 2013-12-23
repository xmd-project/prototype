#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "ui_form.h"
#include "xmdnodedata.h"
#include <QPushButton>
enum DataType{MarkerItem,AttachmentItem,TextItem};
typedef struct XmdWrappedData
{
    QList<QPair<QPushButton , QString > > m_marker;
    QPair<QLabel , QString > m_text;
    QList<QPair<QPushButton , QString > > m_attach;
}XmdWrappedData;

class XmdNodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit XmdNodeWidget(QWidget *parent = 0);
    ~XmdNodeWidget();
signals:

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *);
public slots:
    void addMarkerAttachment();
    //void addAttachment();
    void openMarker();
    void openAttachment();
private:
   Ui::Form *uiNode;
   XmdNodeData *data;
   //XmdWrappedData *wpData;
   QAction *addAttachmentAction;
   QAction *addMarkerAction;
};

#endif // NODEWIDGET_H
