#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <cassert>
#include <QDebug>

namespace {
#ifndef QT_NO_DEBUG
void testNodesAndArrows(Scene *scene)
{
    assert(scene);
    enum {OFFSETX=-600, OFFSETY=-500, DISTANCE=150};
    Node *node1 = new Node;
    Node *node2 = new Node;
    Node *node3 = new Node;
    Node *node4 = new Node;
    Node *centerNode = new Node;
    Node *node6 = new Node;
    Node *node7 = new Node;
    Node *node8 = new Node;
    Node *node9 = new Node;
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(centerNode);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node2, centerNode));
    scene->addItem(new Edge(node3, node6));
    scene->addItem(new Edge(node4, node1));
    scene->addItem(new Edge(node4, centerNode));
    scene->addItem(new Edge(centerNode, node6));
    scene->addItem(new Edge(centerNode, node8));
    scene->addItem(new Edge(node6, node9));
    scene->addItem(new Edge(node7, node4));
    scene->addItem(new Edge(node8, node7));
    scene->addItem(new Edge(node9, node8));

    node1->setPos(OFFSETX-DISTANCE, OFFSETY-DISTANCE);
    node2->setPos(OFFSETX, OFFSETY-DISTANCE);
    node3->setPos(OFFSETX+DISTANCE, OFFSETY-DISTANCE);
    node4->setPos(OFFSETX-DISTANCE, OFFSETY);
    centerNode->setPos(OFFSETX, OFFSETY);
    node6->setPos(OFFSETX+DISTANCE, OFFSETY);
    node7->setPos(OFFSETX-DISTANCE, OFFSETY+DISTANCE);
    node8->setPos(OFFSETX, OFFSETY+DISTANCE);
    node9->setPos(OFFSETX+DISTANCE, OFFSETY+DISTANCE);
}
#endif // QT_NO_DEBUG
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _scene(new Scene),
    _view(new QGraphicsView)
{
    _ui->setupUi(this);

    _view->setScene(_scene);
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //_view->scale(qreal(0.8), qreal(0.8));
    _view->setMinimumSize(600, 600);
    _view->setWindowTitle(tr("Node and Arrow Example"));
    //set drag mode to select widgets
    _view->setDragMode(QGraphicsView::RubberBandDrag);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_view);
    _ui->centralWidget->setLayout(layout);
    createActions();
    createToolbar();
    createConnections();

    setWindowTitle(tr("XMD Prototype"));
#ifndef QT_NO_DEBUG
    testNodesAndArrows(_scene); // Test
#endif // QT_NO_DEBUG
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::createActions()
{

    _addRectAction = new QAction(QIcon(":/addrect.png"),
            tr("Add Rect..."), this);
    _addLineAction = new QAction(QIcon(":/addline.png"),
            tr("Add Line..."), this);
    _addArrowAction = new QAction(QIcon(":/addarrow.png"),
            tr("Add Arrow..."), this);
    _addCircleAction = new QAction(QIcon(":/addcircle.png"),
            tr("Add Circle..."), this);
    _addCurveAction = new QAction(QIcon(":/addcurve.png"),
            tr("Add Curve..."), this);
    _editCopyAction = new QAction(QIcon(":/editcopy.png"),
            tr("Copy..."), this);
    _editCutAction = new QAction(QIcon(":/editcut.png"),
            tr("Copy..."), this);
    _editPasteAction = new QAction(QIcon(":/editpaste.png"),
            tr("Copy..."), this);
}

void MainWindow::createConnections()
{
    connect(_addRectAction, SIGNAL(triggered()),
            this, SLOT(addRect()));
    connect(_addLineAction, SIGNAL(triggered()),
            this, SLOT(addLine()));
    connect(_addArrowAction, SIGNAL(triggered()),
            this, SLOT(addArrow()));
    connect(_addCircleAction, SIGNAL(triggered()),
            this, SLOT(addCircle()));
    connect(_addCurveAction,SIGNAL(triggered()),
            this, SLOT(addCurve()));
    connect(_editCopyAction, SIGNAL(triggered()),
            this, SLOT(editCopy()));
    connect(_editPasteAction, SIGNAL(triggered()),
            this, SLOT(editPaste()));
    connect(_editCutAction,SIGNAL(triggered()),
            this, SLOT(editCut()));
}
void MainWindow::createToolbar()
{
    QAction *separator=0;
    QToolBar *addShapToolBar = addToolBar(tr("AddShap"));
    populateMenuAndToolBar(addShapToolBar, QList<QAction*>()
            << _addRectAction << _addCircleAction << _addCurveAction
            << _addLineAction << _addArrowAction
            << separator << _editCopyAction
            << _editCutAction << _editPasteAction << separator);
}

void MainWindow::populateMenuAndToolBar(QToolBar *toolBar, QList<QAction*> actions)
{
    foreach (QAction *action, actions) {
        if (!action) {
            toolBar->addSeparator();
        }
        else {
            toolBar->addAction(action);
        }
    }
}
void MainWindow::addRect()
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(0);
    rect->setFlags(QGraphicsItem::ItemIsSelectable|
#if QT_VERSION >= 0x040600
             QGraphicsItem::ItemSendsGeometryChanges|
#endif
             QGraphicsItem::ItemIsMovable|
             QGraphicsItem::ItemIsFocusable);
    QRect rect_=QRect(-620,-730,50,60);
    rect->setPos(rect_.center());
    rect->setRect(QRectF(QPointF(-rect_.width() / 2.0,
                           -rect_.height() / 2.0), rect_.size()));
    _scene->clearSelection();
    rect->setSelected(true);
    rect->setFocus();
    _scene->addItem(rect);
    //qDebug()<<"add rect item...";
}

void MainWindow::addLine()
{

}
void MainWindow::addArrow()
{
}

void MainWindow::addCircle()
{

}
void MainWindow::addCurve()
{

}

void MainWindow::editCopy()
{

}

void MainWindow::editPaste()
{

}

void MainWindow::editCut()
{

}

