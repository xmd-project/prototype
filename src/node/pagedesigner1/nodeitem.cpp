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
#if 1
using namespace SmileyConst;
NodeItem::NodeItem(const QPoint point,QGraphicsScene *scene) :
    QGraphicsItemGroup()
{
    /*QGraphicsItemGroup *m_nodeitem = 0;
    m_nodeitem = new QGraphicsItemGroup(parent);*/
    QGraphicsItem *itemBox = 0;
    QGraphicsItem *itemSmile = 0;
    QGraphicsItem *itemTxt = 0;

    itemSmile = new SmileyItem(QPoint(point.x()+SmileyHalfSize,point.y()+SmileyHalfSize), scene);
    TextItemDialog dialog(0, QPoint(SmileySize+point.x(),point.y()+SmileyHalfSize-15), scene, 0);
      if (dialog.exec())
          itemTxt = dialog.textItem();
    TextItem *it=dynamic_cast<TextItem*>(itemTxt);
    qreal WTxt=it->getTextSize().width(); //get the EditTxt box width
    qreal HTxt=it->getTextSize().height();  //get the EditTxt box heigth

    itemBox = new BoxItem(QRect(QPoint(point.x(),point.y()), QSize((WTxt+SmileySize)*1.1, HTxt>SmileySize?HTxt:SmileySize)), scene);
    //another smart way to handle this 3 types obj?
    this->addToGroup(itemBox);
    this->addToGroup(itemSmile);
    this->addToGroup(itemTxt);
    this->setFlag(QGraphicsItem::ItemIsMovable); //let all move togather
    itemBox->setZValue(BoxItemType);
    //itemBox->setParentItem(this);
    itemSmile->setZValue(SmileyItemType);
    //itemSmile->setParentItem(this);
    itemTxt->setZValue(TextItemType);
    //itemTxt->setParentItem(this);
    qDebug()<<"BOX:"<<itemBox->parentItem();
    qDebug()<<"Smile:"<<itemSmile->parentItem();
    qDebug()<<"Txt:"<<itemTxt->parentItem();

}
void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //go here
    QPointF posxy=event->scenePos();
    qDebug()<<this->childItems();
    qDebug()<<"Mouse Pos:"<<posxy;
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
void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Mouse press event processing go here
    QPointF posxy=event->scenePos();     //QPointF posxy=event->pos();
    //qDebug()<<this->childItems();
    qDebug()<<"Mouse Pos:"<<posxy;
    for(int i=0; i<(this->childItems()).size();i++)
    {
        //for loop
        QGraphicsItem *item=(this->childItems()).at(i);
        switch (item->type()) {
            case BoxItemType:{
            //qDebug()<<"click BoxItem here";
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
                qDebug()<<"click Smiely Item here";
            }
            break;
        }
            case TextItemType:{
            TextItem *it=dynamic_cast<TextItem*>(item);
            if (it->contains(posxy))
                qDebug()<<"click Text Item here";
            break;
        }

        }
     }

}

#endif
