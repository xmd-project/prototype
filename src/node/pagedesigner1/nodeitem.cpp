#include "nodeitem.hpp"
#include "itemtypes.hpp"
#include "smileyitem.hpp"
#include "nodeitem.hpp"
#include "boxitem.hpp"
#include "textitemdialog.hpp"
#include "textitem.hpp"
#include "global.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

using namespace SmileyConst;
//gobal function to draw node elements
void DrawNodeItems(NodeItem *itnode,const QPointF &point)
{
    qreal WTxt=0; //get the EditTxt box width
    qreal HTxt=0;  //get the EditTxt box heigth
    for(int i=0; i<(itnode->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(itnode->childItems()).at(i);
        if(item->type() == TextItemType){
            TextItem *it=dynamic_cast<TextItem*>(item);
            WTxt=it->getTextSize().width(); //get the EditTxt box width
            HTxt=it->getTextSize().height();  //get the EditTxt box heigth
            it->setPos(SmileySize+point.x(),point.y()+SmileyHalfSize-15);
            break;
        }

    }
    for(int i=0; i<(itnode->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(itnode->childItems()).at(i);
        switch (item->type()) {
        case BoxItemType:{
            BoxItem *itbox=dynamic_cast<BoxItem*>(item);
            QRect rect_(QPoint(point.x(),point.y()), QSize((WTxt+SmileySize)*1.1, HTxt>SmileySize?HTxt:SmileySize));
            itbox->setPos(rect_.center());
            itbox->setRect(QRectF(QPointF(-rect_.width() / 2.0,
                                   -rect_.height() / 2.0), rect_.size()));
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

        }
    }
}

NodeItem::NodeItem(const QPointF &point,QGraphicsScene *scene) :
    QGraphicsItemGroup()
{
    QGraphicsItem *itemBox = 0;
    QGraphicsItem *itemSmile = 0;
    QGraphicsItem *itemTxt = 0;

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
                rectangle.setRight(rectangle.right()+Xnew); //done!
                itbox->setRect(rectangle);
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
            qDebug()<<"Click BoxItem here";
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
