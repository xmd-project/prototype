#ifndef XMDNODEDATA_H
#define XMDNODEDATA_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QPushButton>
#include <QString>
class Datpair{
public:
    Datpair(){qPushbtn=0;strData="";}
    Datpair(QPushButton *qp,QString str)
    {
        qPushbtn=qp;
        strData=str;
    }
    ~Datpair(){delete qPushbtn;}
    Datpair& operator =(const Datpair &other)
    {
        qPushbtn=other.qPushbtn;
        strData=other.strData;
        return *this;
    }

    QPushButton *qPushbtn;
    QString strData;
};

class XmdNodeData : public QObject
{
    Q_OBJECT
public:
    explicit XmdNodeData(QObject *parent = 0);
    QList<Datpair*> get_nodeMarker(){return m_nodeMarker;}
    void set_nodeMarker(Datpair *it){m_nodeMarker.append(it);}
    QList<QString> get_nodeText(){return m_nodeText;}
    void set_nodeText(QString it){m_nodeText.append(it);}
    QList<Datpair*> get_nodeAttachment() {return m_nodeAttachment;}
    void set_nodeAttachment(Datpair *it) {m_nodeAttachment.append(it);}


signals:

public slots:
private:
    QList<Datpair*> m_nodeMarker;
    QList<QString> m_nodeText;
    QList<Datpair*> m_nodeAttachment;
};

#endif // XMDNODEDATA_H
