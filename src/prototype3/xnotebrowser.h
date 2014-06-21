#ifndef XNOTEBROWSER_H
#define XNOTEBROWSER_H

#include <QTextBrowser>

struct XNoteBrowserImpl;

class XNoteBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit XNoteBrowser(QWidget *parent = 0);

signals:

public slots:

private:
    XNoteBrowserImpl *_impl;

};

#endif // XNOTEBROWSER_H
