#include "xnotebrowser.h"

class XTextDocument;

struct XNoteBrowserImpl
{
    XNoteBrowserImpl();
    ~XNoteBrowserImpl();

    XTextDocument *_doc;
};

XNoteBrowser::XNoteBrowser(QWidget *parent) :
    QTextBrowser(parent)
{
}
