#include "nodewidget.h"
#include "ui_form.h"
#include "ui_nodewidgetexample.h"
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QInputDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsProxyWidget>
//test
QRubberBand *rubberBand=0;
QPoint origin;
NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent), /*_ui(new Ui::NodeWidget),*/_uiNode(new Ui::Form),_data(new NodeData)
{
    //_ui->setupUi(this);
    _uiNode->setupUi(this);
    _uiNode->HlayoutMarker->setDirection(QBoxLayout::RightToLeft);
    _getFocus=false;
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/showgrid.png")));
    this->setPalette(palette);
    //let widget expending and shrink with the content
    this->adjustSize();
}

NodeWidget::~NodeWidget()
{
    delete _uiNode;
    //delete _ui;
}

void NodeWidget::setProxy(QGraphicsProxyWidget *proxy)
{
    _proxy = proxy;
}

void NodeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    //qDebug()<<"add mouseDoubleClickEvent Qwidget";
    QString Str = QInputDialog::getText(0, tr("Input Dialog"),
                                        tr("Add Text Note:"), QLineEdit::Normal,0,0);
    if(Str.isEmpty())
        return;
    _uiNode->label->setText(Str);
    _data->setNodeText(Str);
    this->adjustSize();
}


void NodeWidget::openAttachment()
{
    //qDebug()<<"add openAttachment";
    foreach (Datpair* it,_data->getNodeAttachment()){
        if(it->_pushbutton==sender()){
            //qDebug()<<"Sender:"<<sender();
            QDesktopServices::openUrl((QUrl::fromLocalFile(it->_strData)));
        }
    }
}

void NodeWidget::openMarker()
{
    //qDebug()<<"add openMarker";
    foreach (Datpair* it,_data->getNodeMarker()){
        if(it->_pushbutton==sender()){
            //qDebug()<<"Sender:"<<sender();
            QDesktopServices::openUrl((QUrl::fromLocalFile(it->_strData)));
        }
    }
}

#if 0
void NodeWidget::zoominImage()
{
    //show Image with the original size in the Widget like xmind
    //we don't it that, but show the snapshot over the widget
    qDebug()<<"zoominImage...";
    QPixmap screen;
    screen.load(_Imagetest);
    QLabel *label = new QLabel(this);
    _uiNode->HlayoutAttachment->addWidget(label);
    label->resize(400, 200);
    QPixmap pix = screen.scaled(label->size(), Qt::KeepAspectRatio,
                                Qt::SmoothTransformation);
    label->setPixmap(pix);

}
#endif

void NodeWidget::addMarkerAttachment()
{
    //qDebug()<<"add web link to Qwidget";
    QString inputstr,defaultstr;
    DataType curType;
    QAction *ita=qobject_cast<QAction*>(sender());
    if(ita->data().toInt()==MarkerItem){
        inputstr=tr("Add Marker:");
        curType=MarkerItem;
        defaultstr=tr("www.163.com");
    } else if (ita->data().toInt() ==AttachmentItem) {
        inputstr=tr("Add Attachment");
        curType=AttachmentItem;
        defaultstr=tr("c:/a.log");
    } else if (ita->data().toInt() == ImageItem) {
        inputstr=tr("Add Image");
        curType=ImageItem;
        defaultstr=tr("c:/test.jpg");
    } else {
        inputstr=tr("Add Unknown Type...");
    }
    QString Strtmp = QInputDialog::getText(0, tr("InputDialog"),
                                    inputstr, QLineEdit::Normal,defaultstr, 0);
    if(Strtmp.isEmpty())
        return;
    if (curType != ImageItem) {
    QPushButton *pushbutton=new QPushButton;
    Datpair *it=new Datpair(pushbutton,Strtmp);
    if(curType==MarkerItem) {
        pushbutton->setIcon(QIcon(":/weblink.png"));
        pushbutton->setFixedWidth(QPixmap(":/weblink.png").size().width());
        _uiNode->HlayoutMarker->addWidget(pushbutton);
        _data->setNodeMarker(it);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openMarker()));
    } else if (curType==AttachmentItem) {
        pushbutton->setIcon(QIcon(":/attachment.png"));
        pushbutton->setFixedWidth(QPixmap(":/attachment.png").size().width());
        _uiNode->HlayoutAttachment->addWidget(pushbutton);
        _data->setNodeAttachment(it);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openAttachment()));
    }
    } else  {//if (curType==ImageItem)
        NodeImagePushButton *pushbutton=new NodeImagePushButton(Strtmp);
        Datpair *it=new Datpair((QPushButton *)pushbutton,Strtmp);
        pushbutton->setIcon(QIcon(Strtmp));
        pushbutton->setFixedWidth(20); //todo hardcode
        _uiNode->HlayoutAttachment->addWidget(pushbutton);
        _data->setNodeAttachment(it);  //take Image file as attachment
        //connect two singals
        connect(pushbutton,SIGNAL(showimage(QString)),this,SIGNAL(showimage(QString)));
        connect(pushbutton,SIGNAL(closeimage()),this,SIGNAL(closeimage()));
    }

    this->adjustSize();
}
void NodeWidget::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"mat mousePressEvent";
    if (event->button()==Qt::RightButton){
        QMenu menu;
        _addMarkerAction = menu.addAction(QIcon(":/weblink.png"), tr("Web link"));
        _addMarkerAction->setCheckable(true);
        _addMarkerAction->setData(MarkerItem);
        connect(_addMarkerAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));

        _addAttachmentAction=menu.addAction(QIcon(":/attachment.png"),tr("Attachment"));
        connect(_addAttachmentAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));
        _addAttachmentAction->setCheckable(true);
        _addAttachmentAction->setData(AttachmentItem);

        _addImageAction=menu.addAction(QIcon(":/editaddimage.png"),tr("Image"));
        connect(_addImageAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));
        _addImageAction->setCheckable(true);
        _addImageAction->setData(ImageItem);
        menu.exec(QCursor::pos());
        }
    else if (event->button()==Qt::LeftButton){
        //qDebug()<<"set focus...";
        _getFocus=true;
        this->update();
    }
}

void NodeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    bool isSelectedParent=_proxy->isSelected();
    if(_getFocus || isSelectedParent){
        //qDebug()<<"draw  red rect...";
        QPen pen;  // creates a default pen

        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(3);
        pen.setBrush(Qt::red);
        painter.setPen(pen);
    } else {
        //QWidget::paintEvent(event);
        //qDebug()<<"draw default rect...";
    }
    painter.drawRect(this->rect());
}

void NodeWidget::enterEvent(QEvent *event)
{

    //qDebug()<<"mat EnterEvent";
    this->setWindowOpacity(0.5);
    QWidget::enterEvent(event);
}

void NodeWidget::leaveEvent(QEvent *event)
{
    //qDebug()<<"mat LeaveEvent";
    this->setWindowOpacity(1);
    QWidget::leaveEvent(event);
    _getFocus=false;
    this->update();
}

void NodeWidget::keyPressEvent(QKeyEvent *kevent)
{
    if(kevent->key() == Qt::Key_Delete) {
        //delete a Node as well as the edge pointed to it
        qDebug()<<"click delete key";

    }
}

