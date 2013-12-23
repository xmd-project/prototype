#include "nodewidget.h"
#include "aqp.hpp"
#include "alt_key.hpp"
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QInputDialog>
#include <QLineEdit>
#include <QPair>

//QString Strweblink; //test
XmdNodeWidget::XmdNodeWidget(QWidget *parent) :
    QWidget(parent),uiNode(new Ui::Form),data(new XmdNodeData)
{
    uiNode->setupUi(this);
    //connect(uiNode->label,SIGNAL(onclick()),this,SLOT(changeTxt()));
}

XmdNodeWidget::~XmdNodeWidget()
{
    delete uiNode;
}

void XmdNodeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString Str = QInputDialog::getText(0, tr("Input Dialog"),
                                               tr("Add Text Note:"), QLineEdit::Normal,
                                               0, 0);
    if(Str.isEmpty())
        return;
    uiNode->label->setText(Str);
    data->get_nodeText().append(Str);

}


void XmdNodeWidget::openAttachment()
{
    foreach (Datpair* it,data->get_nodeAttachment())
    {
        if(it->qPushbtn == sender())
        {
            qDebug()<<"Sender:"<<sender();
            QDesktopServices::openUrl((QUrl::fromLocalFile(it->strData)));
        }
    }
}

void XmdNodeWidget::openMarker()
{
    foreach (Datpair* it,data->get_nodeMarker())
    {
        if(it->qPushbtn == sender())
        {
            qDebug()<<"Sender:"<<sender();
            QDesktopServices::openUrl((QUrl::fromLocalFile(it->strData)));
        }
    }
}

void XmdNodeWidget::addMarkerAttachment()
{
    qDebug()<<"add web link to Qwidget";
    QString inputstr;
    DataType curType;
    QAction *ita=qobject_cast<QAction*>(sender());
    if(ita->data().toInt()==MarkerItem)
    {
        inputstr=tr("Add Marker:");
        curType=MarkerItem;
    }
    else if (ita->data().toInt() ==AttachmentItem)
    {
        inputstr=tr("Add Attachment");
        curType=AttachmentItem;
    }
    else
        inputstr=tr("Add Unknown Type...");
    QString Strtmp = QInputDialog::getText(0, tr("InputDialog"),
                                               inputstr, QLineEdit::Normal,
                                               0, 0);
    if(Strtmp.isEmpty())
        return;
    QPushButton *pushbutton=new QPushButton;
    Datpair *it=new Datpair(pushbutton,Strtmp);
    if(curType==MarkerItem)
    {
        pushbutton->setIcon(QIcon(":/weblink.png"));
        pushbutton->setFixedWidth(QPixmap(":/weblink.png").size().width());
        uiNode->HlayoutMarker->addWidget(pushbutton);
        data->set_nodeMarker(it);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openMarker()));
    }
    else if (curType==AttachmentItem)
    {
        data->set_nodeAttachment(it);
        pushbutton->setIcon(QIcon(":/attachment.png"));
        pushbutton->setFixedWidth(QPixmap(":/attachment.png").size().width());
        uiNode->HlayoutAttachment->addWidget(pushbutton);
        connect(pushbutton,SIGNAL(clicked()),this,SLOT(openAttachment()));
    }
}
#if 0
void XmdNodeWidget::addAttachment()
{
    qDebug()<<"add web link to Qwidget";
    QString StrAttach = QInputDialog::getText(0, tr("QInputDialog::getText()"),
                                               tr("Add Attachment:"), QLineEdit::Normal,
                                               0, 0);
    if(StrAttach.isEmpty())
        return;
    QPushButton *pushbutton=new QPushButton;
    pushbutton->setIcon(QIcon(":/attachment.png"));
    pushbutton->setFixedWidth(QPixmap(":/attachment.png").size().width());
    uiNode->HlayoutAttachment->addWidget(pushbutton);
    Datpair *it=new Datpair(pushbutton,StrAttach);
    data->get_nodeAttachment().append(it);
    connect(pushbutton,SIGNAL(clicked()),this,SLOT(openAttachment()));
}

void XmdNodeWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void XmdNodeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ;
}
#endif
void XmdNodeWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse press at Qwidget";
    if (event->button()==Qt::RightButton){
        //context menu
        QMenu menu;
        addMarkerAction = menu.addAction(QIcon(":/weblink.png"), tr("Web link"));
        addMarkerAction->setCheckable(true);
        addMarkerAction->setData(MarkerItem);
        connect(addMarkerAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));
        addAttachmentAction=menu.addAction(QIcon(":/attachment.png"),
                tr("Attachment"));
        connect(addAttachmentAction, SIGNAL(triggered(bool)),this, SLOT(addMarkerAttachment()));
        addAttachmentAction->setCheckable(true);
        addAttachmentAction->setData(AttachmentItem);
        AQP::accelerateMenu(&menu);
        QAction *chosen = menu.exec(QCursor::pos());
    }
}

