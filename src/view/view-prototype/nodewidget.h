#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include "nodedata.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class QMouseEvent;
class QPushButton;
class QSize;
class QString;
namespace Ui {
class NodeWidgetExample;
typedef NodeWidgetExample NodeWidget; // type alias
class Form;
}
QT_END_NAMESPACE

class NodeImagePushButton:public QPushButton
{
    Q_OBJECT
public:
    NodeImagePushButton(QString image):_image(image)
    {
        //_image = image;
    }

signals:
    void showimage(QString);
    void closeimage();
protected:
    void enterEvent(QEvent *event){emit(showimage(_image));}
    void leaveEvent(QEvent *event){emit(closeimage());}
private:
    QString _image;
};

enum DataType{MarkerItem,AttachmentItem,TextItem,ImageItem};

class NodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeWidget(QWidget *parent = 0);
    ~NodeWidget();
    void setProxy(QGraphicsProxyWidget *proxy);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *);
    //void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);
public slots:
    void addMarkerAttachment();
    void openMarker();
    void openAttachment();
    //void zoominImage();
private:
   //Ui::NodeWidget *_ui;
   Ui::Form *_uiNode;
   NodeData *_data;
   //QString _Imagetest;
   QAction *_addAttachmentAction;
   QAction *_addMarkerAction;
   QAction *_addImageAction;
   bool _getFocus;
   QGraphicsProxyWidget *_proxy;
signals:
   void showimage(QString);
   void closeimage();


};

#endif // NODEWIDGET_H
