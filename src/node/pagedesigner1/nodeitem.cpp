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
//gobal function to draw node elements
void DrawNodeItems(NodeItem *itnode,const QPointF &point)
{
    qreal WTxt=0; //get the EditTxt box width
    qreal HTxt=0;  //get the EditTxt box heigth
    qreal Wattach=0;
    for(int i=0; i<(itnode->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(itnode->childItems()).at(i);
        if(item->type() == TextItemType){
            TextItem *it=dynamic_cast<TextItem*>(item);
            WTxt=it->getTextSize().width(); //get the EditTxt box width
            HTxt=it->getTextSize().height();  //get the EditTxt box heigth
            it->setPos(SmileySize+point.x(),point.y()+SmileyHalfSize-15);

        }
        else if(item->type() ==  AttachmentItemType){
            if (itnode->hasAttachment()==NodeItem::Empty)
                break;
            else if (itnode->hasAttachment()==NodeItem::Weblink || itnode->hasAttachment()==NodeItem::Attachment)
            {
                //draw attachment ico
                AttachmentItem *it=dynamic_cast<AttachmentItem*>(item);
                //50!! -- TODO: hardcode
                Wattach=it->radius.width();
                //itnode->ExtendByRightSide(it->radius.width(),true);
            }
        }
    }

    for(int i=0; i<(itnode->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(itnode->childItems()).at(i);
        switch (item->type()) {
        case BoxItemType:{
            BoxItem *itbox=dynamic_cast<BoxItem*>(item);
            //int boxWidth=(WTxt+SmileySize)*1.1;
            int boxWidth=(WTxt+SmileySize)*1.1+Wattach;
            int boxHight=HTxt>SmileySize?HTxt:SmileySize;
            QRect rect_(QPoint(point.x(),point.y()), QSize(boxWidth,boxHight));
            itbox->setPos(rect_.center());
            itbox->setRect(QRectF(QPointF(-rect_.width() / 2.0,
                                   -rect_.height() / 2.0), rect_.size()));
            itnode->m_PosRightMiddle=QPointF(point.x()+rect_.width(),point.y()+rect_.height()/2);
            break;
        }
        case SmileyItemType:{
            SmileyItem *it=dynamic_cast<SmileyItem*>(item);
            it->setPos(point.x()+SmileyHalfSize,point.y()+SmileyHalfSize);
            break;
        }
        case TextItemType:{
            break;
        }
        case AttachmentItemType:{
            if (itnode->hasAttachment()==NodeItem::Empty)
                break;
            else if (itnode->hasAttachment()==NodeItem::Weblink || itnode->hasAttachment()==NodeItem::Attachment)
            {
                //draw attachment ico
                AttachmentItem *it=dynamic_cast<AttachmentItem*>(item);
                it->setPos(itnode->m_PosRightMiddle.x()-Wattach,itnode->m_PosRightMiddle.y());
                //itnode->ExtendByRightSide(it->radius.width(),true);
            }

            break;
        }

        }
    }
}
NodeItem::ItemType NodeItem::hasAttachment()
{
    return this->m_added;
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
        m_added=Weblink;
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
    qDebug() <<tr("Insert an attachment: %1 here!").arg(fileName);
    AttachmentItem *pAttachItem = new AttachmentItem(this->pos(),QPixmap(":/attachment.png"));
    pAttachItem->setFileName(fileName);
    pAttachItem->radius=QPixmap(":/attachment.png").size();
    this->addToGroup(pAttachItem);
    pAttachItem->setPos(m_PosRightMiddle);
    ExtendByRightSide(pAttachItem->radius.width(),true);
}
void NodeItem::addWebLink()
{
    //add a web link here
    bool ok;
    QString Strweblink = QInputDialog::getText(0, tr("QInputDialog::getText()"),
                                         tr("WebLink:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    qDebug()<<tr("Insert a web link here: %1!").arg(Strweblink);
    AttachmentItem *pAttachItem = new AttachmentItem(this->pos(),QPixmap(":/weblink.png"));
    pAttachItem->setFileName(Strweblink);
    pAttachItem->radius=QPixmap(":/weblink.png").size();
    this->addToGroup(pAttachItem);
    //pAttachItem->setPos(m_PosRightMiddle.x(),m_PosRightMiddle.y()+pAttachItem->radius.width());
    pAttachItem->setPos(m_PosRightMiddle);
    ExtendByRightSide(pAttachItem->radius.width(),true);
}

NodeItem::NodeItem(const QPointF &point,QGraphicsScene *scene) :
    QGraphicsItemGroup()
{
    QGraphicsItem *itemBox = 0;
    QGraphicsItem *itemSmile = 0;
    QGraphicsItem *itemTxt = 0;
    m_added=Empty;
    m_PosRightMiddle=QPointF(-1,-1);
    itemSmile = new SmileyItem(QPoint(1,1), scene);
    TextItemDialog dialog(0, QPoint(1,1), scene, 0);
      if (dialog.exec())
          itemTxt = dialog.textItem();
    itemBox = new BoxItem(QRect(QPoint(1,1), QSize(1,1)), scene);
    this->addToGroup(itemBox);
    this->addToGroup(itemSmile);
    this->addToGroup(itemTxt);
    DrawNodeItems(this,point); //redraw this the normal size
    this->setFlags(QGraphicsItem::ItemIsMovable
                   |QGraphicsItem::ItemSendsScenePositionChanges
                   |QGraphicsItem::ItemSendsGeometryChanges); //let all move togather
    itemBox->setZValue(BoxItemType);
    //itemBox->setParentItem(this);
    itemSmile->setZValue(SmileyItemType);
    //itemSmile->setParentItem(this);
    itemTxt->setZValue(TextItemType);
    //itemTxt->setParentItem(this);
    //qDebug()<<"BOX:"<<itemBox->parentItem();
    //qDebug()<<"Smile:"<<itemSmile->parentItem();
    //qDebug()<<"Txt:"<<itemTxt->parentItem();

}
void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //go here
    QPointF posxy=event->scenePos();
    qDebug()<<this->childItems();
    //qDebug()<<"Mouse Pos:"<<posxy;
    bool isTextChanged=false;
    qint32 Wnew=0,Xnew=0;
    for(int i=0; i<(this->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        //only Text Item response to double click event
        if(item->type() == TextItemType)
        {
            qDebug()<<"double click Text Item here";
            TextItem *it=dynamic_cast<TextItem*>(item);
            qreal Wold=it->getTextSize().width();
            if (it->contains(posxy))
            {
                it->edit();
                Wnew=it->getTextSize().width();
                if(Wnew!=Wold)
                {
                    isTextChanged=true;
                    Xnew=Wnew-Wold;
                }
                qDebug()<<"Changed Text Item here";
            }
            break;
        }
    }
    ExtendByRightSide(Xnew,isTextChanged);
}

void NodeItem::ExtendByRightSide(qint32 dx,bool isTextChanged)
{
    for(int i=0; i<(this->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        //only Text Item response to double click event
        if(!isTextChanged)
            break;
        if(item->type() == BoxItemType)
        {
            qDebug()<<"Change Size of Box item now!";
            BoxItem *itbox=dynamic_cast<BoxItem*>(item);
                QRectF rectangle(itbox->rect());
                rectangle.setRight(rectangle.right()+dx); //done!
                itbox->setRect(rectangle);
                //this->m_PosRightMiddle.setX(this->m_PosRightMiddle.x()+dx);
                //test move,it works
                //this->moveBy(Xnew,0);
            //itemTxt->setX(xt);  //also update its sub menber's pos
                //emit(itbox->dirty());
                //scene()->update();
        }
    }
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
        DrawNodeItems(this,posxy);
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
        QGraphicsItem *item=(this->childItems()).at(i);
        switch (item->type()) {
            case BoxItemType:{
            BoxItem *it=dynamic_cast<BoxItem*>(item);
            bool isclickme=it->contains(posxy);
            if(event->button() ==Qt::RightButton && isclickme)
            {
                //right click event
                edit();
                qDebug()<<"Right Click BoxItem here";
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
            if(it->contains(posxy))
            {
                //
                it->openURL();
            }
        }

        }
     }

}


#if 0
//not work, if has, no node group is shown
QVariant NodeItem::itemChange(GraphicsItemChange change,
                                const QVariant &value)
{
    if (isDirtyChange(change))
    {
        //emit dirty();
        for(int i=0; i<(this->childItems()).size();i++)
        {
            //for loop
            QGraphicsItem *item=(this->childItems()).at(i);
            switch (item->type()) {
            case BoxItemType:{
                BoxItem *itbox=dynamic_cast<BoxItem*>(item);
                itbox->itemChange(change,value);
                //qDebug()<<"click BoxItem here";
                break;
            }
            case SmileyItemType:{
                SmileyItem *it=dynamic_cast<SmileyItem*>(item);
                it->itemChange(change,value);
                break;
            }
            case TextItemType:{
                TextItem *it=dynamic_cast<TextItem*>(item);
                it->itemChange(change,value);
                break;
            }

            }
        }
        return QGraphicsItem::itemChange(change, value);
    }
}
#endif
