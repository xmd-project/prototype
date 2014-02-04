#include "xmainwindow.h"
#include "xscene.h"
#include "xgraphicsview.h"
#include "xrect.h"
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>

XMainWindow::XMainWindow(QWidget *parent) :
    QMainWindow(parent),
    _scene(new XScene),
    _view(new XGraphicsView)
{
    initXScene();
    initCentralWidget();
    initToolBars();
}

void XMainWindow::graphicsItemInserted(QGraphicsItem *item)
{
    _scene->setMode();
    _view->setDragMode(QGraphicsView::RubberBandDrag);
    switch (item->type()) {
    case XRect::Type: _action[INS_RECT]->setChecked(false); break;
    default:;
    }
}

void XMainWindow::initXScene()
{
    // setting scene rectangle is necessary for creating and locating a graphics item
    _scene->setSceneRect(QRectF(0, 0, _INIT_XSCENE_WIDTH, _INIT_XSCENE_HEIGHT));
    connect(_scene, SIGNAL(graphicsItemInserted(QGraphicsItem*)),
            this, SLOT(graphicsItemInserted(QGraphicsItem*)));
}

void XMainWindow::initXView()
{
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
    initXView();

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
    initInsertToolBar();
    initArrangeToolBar();
}

void XMainWindow::initFileToolBar()
{
    _toolBar[FILE] = addToolBar(tr("File"));
    _action[OPEN] = _toolBar[FILE]->addAction(QIcon(":/icon/images/open.png"), tr("&Open"), this, SLOT(open()));
    _action[OPEN]->setShortcut(tr("Ctrl+O"));
    _action[OPEN]->setToolTip(tr("Open (Ctrl+O)"));
    _action[OPEN]->setEnabled(false);
    _action[SAVE] = _toolBar[FILE]->addAction(QIcon(":/icon/images/save.png"), tr("&Save"), this, SLOT(save()));
    _action[SAVE]->setShortcut(tr("Ctrl+S"));
    _action[SAVE]->setToolTip(tr("Save (Ctrl+S)"));
    _action[SAVE]->setEnabled(false);
}

void XMainWindow::initEditToolBar()
{
    _toolBar[EDIT] = addToolBar(tr("Edit"));
    _action[DEL] = _toolBar[EDIT]->addAction(QIcon(":/icon/images/delete.png"), tr("&Delete"), this, SLOT(del()));
    _action[DEL]->setShortcut(tr("Del"));
    _action[DEL]->setToolTip(tr("Delete (Del)"));
    _action[DEL]->setEnabled(false);
    _action[UNDO] = _toolBar[EDIT]->addAction(QIcon(":/icon/images/undo.png"), tr("&Undo"), this, SLOT(undo()));
    _action[UNDO]->setShortcut(tr("Ctrl+Z"));
    _action[UNDO]->setToolTip(tr("Undo (Ctrl+Z)"));
    _action[UNDO]->setEnabled(false);
    _action[REDO] = _toolBar[EDIT]->addAction(QIcon(":/icon/images/redo.png"), tr("&Redo"), this, SLOT(redo()));
    _action[REDO]->setShortcut(tr("Ctrl+Y"));
    _action[REDO]->setToolTip(tr("Redo (Ctrl+Y)"));
    _action[REDO]->setEnabled(false);
    _action[FIND] = _toolBar[EDIT]->addAction(QIcon(":/icon/images/find.png"), tr("&Find"), this, SLOT(find()));
    _action[FIND]->setShortcut(tr("Ctrl+F"));
    _action[FIND]->setToolTip(tr("Find (Ctrl+F)"));
    _action[FIND]->setEnabled(false);
}

void XMainWindow::initClipboardToolBar()
{
    _toolBar[CLIPBOARD] = addToolBar(tr("Clipboard"));
    _action[CUT] = _toolBar[CLIPBOARD]->addAction(QIcon(":/icon/images/cut.png"), tr("&Cut"), this, SLOT(cut()));
    _action[CUT]->setShortcut(tr("Ctrl+X"));
    _action[CUT]->setToolTip(tr("Cut (Ctrl+X)"));
    _action[CUT]->setEnabled(false);
    _action[COPY] = _toolBar[CLIPBOARD]->addAction(QIcon(":/icon/images/copy.png"), tr("&Copy"), this, SLOT(copy()));
    _action[COPY]->setShortcut(tr("Ctrl+C"));
    _action[COPY]->setToolTip(tr("Copy (Ctrl+C)"));
    _action[COPY]->setEnabled(false);
    _action[PASTE] = _toolBar[CLIPBOARD]->addAction(QIcon(":/icon/images/paste.png"), tr("&Paste"), this, SLOT(paste()));
    _action[PASTE]->setShortcut(tr("Ctrl+V"));
    _action[PASTE]->setToolTip(tr("Paste (Ctrl+V)"));
    _action[PASTE]->setEnabled(false);
}

void XMainWindow::initInsertToolBar()
{
    // All insert actions are checkable
    _toolBar[INSERT] = addToolBar(tr("Insert"));
    _action[INS_RECT] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/rectangle.png"), tr("&Rectangle"), this, SLOT(insertRect()));
    _action[INS_RECT]->setShortcut(tr("Alt+R"));
    _action[INS_RECT]->setToolTip(tr("Rectangle (Alt+R)"));
    _action[INS_RECT]->setCheckable(true);
    _action[INS_LINE] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/line.png"), tr("&Line"), this, SLOT(insertLine()));
    _action[INS_LINE]->setShortcut(tr("Alt+L"));
    _action[INS_LINE]->setToolTip(tr("Line (Alt+L)"));
    _action[INS_LINE]->setCheckable(true);
    _action[INS_LINE]->setEnabled(false);
    _action[INS_OVAL] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/oval.png"), tr("&Oval"), this, SLOT(insertOval()));
    _action[INS_OVAL]->setShortcut(tr("Alt+O"));
    _action[INS_OVAL]->setToolTip(tr("Oval (Alt+O)"));
    _action[INS_OVAL]->setCheckable(true);
    _action[INS_OVAL]->setEnabled(false);
    _action[INS_TEXT] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/text.png"), tr("&Text"), this, SLOT(insertText()));
    _action[INS_TEXT]->setShortcut(tr("Alt+T"));
    _action[INS_TEXT]->setToolTip(tr("Text (Alt+T)"));
    _action[INS_TEXT]->setCheckable(true);
    _action[INS_TEXT]->setEnabled(false);
    _action[INS_CURVE] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/curve.png"), tr("&Curve"), this, SLOT(insertCurve()));
    _action[INS_CURVE]->setShortcut(tr("Alt+C"));
    _action[INS_CURVE]->setToolTip(tr("Curve (Alt+C)"));
    _action[INS_CURVE]->setCheckable(true);
    _action[INS_CURVE]->setEnabled(false);
    _action[INS_POLYGON] = _toolBar[INSERT]->addAction(QIcon(":/icon/images/polygon.png"), tr("&Polygon"), this, SLOT(insertPolygon()));
    _action[INS_POLYGON]->setShortcut(tr("Alt+P"));
    _action[INS_POLYGON]->setToolTip(tr("Polygon (Alt+P)"));
    _action[INS_POLYGON]->setCheckable(true);
    _action[INS_POLYGON]->setEnabled(false);
    // The action group is exclusive by default,
    // only one of the actions in the group is checked at any one time.
    QActionGroup *ag = new QActionGroup(this);
    ag->addAction(_action[INS_RECT]);
    ag->addAction(_action[INS_LINE]);
    ag->addAction(_action[INS_OVAL]);
    ag->addAction(_action[INS_TEXT]);
    ag->addAction(_action[INS_CURVE]);
    ag->addAction(_action[INS_POLYGON]);
}

void XMainWindow::initArrangeToolBar()
{
    _toolBar[ARRANGE] = addToolBar(tr("Arrange"));
    _action[BRING_FORWARD] = _toolBar[ARRANGE]->addAction(QIcon(":/icon/images/bring_forward.png"), tr("Bring &Forward"), this, SLOT(bringForward()));
    _action[BRING_FORWARD]->setShortcut(tr("Alt+F"));
    _action[BRING_FORWARD]->setToolTip(tr("Bring Forward (Alt+F)"));
    _action[BRING_FORWARD]->setEnabled(false);
    _action[SEND_BACKWARD] = _toolBar[ARRANGE]->addAction(QIcon(":/icon/images/send_backward.png"), tr("Send &Backward"), this, SLOT(sendBackward()));
    _action[SEND_BACKWARD]->setShortcut(tr("Alt+B"));
    _action[SEND_BACKWARD]->setToolTip(tr("Send Backward (Alt+B)"));
    _action[SEND_BACKWARD]->setEnabled(false);
    _action[GROUP] = _toolBar[ARRANGE]->addAction(QIcon(":/icon/images/group.png"), tr("&Group"), this, SLOT(group()));
    _action[GROUP]->setShortcut(tr("Alt+G"));
    _action[GROUP]->setToolTip(tr("Group (Alt+G)"));
    _action[GROUP]->setEnabled(false);
    _action[UNGROUP] = _toolBar[ARRANGE]->addAction(QIcon(":/icon/images/ungroup.png"), tr("&Ungroup"), this, SLOT(ungroup()));
    _action[UNGROUP]->setShortcut(tr("Alt+U"));
    _action[UNGROUP]->setToolTip(tr("Ungroup (Alt+U)"));
    _action[UNGROUP]->setEnabled(false);
    _action[ROTATE] = _toolBar[ARRANGE]->addAction(QIcon(":/icon/images/rotate.png"), tr("&Rotate"), this, SLOT(rotate()));
    _action[ROTATE]->setShortcut(tr("Ctrl+R"));
    _action[ROTATE]->setToolTip(tr("Rotate (Ctrl+R)"));
    _action[ROTATE]->setEnabled(false);
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

void XMainWindow::insertRect()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_RECT);
}

void XMainWindow::insertLine()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_LINE);
}

void XMainWindow::insertOval()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_OVAL);
}

void XMainWindow::insertText()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_TEXT);
}

void XMainWindow::insertCurve()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_CURVE);
}

void XMainWindow::insertPolygon()
{
    _view->setDragMode(QGraphicsView::NoDrag);
    _scene->setMode(XScene::INS_POLYGON);
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
