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
class QDataStream;
class QShortcut;
class QFile;
QT_END_NAMESPACE

class XMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

private slots:
    void graphicsItemInserted(QGraphicsItem *item);
    void XSceneSelectionChanged();

    // Graphics scene and view
private:
    XScene *_scene;
    XGraphicsView *_view;
    enum {
        INIT_XVIEW_WIDTH = 600, INIT_XVIEW_HEIGHT = 400,
        INIT_XSCENE_WIDTH = 5000, INIT_XSCENE_HEIGHT = 5000
    };
private:
    void initXScene();
    void initXView();
    void initCentralWidget();

    // Toolbars and actions
private:
    enum { // DO NOT modify any of the following values!
        FILE, EDIT, CLIPBOARD, INSERT, ARRANGE,
        NUM_TOOLBARS // NUM_TOOLBARS must be the last element! It indicates how many toolbars there are.
    };
    QToolBar **_toolBar;

    enum { // DO NOT modify any of the following values!
        SAVE, SAVEAS, OPEN,
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

    // Status bar
private:
    ZoomWidget *_zoomWidget;
private:
    void initStatusBar();

private slots:
    // file actions
    bool save();
    bool saveAs();
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
    // zoom
    void setZoomScale(int newScalePercentage);
private:
    bool openXMDFile(QFile *file, QDataStream &in);
    bool okToClearData();
    void clear();

    // Cut, copy and paste
private:
    enum { PASTE_OFFSET_ORIG = 0, PASTE_OFFSET_INC = 15 };
    int _pasteOffset;
private:
    void setPasteOffset(const int origOffset = PASTE_OFFSET_ORIG) { _pasteOffset = origOffset; }
    int pasteOffset() const { return _pasteOffset; }
    int incPasteOffset(int offsetInc = PASTE_OFFSET_INC) { return _pasteOffset += offsetInc; }
    void selectItems(const QList<QGraphicsItem*> &items);
    void readItems(QDataStream &in, const int offset = 0, const bool select = false);
    void writeItems(QDataStream &out, const QList<QGraphicsItem*> &items);
    void copyItems(const QList<QGraphicsItem*> &items);
private:
    enum {
        XTYPE_MIME,
        NUM_MIME_TYPES  // THIS MUST BE THE LAST ENUM!
    };
private:
    static const QString &mimeType(int typeId = XTYPE_MIME);
private slots:
    void activatePasteAction();

    // Shortcuts
private:
    enum {
        CTRL_A,
        NUM_SHORTCUTS // THIS MUST BE THE LAST ENUM!
    };
    QShortcut **_shortcut;
private:
    void initShortcut();
private slots:
    void selectAllItems();
};

#endif // XMAINWINDOW_H
