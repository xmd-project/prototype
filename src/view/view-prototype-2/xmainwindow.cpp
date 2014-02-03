#include "xmainwindow.h"
#include "xscene.h"
#include "xgraphicsview.h"
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>

XMainWindow::XMainWindow(QWidget *parent) :
    QMainWindow(parent),
    _scene(new XScene),
    _view(new XGraphicsView)
{
    initCentralWidget();
    initToolBars();
}

void XMainWindow::initView()
{
    // setting scene rectangle is necessary for creating and locating a graphics item
    _scene->setSceneRect(QRectF(0, 0, _INIT_XSCENE_WIDTH, _INIT_XSCENE_HEIGHT));

    _view->setScene(_scene);
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    _view->setMinimumSize(_INIT_XVIEW_WIDTH, _INIT_XVIEW_HEIGHT);
    //set drag mode to select a group of widgets
    _view->setDragMode(QGraphicsView::RubberBandDrag);
}

void XMainWindow::initCentralWidget()
{
    initView();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_view);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle(tr("XMD Prototype (Version 2)"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void XMainWindow::initToolBars()
{
    initFileToolBar();
    initEditToolBar();
    initClipboardToolBar();
    initAddToolBar();
    initArrangeToolBar();
}

void XMainWindow::initFileToolBar()
{
    QToolBar *tb = 0;
    QAction *act = 0;

    tb = addToolBar(tr("File"));
    act = tb->addAction(QIcon(":/icon/images/open.png"), tr("&Open"), this, SLOT(open()));
    act->setShortcut(tr("Ctrl+O"));
    act->setToolTip(tr("Open (Ctrl+O)"));
    act = tb->addAction(QIcon(":/icon/images/save.png"), tr("&Save"), this, SLOT(save()));
    act->setShortcut(tr("Ctrl+S"));
    act->setToolTip(tr("Save (Ctrl+S)"));
}

void XMainWindow::initEditToolBar()
{
    QToolBar *tb = 0;
    QAction *act = 0;

    tb = addToolBar(tr("Edit"));
    act = tb->addAction(QIcon(":/icon/images/delete.png"), tr("&Delete"), this, SLOT(del()));
    act->setShortcut(tr("Del"));
    act->setToolTip(tr("Delete (Del)"));
    act = tb->addAction(QIcon(":/icon/images/undo.png"), tr("&Undo"), this, SLOT(undo()));
    act->setShortcut(tr("Ctrl+Z"));
    act->setToolTip(tr("Undo (Ctrl+Z)"));
    act = tb->addAction(QIcon(":/icon/images/redo.png"), tr("&Redo"), this, SLOT(redo()));
    act->setShortcut(tr("Ctrl+Y"));
    act->setToolTip(tr("Redo (Ctrl+Y)"));
    act = tb->addAction(QIcon(":/icon/images/find.png"), tr("&Find"), this, SLOT(find()));
    act->setShortcut(tr("Ctrl+F"));
    act->setToolTip(tr("Find (Ctrl+F)"));
}

void XMainWindow::initClipboardToolBar()
{
    QToolBar *tb = 0;
    QAction *act = 0;

    tb = addToolBar(tr("Clipboard"));
    act = tb->addAction(QIcon(":/icon/images/cut.png"), tr("&Cut"), this, SLOT(cut()));
    act->setShortcut(tr("Ctrl+X"));
    act->setToolTip(tr("Cut (Ctrl+X)"));
    act = tb->addAction(QIcon(":/icon/images/copy.png"), tr("&Copy"), this, SLOT(copy()));
    act->setShortcut(tr("Ctrl+C"));
    act->setToolTip(tr("Copy (Ctrl+C)"));
    act = tb->addAction(QIcon(":/icon/images/paste.png"), tr("&Paste"), this, SLOT(paste()));
    act->setShortcut(tr("Ctrl+V"));
    act->setToolTip(tr("Paste (Ctrl+V)"));
}

void XMainWindow::initAddToolBar()
{
    QToolBar *tb = 0;
    QAction *act = 0;

    tb = addToolBar(tr("Add"));
    act = tb->addAction(QIcon(":/icon/images/rectangle.png"), tr("&Rectangle"), this, SLOT(addRect()));
    act->setShortcut(tr("Alt+R"));
    act->setToolTip(tr("Rectangle (Alt+R)"));
    act = tb->addAction(QIcon(":/icon/images/line.png"), tr("&Line"), this, SLOT(addLine()));
    act->setShortcut(tr("Alt+L"));
    act->setToolTip(tr("Line (Alt+L)"));
    act = tb->addAction(QIcon(":/icon/images/oval.png"), tr("&Oval"), this, SLOT(addOval()));
    act->setShortcut(tr("Alt+O"));
    act->setToolTip(tr("Oval (Alt+O)"));
    act = tb->addAction(QIcon(":/icon/images/text.png"), tr("&Text"), this, SLOT(addText()));
    act->setShortcut(tr("Alt+T"));
    act->setToolTip(tr("Text (Alt+T)"));
    act = tb->addAction(QIcon(":/icon/images/curve.png"), tr("&Curve"), this, SLOT(addCurve()));
    act->setShortcut(tr("Alt+C"));
    act->setToolTip(tr("Curve (Alt+C)"));
    act = tb->addAction(QIcon(":/icon/images/polygon.png"), tr("&Polygon"), this, SLOT(addPolygon()));
    act->setShortcut(tr("Alt+P"));
    act->setToolTip(tr("Polygon (Alt+P)"));
}

void XMainWindow::initArrangeToolBar()
{
    QToolBar *tb = 0;
    QAction *act = 0;

    tb = addToolBar(tr("Arrange"));
    act = tb->addAction(QIcon(":/icon/images/bring_forward.png"), tr("Bring &Forward"), this, SLOT(bringForward()));
    act->setShortcut(tr("Alt+F"));
    act->setToolTip(tr("Bring Forward (Alt+F)"));
    act = tb->addAction(QIcon(":/icon/images/send_backward.png"), tr("Send &Backward"), this, SLOT(sendBackward()));
    act->setShortcut(tr("Alt+B"));
    act->setToolTip(tr("Send Backward (Alt+B)"));
    act = tb->addAction(QIcon(":/icon/images/group.png"), tr("&Group"), this, SLOT(group()));
    act->setShortcut(tr("Alt+G"));
    act->setToolTip(tr("Group (Alt+G)"));
    act = tb->addAction(QIcon(":/icon/images/ungroup.png"), tr("&Ungroup"), this, SLOT(ungroup()));
    act->setShortcut(tr("Alt+U"));
    act->setToolTip(tr("Ungroup (Alt+U)"));
    act = tb->addAction(QIcon(":/icon/images/rotate.png"), tr("&Rotate"), this, SLOT(rotate()));
    act->setShortcut(tr("Ctrl+R"));
    act->setToolTip(tr("Rotate (Ctrl+R)"));
}

void XMainWindow::save()
{
}

void XMainWindow::open()
{
}

void XMainWindow::del()
{
}

void XMainWindow::undo()
{
}

void XMainWindow::redo()
{
}

void XMainWindow::find()
{
}

void XMainWindow::addRect()
{
    _scene->setMode(XScene::INS_RECT);
}

void XMainWindow::addLine()
{
}

void XMainWindow::addOval()
{
}

void XMainWindow::addText()
{
}

void XMainWindow::addCurve()
{
}

void XMainWindow::addPolygon()
{
}

void XMainWindow::bringForward()
{
}

void XMainWindow::sendBackward()
{
}

void XMainWindow::group()
{
}

void XMainWindow::ungroup()
{
}

void XMainWindow::rotate()
{
}

void XMainWindow::cut()
{
}

void XMainWindow::copy()
{
}

void XMainWindow::paste()
{
}
