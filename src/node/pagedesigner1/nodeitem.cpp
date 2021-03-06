#include "nodeitem.hpp"
#include "itemtypes.hpp"
#include "smileyitem.hpp"
#include "nodeitem.hpp"
#include "boxitem.hpp"
#include "textitemdialog.hpp"
#include "textitem.hpp"
#include "global.hpp"
#include "aqp.hpp"
#include "alt_key.hpp"
#include <QInputDialog>
#include <QLineEdit>
using namespace SmileyConst;
//function to draw node elements
void NodeItem::DrawNodeItems(const QPointF &point)
{
    int WTxt=0; //get the EditTxt box width
    int HTxt=0;  //get the EditTxt box heigth
    int Wattach=0;
    int Nchild=this->childItems().size();  //NodeItem's child number
    int iattr=this->m_attachment_num;
    if (Nchild==0)
        return;
    for(int i=0; i<Nchild;i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        if(item->type() == TextItemType){
            TextItem *it=dynamic_cast<TextItem*>(item);
            WTxt=it->getTextSize().width(); //get the EditTxt box width
            HTxt=it->getTextSize().height();  //get the EditTxt box heigth
            it->setPos(SmileySize+point.x(),point.y()+SmileyHalfSize-15);
        }
        else if(item->type() ==  AttachmentItemType){
            if (!this->hasAttachment())
                break;
            else
            {
                //draw attachment ico
                AttachmentItem *it=dynamic_cast<AttachmentItem*>(item);
                //50!! -- TODO: hardcode
                Wattach=it->radius.width()>Wattach?it->radius.width():Wattach; //get the bigger width
                //this->ExtendByRightSide(it->radius.width(),true);
            }
        }
    }

    for(int i=0; i<Nchild;i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        if (item->type() == BoxItemType) {
            BoxItem *itbox=dynamic_cast<BoxItem*>(item);
            //int boxWidth=(WTxt+SmileySize)*1.1;
            int boxWidth=(WTxt+SmileySize)*1.1+Wattach*this->get_attachment_num();
            int boxHight=HTxt>SmileySize?HTxt:SmileySize;
            QRect rect_(QPoint(point.x(),point.y()), QSize(boxWidth,boxHight));
            itbox->setPos(rect_.center());
            itbox->setRect(QRectF(QPointF(-rect_.width() / 2.0,
                                          -rect_.height() / 2.0), rect_.size()));
            this->m_PosRightMiddle=QPointF(point.x()+rect_.width(),point.y()+rect_.height()/2);
            break;
        }
    }
    for(int i=0; i<Nchild;i++)
    {
        QGraphicsItem *item=(this->childItems()).at(i);
        if (item->type() ==SmileyItemType) {
            SmileyItem *it=dynamic_cast<SmileyItem*>(item);
            it->setPos(point.x()+SmileyHalfSize,point.y()+SmileyHalfSize);
        }
        else if (item->type() ==AttachmentItemType) {
            if (!this->hasAttachment())
                break;
            else
            {
                //draw attachment ico
                AttachmentItem *it=dynamic_cast<AttachmentItem*>(item);
                it->setPos(this->m_PosRightMiddle.x()-iattr*Wattach,this->m_PosRightMiddle.y());
                //this->m_PosRightMiddle.setX(this->m_PosRightMiddle.x()+Wattach);
                //this->ExtendByRightSide(it->radius.width(),true);
                iattr--;
            }
        }
    }
}
bool NodeItem::hasAttachment()
{
    return this->m_attachment_num>0;
}

void NodeItem::edit()
{
    QMenu menu;
    QActionGroup *group = new QActionGroup(this);
    QAction *addWebLinkAction = createMenuAction(&menu, QIcon(":/weblink.png"),
            tr("Web link"), m_added==Weblink,group,Weblink);
    connect(addWebLinkAction, SIGNAL(triggered(bool)),
            this, SLOT(addWebLink()));
    menu.addSeparator();
    createMenuAction(&menu, QIcon(":/attachment.png"),
            tr("Attachment"), m_added == Attachment,group,Attachment);

    AQP::accelerateMenu(&menu);
    QAction *chosen = menu.exec(QCursor::pos());
    if (chosen /*&& chosen != addWebLinkAction */)
    {
        setSelectedItem(static_cast<ItemType>(chosen->data().toInt()));
    }
}

void NodeItem::setSelectedItem(ItemType it)
{
    if (it==Weblink)
    {
        //no needed beacuse addWebLinlk is a slot function and connected into a signal!
        //addWebLink();
        //m_added=Weblink;
        ;
    }
    else if(it==Attachment)
    {
        m_added = Attachment;
        addAttachment();
    }

}
QAction *NodeItem::createMenuAction(QMenu *menu, const QIcon &icon,
        const QString &text, bool checked, QActionGroup *group,
        const QVariant &data)
{
    QAction *action = menu->addAction(icon, text);
    action->setCheckable(true);
    action->setChecked(checked);
    if (group)
        group->addAction(action);
    action->setData(data);
    return action;
}

void NodeItem::addAttachment()
{
    //add an attachment into the node
    QString fileName = QFileDialog::getOpenFileName(0, tr("Open File"),
                                                    ".",
                                                    tr("attachment (*.pdf *.txt *.jpg)"));
    if(fileName.isEmpty())
        return;
    qDebug() <<tr("Insert an attachment: %1 here!").arg(fileName);
    AttachmentItem *pAttachItem = new AttachmentItem(this->pos(),QPixmap(":/attachment.png"));
    pAttachItem->setFileName(fileName);
    pAttachItem->radius=QPixmap(":/attachment.png").size();
    addToGroup(pAttachItem);
    pAttachItem->setPos(m_PosRightMiddle);
    m_attachment_num++;
    //redraw NodeItems at the current position
    DrawNodeItems(this->childrenBoundingRect().topLeft());
}
void NodeItem::addWebLink()
{
    //add a web link here
    bool ok;
    QString Strweblink = QInputDialog::getText(0, tr("QInputDialog::getText()"),
                                         tr("WebLink:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if(Strweblink.isEmpty())
        return;
    qDebug()<<tr("Insert a web link here: %1!").arg(Strweblink);
    AttachmentItem *pAttachItem = new AttachmentItem(this->pos(),QPixmap(":/weblink.png"));
    pAttachItem->setFileName(Strweblink);
    pAttachItem->radius=QPixmap(":/weblink.png").size();
    addToGroup(pAttachItem);
    pAttachItem->setPos(m_PosRightMiddle);
    m_attachment_num++;
    m_added=Weblink;
    DrawNodeItems(this->childrenBoundingRect().topLeft());
}

NodeItem::NodeItem(const QPointF &point,QGraphicsScene *scene) :
    QGraphicsItemGroup()
{
    QGraphicsItem *itemBox = 0;
    QGraphicsItem *itemSmile = 0;
    QGraphicsItem *itemTxt = 0;

    m_added=Empty;
    m_attachment_num=0;
    m_PosRightMiddle=QPointF(-1,-1);
    itemSmile = new SmileyItem(QPoint(1,1), scene);
    TextItemDialog dialog(0, QPoint(1,1), scene, 0);
      if (dialog.exec())
          itemTxt = dialog.textItem();
    itemBox = new BoxItem(QRect(QPoint(1,1), QSize(1,1)), scene);
    this->addToGroup(itemBox);
    this->addToGroup(itemSmile);
    this->addToGroup(itemTxt);
    DrawNodeItems(point); //redraw this the normal size
    this->setFlags(QGraphicsItem::ItemIsMovable
                   |QGraphicsItem::ItemSendsScenePositionChanges
                   |QGraphicsItem::ItemSendsGeometryChanges); //let all move togather
    this->setHandlesChildEvents(true);
    itemBox->setZValue(BoxItemType);
    itemSmile->setZValue(SmileyItemType);
    itemTxt->setZValue(TextItemType);
#if 0
    //itemTxt->setParentItem(this);
    //qDebug()<<"BOX:"<<itemBox->parentItem();
    //qDebug()<<"Smile:"<<itemSmile->parentItem();
    //qDebug()<<"Txt:"<<itemTxt->parentItem();
    //for testing
    QRectF pt=this->childrenBoundingRect();
    bool bl=this->filtersChildEvents(); //false
    bool bl1=this->handlesChildEvents();//true
    QPointF pf=this->mapToItem(itemSmile,QPointF(1,1));
    QPointF pf1=this->scenePos();
    pf1=this->pos();
    QRectF pfx=this->mapRectToScene(pt);
    itemTxt=NULL;
#endif
}
void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //go here
    QPointF posxy=event->scenePos();
    qDebug()<<this->childItems();
    //qDebug()<<"Mouse Pos:"<<posxy;
    for(int i=0; i<(this->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        //only Text Item response to double click event
        if(item->type() == TextItemType)
        {
            qDebug()<<"double click Text Item here";
            TextItem *it=dynamic_cast<TextItem*>(item);
            if (it->contains(posxy))
            {
                it->edit();
            }
            break;
        }
    }
    DrawNodeItems(this->childrenBoundingRect().topLeft());
}


void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousehold=false;
}
void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //Mouse Move event processing go here
    if(m_mousehold) {
        QPointF posxy=event->scenePos();     //QPointF posxy=event->pos();
        //qDebug()<<this->childItems();
        //qDebug()<<"Mouse Pos:"<<posxy;
        DrawNodeItems(posxy);
    }
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Mouse press event processing go here
    QPointF posxy=event->scenePos();     //QPointF posxy=event->pos();
    //qDebug()<<this->childItems();
    //qDebug()<<"Mouse Pos:"<<posxy;
    m_mousehold=true;
    for(int i=0; i<(this->childItems()).size();i++)
    {
        //for loop
        qDebug()<<"mouse press loop:"<<i;
        QGraphicsItem *item=(this->childItems()).at(i);
        switch (item->type()) {
        case BoxItemType:{
            qDebug()<<"Click BoxItem here"<<i;
            //BoxItem *it=dynamic_cast<BoxItem*>(item);
            //bool isclickme=it->contains(posxy);
            //check if the pos within scene axis locates in BoxItem since it's the biggest child
            bool isclickme=this->childrenBoundingRect().contains(posxy);
            if(event->button() ==Qt::RightButton && isclickme)
            {
                //right click event
                edit();
                qDebug()<<"Right Click BoxItem here"<<i;
                return; //to avoid double enter in this section
            }
            break;
        }
        case SmileyItemType:{
            SmileyItem *it=dynamic_cast<SmileyItem*>(item);
            if(it->contains(posxy) && event->button() == Qt::LeftButton)
                //the 2 below not work, since the different XY system(item vs. scene )
                //if((it->shape()).contains(posxy) && event->button() == Qt::LeftButton)
                //if((it->boundingRect()).contains(posxy) && event->button() == Qt::LeftButton)
            {
                //show the context window
                it->edit();
                qDebug()<<"Click & Change Smiely Item here";
            }
            break;
        }
        case TextItemType:{
            TextItem *it=dynamic_cast<TextItem*>(item);
            if (it->contains(posxy))
                qDebug()<<"Click Text Item here";
            break;
        }
        case AttachmentItemType:{
            AttachmentItem *it=dynamic_cast<AttachmentItem*>(item);
            if(it->contains(posxy) && event->button() == Qt::LeftButton)
            {
                //any other way to emit/invok child's signal?
                it->openURL();
            }
        }

        }
    }

}


