#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <QMainWindow>

class XScene;
class XGraphicsView;

QT_BEGIN_NAMESPACE
class QToolBar;
class QAction;
QT_END_NAMESPACE

class XMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit XMainWindow(QWidget *parent = 0);

private:
    XScene *_scene;
    XGraphicsView *_view;
    enum {_INIT_VIEW_WIDTH = 500, _INIT_VIEW_HEIGHT = 400};
private:
    void initView();
    void initCentralWidget();

private:
    QToolBar *_fileToolBar;
    QAction *_saveAction, *_openAction;

    QToolBar *_clipboardToolBar;
    QAction *_cutAction, *_copyAction, *_pasteAction;

    QToolBar *_editToolBar;
    QAction *_delAction, *_undoAction, *_redoAction, *_findAction;

    QToolBar *_drawAddToolBar;
    QAction *_addRectAction, *_addLineAction, *_addOvalAction;
    QAction *_addTextAction, *_addCurveAction, *_addPolygonAction;

    QToolBar *_drawArrangeToolBar;
    QAction *_bringForwardAction, *_sendBackwardAction;
    QAction *_groupAction, *_ungroupAction;
    QAction *_rotateAction;

    ///TODO:
    /// QToolBar *fontToolBar;
    /// QToolBar *_shapeToolBar;
private:
    void initActions();
    void initToolBars();

private slots:
    // file actions
    void _save();
    void _open();
    // edit actions
    void _del();
    void _undo();
    void _redo();
    void _find();
    // draw: add actions
    void _addRect();
    void _addLine();
    void _addOval();
    void _addText();
    void _addCurve();
    void _addPolygon();
    // draw: arrange actions
    void _bringForward();
    void _sendBackward();
    void _group();
    void _ungroup();
    void _rotate();
    // clipboard actions
    void _cut();
    void _copy();
    void _paste();
};

#endif // XMAINWINDOW_H
