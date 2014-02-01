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
    _view->setScene(_scene);
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //_view->scale(qreal(0.8), qreal(0.8));
    _view->setMinimumSize(_INIT_VIEW_WIDTH, _INIT_VIEW_HEIGHT);
    //_view->setWindowTitle(tr("Node and Arrow Example"));
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

void XMainWindow::initActions()
{
    _openAction = new QAction(QIcon(":/icon/images/open.png"), tr("&Open"), this);
    _openAction->setShortcut(tr("Ctrl+O"));
    _openAction->setToolTip(tr("Open (Ctrl+O)"));
    connect(_openAction, SIGNAL(triggered()), this, SLOT(_open()));

    _saveAction = new QAction(QIcon(":/icon/images/save.png"), tr("&Save"), this);
    _saveAction->setShortcut(tr("Ctrl+S"));
    _saveAction->setToolTip(tr("Save (Ctrl+S)"));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(_save()));

    _delAction = new QAction(QIcon(":/icon/images/delete.png"), tr("&Delete"), this);
    _delAction->setShortcut(tr("Del"));
    _delAction->setToolTip(tr("Delete (Del)"));
    connect(_delAction, SIGNAL(triggered()), this, SLOT(_del()));

    _undoAction = new QAction(QIcon(":/icon/images/undo.png"), tr("&Undo"), this);
    _undoAction->setShortcut(tr("Ctrl+Z"));
    _undoAction->setToolTip(tr("Undo (Ctrl+Z)"));
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(_undo()));

    _redoAction = new QAction(QIcon(":/icon/images/redo.png"), tr("&Redo"), this);
    _redoAction->setShortcut(tr("Ctrl+Y"));
    _redoAction->setToolTip(tr("Redo (Ctrl+Y)"));
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(_redo()));

    _findAction = new QAction(QIcon(":/icon/images/find.png"), tr("&Find"), this);
    _findAction->setShortcut(tr("Ctrl+F"));
    _findAction->setToolTip(tr("Find (Ctrl+F)"));
    connect(_findAction, SIGNAL(triggered()), this, SLOT(_find()));

    _cutAction = new QAction(QIcon(":/icon/images/cut.png"), tr("&Cut"), this);
    _cutAction->setShortcut(tr("Ctrl+X"));
    _cutAction->setToolTip(tr("Cut (Ctrl+X)"));
    connect(_cutAction, SIGNAL(triggered()), this, SLOT(_cut()));

    _copyAction = new QAction(QIcon(":/icon/images/copy.png"), tr("&Copy"), this);
    _copyAction->setShortcut(tr("Ctrl+C"));
    _copyAction->setToolTip(tr("Copy (Ctrl+C)"));
    connect(_copyAction, SIGNAL(triggered()), this, SLOT(_copy()));

    _pasteAction = new QAction(QIcon(":/icon/images/paste.png"), tr("&Paste"), this);
    _pasteAction->setShortcut(tr("Ctrl+V"));
    _pasteAction->setToolTip(tr("Paste (Ctrl+V)"));
    connect(_pasteAction, SIGNAL(triggered()), this, SLOT(_paste()));

    _addRectAction = new QAction(QIcon(":/icon/images/rectangle.png"), tr("&Rectangle"), this);
    _addRectAction->setShortcut(tr("Alt+R"));
    _addRectAction->setToolTip(tr("Rectangle (Alt+R)"));
    connect(_addRectAction, SIGNAL(triggered()), this, SLOT(_addRect()));

    _addLineAction = new QAction(QIcon(":/icon/images/line.png"), tr("&Line"), this);
    _addLineAction->setShortcut(tr("Alt+L"));
    _addLineAction->setToolTip(tr("Line (Alt+L)"));
    connect(_addLineAction, SIGNAL(triggered()), this, SLOT(_addLine()));

    _addOvalAction = new QAction(QIcon(":/icon/images/oval.png"), tr("&Oval"), this);
    _addOvalAction->setShortcut(tr("Alt+O"));
    _addOvalAction->setToolTip(tr("Oval (Alt+O)"));
    connect(_addOvalAction, SIGNAL(triggered()), this, SLOT(_addOval()));

    _addTextAction = new QAction(QIcon(":/icon/images/text.png"), tr("&Text"), this);
    _addTextAction->setShortcut(tr("Alt+T"));
    _addTextAction->setToolTip(tr("Text (Alt+T)"));
    connect(_addTextAction, SIGNAL(triggered()), this, SLOT(_addText()));

    _addCurveAction = new QAction(QIcon(":/icon/images/curve.png"), tr("&Curve"), this);
    _addCurveAction->setShortcut(tr("Alt+C"));
    _addCurveAction->setToolTip(tr("Curve (Alt+C)"));
    connect(_addCurveAction, SIGNAL(triggered()), this, SLOT(_addCurve()));

    _addPolygonAction = new QAction(QIcon(":/icon/images/polygon.png"), tr("&Polygon"), this);
    _addPolygonAction->setShortcut(tr("Alt+P"));
    _addPolygonAction->setToolTip(tr("Polygon (Alt+P)"));
    connect(_addPolygonAction, SIGNAL(triggered()), this, SLOT(_addPolygon()));

    _bringForwardAction = new QAction(QIcon(":/icon/images/bring_forward.png"), tr("Bring &Forward"), this);
    _bringForwardAction->setShortcut(tr("Alt+F"));
    _bringForwardAction->setToolTip(tr("Bring Forward (Alt+F)"));
    connect(_bringForwardAction, SIGNAL(triggered()), this, SLOT(_bringForward()));

    _sendBackwardAction = new QAction(QIcon(":/icon/images/send_backward.png"), tr("Send &Backward"), this);
    _sendBackwardAction->setShortcut(tr("Alt+B"));
    _sendBackwardAction->setToolTip(tr("Send Backward (Alt+B)"));
    connect(_sendBackwardAction, SIGNAL(triggered()), this, SLOT(_sendBackward()));

    _groupAction = new QAction(QIcon(":/icon/images/group.png"), tr("&Group"), this);
    _groupAction->setShortcut(tr("Alt+G"));
    _groupAction->setToolTip(tr("Group (Alt+G)"));
    connect(_groupAction, SIGNAL(triggered()), this, SLOT(_group()));

    _ungroupAction = new QAction(QIcon(":/icon/images/ungroup.png"), tr("&Ungroup"), this);
    _ungroupAction->setShortcut(tr("Alt+U"));
    _ungroupAction->setToolTip(tr("Ungroup (Alt+U)"));
    connect(_ungroupAction, SIGNAL(triggered()), this, SLOT(_ungroup()));

    _rotateAction = new QAction(QIcon(":/icon/images/rotate.png"), tr("&Rotate"), this);
    _rotateAction->setShortcut(tr("Ctrl+R"));
    _rotateAction->setToolTip(tr("Rotate (Ctrl+R)"));
    connect(_rotateAction, SIGNAL(triggered()), this, SLOT(_rotate()));
}

void XMainWindow::initToolBars()
{
    initActions();

    _fileToolBar = addToolBar(tr("File"));
    _fileToolBar->addAction(_openAction);
    _fileToolBar->addAction(_saveAction);

    _editToolBar = addToolBar(tr("Edit"));
    _editToolBar->addAction(_delAction);
    _editToolBar->addAction(_undoAction);
    _editToolBar->addAction(_redoAction);
    _editToolBar->addAction(_findAction);

    _clipboardToolBar = addToolBar(tr("Clipboard"));
    _clipboardToolBar->addAction(_cutAction);
    _clipboardToolBar->addAction(_copyAction);
    _clipboardToolBar->addAction(_pasteAction);

    _drawAddToolBar = addToolBar(tr("Add"));
    _drawAddToolBar->addAction(_addRectAction);
    _drawAddToolBar->addAction(_addLineAction);
    _drawAddToolBar->addAction(_addOvalAction);
    _drawAddToolBar->addAction(_addTextAction);
    _drawAddToolBar->addAction(_addCurveAction);
    _drawAddToolBar->addAction(_addPolygonAction);

    _drawArrangeToolBar = addToolBar(tr("Arrange"));
    _drawArrangeToolBar->addAction(_bringForwardAction);
    _drawArrangeToolBar->addAction(_sendBackwardAction);
    _drawArrangeToolBar->addAction(_groupAction);
    _drawArrangeToolBar->addAction(_ungroupAction);
    _drawArrangeToolBar->addAction(_rotateAction);
}

void XMainWindow::_save()
{
}

void XMainWindow::_open()
{
}

void XMainWindow::_del()
{
}

void XMainWindow::_undo()
{
}

void XMainWindow::_redo()
{
}

void XMainWindow::_find()
{
}

void XMainWindow::_addRect()
{
}

void XMainWindow::_addLine()
{
}

void XMainWindow::_addOval()
{
}

void XMainWindow::_addText()
{
}

void XMainWindow::_addCurve()
{
}

void XMainWindow::_addPolygon()
{
}

void XMainWindow::_bringForward()
{
}

void XMainWindow::_sendBackward()
{
}

void XMainWindow::_group()
{
}

void XMainWindow::_ungroup()
{
}

void XMainWindow::_rotate()
{
}

void XMainWindow::_cut()
{
}

void XMainWindow::_copy()
{
}

void XMainWindow::_paste()
{
}
