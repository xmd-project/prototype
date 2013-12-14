#ifndef ATTACHMENTITEM_H
#define ATTACHMENTITEM_H

#include <QGraphicsPixmapItem>
#include <QString>
class AttachmentItem : public QGraphicsPixmapItem
{
public:
    AttachmentItem(const QPointF &position,QPixmap pic);
    void setFileName(QString filename){m_fileName=filename;}
    QString getFileName(){return m_fileName;}
    int type() const;
    QSize radius;
    bool contains(const QPointF &point) const;
    void openURL();
private:
    QString m_fileName;
protected:
    void mousePressEvent(QKeyEvent *event);

};

#endif // ATTACHMENTITEM_H
