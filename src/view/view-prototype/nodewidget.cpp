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

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent), /*_ui(new Ui::NodeWidget),*/_uiNode(new Ui::Form),_data(new NodeData)
{
    //_ui->setupUi(this);
    _uiNode->setupUi(this);
    _uiNode->HlayoutMarker->setDirection(QBoxLayout::RightToLeft);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/showgrid.png")));
    this->setPalette(palette);
}

NodeWidget::~NodeWidget()
{
    delete _uiNode;
    //delete _ui;
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

void NodeWidget::addMarkerAttachment()
{
    //qDebug()<<"add web link to Qwidget";
    QString inputstr;
    DataType curType;
    QAction *ita=qobject_cast<QAction*>(sender());
    if(ita->data().toInt()==MarkerItem){
        inputstr=tr("Add Marker:");
        curType=MarkerItem;
    } else if (ita->data().toInt() ==AttachmentItem) {
        inputstr=tr("Add Attachment");
        curType=AttachmentItem;
    } else {
        inputstr=tr("Add Unknown Type...");
    }
    QString Strtmp = QInputDialog::getText(0, tr("InputDialog"),
                                    inputstr, QLineEdit::Normal,0, 0);
    if(Strtmp.isEmpty())
        return;
    QPushButton *pushbutton=new QPushButton;
    Datpair *it=new Datpair(pushbutton,Strtmp);
    if(curType==MarkerItem) {
        pushbutton->setIcon(QIcon(":/weblink.png"));
        pushbutton->setFixedWidth(QPixmap(":/weblink.png").size().width());
        _uiNode->HlayoutMarker->addWidget(pushbutton);
        _data->setNodeMarker(it);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openMarker()));
    } else if (curType==AttachmentItem) {
        _data->setNodeAttachment(it);
        pushbutton->setIcon(QIcon(":/attachment.png"));
        pushbutton->setFixedWidth(QPixmap(":/attachment.png").size().width());
        _uiNode->HlayoutAttachment->addWidget(pushbutton);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openAttachment()));
    }
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
        _addAttachmentAction=menu.addAction(QIcon(":/attachment.png"),
                tr("Attachment"));
        connect(_addAttachmentAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));
        _addAttachmentAction->setCheckable(true);
        _addAttachmentAction->setData(AttachmentItem);
        menu.exec(QCursor::pos());
        }
}
