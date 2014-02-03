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
    enum {
        _INIT_XVIEW_WIDTH = 600, _INIT_XVIEW_HEIGHT = 400,
        _INIT_XSCENE_WIDTH = 5000, _INIT_XSCENE_HEIGHT = 5000
    };
private:
    void initView();
    void initCentralWidget();

private:
    void initFileToolBar();
    void initEditToolBar();
    void initClipboardToolBar();
    void initAddToolBar();
    void initArrangeToolBar();
    ///TODO:
    ///void initFontToolBar();
    ///void initShapeToolBar();

    void initToolBars();

private slots:
    // file actions
    void save();
    void open();
    // edit actions
    void del();
    void undo();
    void redo();
    void find();
    // draw: add actions
    void addRect();
    void addLine();
    void addOval();
    void addText();
    void addCurve();
    void addPolygon();
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
