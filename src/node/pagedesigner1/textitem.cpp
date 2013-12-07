/*
    Copyright (c) 2009-10 Qtrac Ltd. All rights reserved.

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "aqp.hpp"
#include "global.hpp"
#include "textitem.hpp"
#include "textitemdialog.hpp"
#include <QGraphicsView>
#include <QRect>
#include <QFontMetricsF>


TextItem::TextItem(const QPoint &position, QGraphicsScene *scene)
    : QGraphicsTextItem(), m_angle(0.0), m_shearHorizontal(0.0),
      m_shearVertical(0.0)
{
    setFont(QFont("Helvetica", 11));
    setFlags(QGraphicsItem::ItemIsSelectable|
#if QT_VERSION >= 0x040600
             QGraphicsItem::ItemSendsGeometryChanges|
#endif
             QGraphicsItem::ItemIsMovable);
    setPos(position);
    scene->clearSelection();
    scene->addItem(this);
    setSelected(true);
}


void TextItem::edit()
{
    QWidget *window = 0;
    QList<QGraphicsView*> views = scene()->views();
    if (!views.isEmpty())
        window = views.at(0)->window();
    TextItemDialog dialog(this, QPoint(), scene(), window);
    if (dialog.exec())
        emit dirty();
}

bool TextItem::contains(const QPointF &point) const
{
    bool ret;
    //reimp, true if point in this item,
    //check if the current mouse point is within the EditTxt box

    //QFontMetricsF fm(this->font());
    //qreal WTxt=this->getTextSize().width; //get the EditTxt box width
    //qreal HTxt=fm.height();  //get the EditTxt box heigth
    //qDebug()<<this->x()<<":"<<this->y()<<"|"<<WTxt<<":"<<HTxt
    //          <<"|"<<point.x()<<":"<<point.y()<<endl;
    qDebug()<<this->x()<<":"<<this->y()<<"|"<<this->getTextSize()
              <<"|"<<point.x()<<":"<<point.y()<<endl;
    //ret=(QRect(this->x(),this->y(),this->getTextSize().width(),this->getTextSize().height()).contains(point.x(),point.y());
    ret=(QRect(QPoint(this->x(),this->y()),this->getTextSize())).contains(point.x(),point.y());
    return ret;

}
QSize TextItem::getTextSize() const
{
    QFontMetricsF fm(this->font());
    //qreal WTxt=fm.width(this->toHtml()); //get the EditTxt box width,cause very long width
    qreal WTxt=fm.width(this->toPlainText()); //get the EditTxt box width
    qreal HTxt=fm.height();  //get the EditTxt box heigth
    return QSize(WTxt,HTxt);
}
void TextItem::setAngle(double angle)
{
    if (isSelected() && !qFuzzyCompare(m_angle, angle)) {
        m_angle = angle;
        updateTransform();
    }
}


void TextItem::setShear(double shearHorizontal, double shearVertical)
{
    if (isSelected() &&
        (!qFuzzyCompare(m_shearHorizontal, shearHorizontal) ||
         !qFuzzyCompare(m_shearVertical, shearVertical))) {
        m_shearHorizontal = shearHorizontal;
        m_shearVertical = shearVertical;
        updateTransform();
    }
}


void TextItem::updateTransform()
{
    QTransform transform;
    transform.shear(m_shearHorizontal, m_shearVertical);
    transform.rotate(m_angle);
    setTransform(transform);
}


QVariant TextItem::itemChange(GraphicsItemChange change,
                              const QVariant &value)
{
    if (isDirtyChange(change))
        emit dirty();
    return QGraphicsTextItem::itemChange(change, value);
}


QDataStream &operator<<(QDataStream &out, const TextItem &textItem)
{
    out << textItem.pos() << textItem.angle()
        << textItem.shearHorizontal() << textItem.shearVertical()
        << textItem.zValue() << textItem.toHtml();
    return out;
}


QDataStream &operator>>(QDataStream &in, TextItem &textItem)
{
    QPointF position;
    double angle;
    double shearHorizontal;
    double shearVertical;
    double z;
    QString html;
    in >> position >> angle >> shearHorizontal >> shearVertical >> z
       >> html;
    textItem.setPos(position);
    textItem.setAngle(angle);
    textItem.setShear(shearHorizontal, shearVertical);
    textItem.setZValue(z);
    textItem.setHtml(html);
    return in;
}
