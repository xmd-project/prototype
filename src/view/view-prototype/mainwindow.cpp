#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <cassert>

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

    setWindowTitle(tr("XMD Prototype"));
#ifndef QT_NO_DEBUG
    testNodesAndArrows(_scene); // Test
#endif // QT_NO_DEBUG
}

MainWindow::~MainWindow()
{
    delete _ui;
}

