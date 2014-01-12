#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void addRect();
    void addLine();
    void addArrow();
    void addCircle();
    void addCurve();
    void editCopy();
    void editPaste();
    void editCut();
private:
    Ui::MainWindow *_ui;
    Scene *_scene;
    QGraphicsView *_view;
    void createToolbar();
    void createActions();
    void createConnections();
    void populateMenuAndToolBar(QToolBar *toolBar, QList<QAction*> actions);
    QAction *_addRectAction;
    QAction *_addLineAction;
    QAction *_addArrowAction;
    QAction *_addCircleAction;
    QAction *_addCurveAction;
    QAction *_editCopyAction;
    QAction *_editCutAction ;
    QAction *_editPasteAction;

};

#endif // MAINWINDOW_H
