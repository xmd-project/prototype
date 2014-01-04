#ifndef XMDNODEDATA_H
#define XMDNODEDATA_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QPushButton>
#include <QString>
class Datpair{
public:
    Datpair(){_pushbutton=0;_strData="";}
    Datpair(QPushButton *qp,QString str)
    {
        _pushbutton=qp;
        _strData=str;
    }
    ~Datpair(){delete _pushbutton;}
    Datpair& operator =(const Datpair &other)
    {
        _pushbutton=other._pushbutton;
        _strData=other._strData;
        return *this;
    }

    QPushButton *_pushbutton;
    QString _strData;
};

class NodeData : public QObject
{
    Q_OBJECT
public:
    explicit NodeData(QObject *parent = 0);
    QList<Datpair*> getNodeMarker(){return _nodeMarker;}
    void setNodeMarker(Datpair *it){_nodeMarker.append(it);}
    QList<QString> getNodeText(){return _nodeText;}
    void setNodeText(QString it){_nodeText.append(it);}
    QList<Datpair*> getNodeAttachment() {return _nodeAttachment;}
    void setNodeAttachment(Datpair *it) {_nodeAttachment.append(it);}


signals:

public slots:
private:
    QList<Datpair*> _nodeMarker;
    QList<QString> _nodeText;
    QList<Datpair*> _nodeAttachment;
};

#endif // XMDNODEDATA_H
