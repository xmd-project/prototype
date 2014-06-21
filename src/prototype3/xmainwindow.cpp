#include "xmainwindow.h"
#include "ui_xmainwindow.h"
#include <QTabWidget>
#include <QList>

class XNoteBrowser;
//class XView;
//class XScene;

/// Pimple: customized stuff
struct XMainWindowImpl
{
    XMainWindowImpl();
    ~XMainWindowImpl();
    void setup();

    Ui::XMainWindow *_ui;
    XNoteBrowser *_xnoteBrowser;
    QList<QTabWidget *>_tabWidget;

    enum _ToolBarType { // DO NOT modify any of the following values!
        FILE, EDIT, CLIPBOARD, INSERT, ARRANGE, // and so on
        NUM_TOOLBARS // NUM_TOOLBARS must be the last element! It indicates how many toolbars there are.
    };
    QTabBar *_toolbar[NUM_TOOLBARS];

    enum _ActionType { // DO NOT modify any of the following values!
        SAVE, SAVEAS, OPEN,
        DEL, UNDO, REDO, FIND,
        INS_RECT, INS_LINE, INS_OVAL, INS_TEXT, INS_CURVE, INS_POLYGON,
        BRING_FORWARD, SEND_BACKWARD, GROUP, UNGROUP, ROTATE,
        CUT, COPY, PASTE, // and so on
        NUM_ACTIONS  // NUM_ACTIONS must be the last element! It indicates how many actions there are.
    };
    QAction *_action[NUM_TOOLBARS];
};

XMainWindowImpl::XMainWindowImpl() :
    _ui(new Ui::XMainWindow)
{
}

XMainWindowImpl::~XMainWindowImpl()
{
    delete _ui;
}

void XMainWindowImpl::setup()
{
    // TODO: set up all subobjects
}

XMainWindow::XMainWindow(QWidget *parent) :
    QMainWindow(parent),
    _impl(new XMainWindowImpl)
{
    _impl->_ui->setupUi(this);
}

XMainWindow::~XMainWindow()
{
    delete _impl;
}
