#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <QMainWindow>

class XScene;
class XGraphicsView;
class ZoomWidget;

QT_BEGIN_NAMESPACE
class QToolBar;
class QAction;
class QGraphicsItem;
QT_END_NAMESPACE

class XMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

private slots:
    void graphicsItemInserted(QGraphicsItem *item);

private:
    XScene *_scene;
    XGraphicsView *_view;
    enum {
        _INIT_XVIEW_WIDTH = 600, _INIT_XVIEW_HEIGHT = 400,
        _INIT_XSCENE_WIDTH = 5000, _INIT_XSCENE_HEIGHT = 5000
    };
private:
    void initXScene();
    void initXView();
    void initCentralWidget();

private:
    enum __ToolBar { // DO NOT modify any of the following values!
        FILE, EDIT, CLIPBOARD, INSERT, ARRANGE,
        NUM_TOOLBARS // NUM_TOOLBARS must be the last element! It indicates how many toolbars there are.
    };
    QToolBar **_toolBar;

    enum __Action { // DO NOT modify any of the following values!
        SAVE, OPEN,
        DEL, UNDO, REDO, FIND,
        INS_RECT, INS_LINE, INS_OVAL, INS_TEXT, INS_CURVE, INS_POLYGON,
        BRING_FORWARD, SEND_BACKWARD, GROUP, UNGROUP, ROTATE,
        CUT, COPY, PASTE,
        NUM_ACTIONS  // NUM_ACTIONS must be the last element! It indicates how many actions there are.
    };
    QAction **_action;
private:
    void initFileToolBar();
    void initEditToolBar();
    void initClipboardToolBar();
    void initInsertToolBar();
    void initArrangeToolBar();
    ///TODO:
    ///void initFontToolBar();
    ///void initShapeToolBar();

    void initToolBars();

private:
    ZoomWidget *_zoomWidget;
private:
    void initStatusBar();

private slots:
    // file actions
    void save();
    void open();
    // edit actions
    void del();
    void undo();
    void redo();
    void find();
    // draw: insert actions
    void insertRect();
    void insertLine();
    void insertOval();
    void insertText();
    void insertCurve();
    void insertPolygon();
    // draw: arrange actions
    void bringForward();
    void sendBackward();
    void group();
    void ungroup();
    void rotate();
    // clipboard actions
    void cut();
    void copy();
    void paste();
};

#endif // XMAINWINDOW_H
