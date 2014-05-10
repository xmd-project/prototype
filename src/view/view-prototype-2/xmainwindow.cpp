#include "xmainwindow.h"
#include "xscene.h"
#include "xgraphicsview.h"
#include "xrect.h"
#include "zoomwidget.h"
#include "xgroup.h"
#include "xmd.h"
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QStatusBar>
#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QShortcut>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

XMainWindow::XMainWindow(QWidget *parent) :
    QMainWindow(parent),
    _pasteOffset(PASTE_OFFSET_ORIG)
{
    initXScene();
    initCentralWidget();
    initToolBars();
    initStatusBar();
    initShortcut();
}
XMainWindow::~XMainWindow()
{
    delete[] _action;
    delete[] _toolBar;
    delete[] _shortcut;
}

void XMainWindow::graphicsItemInserted(QGraphicsItem *item)
{
    _scene->setMode();
    _view->setDragMode(QGraphicsView::RubberBandDrag); // recover selection view mode
    switch (item->type()) {
    case XRect::Type: _action[INS_RECT]->setChecked(false); break;
    default:;
    }
}

void XMainWindow::XSceneSelectionChanged()
{
    Q_ASSERT(_scene);
    if (_scene->selectedItems().empty()) { // deactivate actions
        // delete action
        _action[DEL]->setEnabled(false);
        // cut and copy actions
        _action[CUT]->setEnabled(false);
        _action[COPY]->setEnabled(false);
        // bring forward and send backward
        _action[BRING_FORWARD]->setEnabled(false);
        _action[SEND_BACKWARD]->setEnabled(false);
        // group and ungroup
        _action[GROUP]->setEnabled(false);
        _action[UNGROUP]->setEnabled(false);
    } else { // activate delete action
        // delete action
        _action[DEL]->setEnabled(true);
        // cut and copy actions
        _action[CUT]->setEnabled(true);
        _action[COPY]->setEnabled(true);
        // bring forward and send backward
        _action[BRING_FORWARD]->setEnabled(true);
        _action[SEND_BACKWARD]->setEnabled(true);
        // group and ungroup
        if (_scene->selectedItems().size() > 1) // never group single item
            _action[GROUP]->setEnabled(true);
        foreach (QGraphicsItem *item, _scene->selectedItems()) {
            if (qgraphicsitem_cast<XGroup *>(item)) {
                _action[UNGROUP]->setEnabled(true);
                break;
            }
        }
    }
}

void XMainWindow::initXScene()
{
    _scene = new XScene;
    // setting scene rectangle is necessary for creating and locating a graphics item
    _scene->setSceneRect(QRectF(0, 0, INIT_XSCENE_WIDTH, INIT_XSCENE_HEIGHT));
    connect(_scene, SIGNAL(graphicsItemInserted(QGraphicsItem*)),
            this, SLOT(graphicsItemInserted(QGraphicsItem*)));
    connect(_scene, SIGNAL(selectionChanged()), this, SLOT(XSceneSelectionChanged()));
}

void XMainWindow::initXView()
{
    _view = new XGraphicsView;
    _view->setScene(_scene);
    _view->setCacheMode(QGraphicsView::CacheBackground);
    _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    _view->setMinimumSize(INIT_XVIEW_WIDTH, INIT_XVIEW_HEIGHT);
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
    _toolBar = new QToolBar*[NUM_TOOLBARS];
    _action = new QAction*[NUM_ACTIONS];

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
    _action[SAVE] = _toolBar[FILE]->addAction(QIcon(":/icon/images/save.png"), tr("&Save"), this, SLOT(save()));
    _action[SAVE]->setShortcut(tr("Ctrl+S"));
    _action[SAVE]->setToolTip(tr("Save (Ctrl+S)"));
    _action[SAVEAS] = _toolBar[FILE]->addAction(QIcon(":/icon/images/saveas.png"), tr("Save &As"), this, SLOT(saveAs()));
    _action[SAVEAS]->setShortcut(QKeySequence::SaveAs);
    _action[SAVEAS]->setToolTip(tr("Save As"));
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
    // activate paste action if and only if the clipboard has acceptable data
    _action[PASTE]->setEnabled(false);
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(activatePasteAction()));
}

void XMainWindow::activatePasteAction()
{
    const QMimeData *mimeData = QApplication::clipboard()->mimeData();
    if (mimeData && mimeData->hasFormat(mimeType()))
        _action[PASTE]->setEnabled(true);
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

void XMainWindow::initStatusBar()
{
    _zoomWidget = new ZoomWidget;
    connect(_zoomWidget, SIGNAL(scaleChanged(int)), this, SLOT(setZoomScale(int)));
    statusBar()->addPermanentWidget(_zoomWidget);
}

bool XMainWindow::save()
{
    const QString filename = windowFilePath();
    if (filename.isEmpty() || filename == tr("Unnamed"))
        return saveAs();
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream outStream(&file);
    outStream << Xmd::FILE_FORMAT_IDENTIFIER << Xmd::VERSION_NUMBER;
    outStream.setVersion(QDataStream::Qt_5_1);
    writeItems(outStream, _scene->items());
    file.close();
    return true;
}

bool XMainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("%1 - Save As").arg(QApplication::applicationName()),
                                                    ".", tr("XMD (*.xmd)"));
    if (filename.isEmpty())
        return false;
    if (!filename.toLower().endsWith(".xmd"))
        filename += ".xmd";
    setWindowFilePath(filename);
    return save();
}

template<typename T>
bool isOkToClearData(bool (T::*saveData)(), T *parent,
                   const QString &title, const QString &text,
                   const QString &detailedText=QString())
{
    Q_ASSERT(saveData && parent);
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2")
                               .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->addButton(QMessageBox::Save);
    messageBox->addButton(QMessageBox::Discard);
    messageBox->addButton(QMessageBox::Cancel);
    messageBox->setDefaultButton(QMessageBox::Save);
    messageBox->exec();
    if (messageBox->clickedButton() ==
            messageBox->button(QMessageBox::Cancel))
        return false;
    if (messageBox->clickedButton() ==
            messageBox->button(QMessageBox::Save))
        return (parent->*saveData)();
    return true;
}

bool XMainWindow::okToClearData()
{
    if (isWindowModified())
        return isOkToClearData(&XMainWindow::save, this,
                               tr("Unsaved changes"), tr("Save unsaved changes?"));
    return true;
}

void XMainWindow::clear()
{
    _scene->clear();
    _zoomWidget->resetZoomScale();
}

void XMainWindow::open()
{
    if (!okToClearData())
        return;
    const QString &filename =
            QFileDialog::getOpenFileName(
                this,
                tr("%1 - Open").arg(QApplication::applicationName()),
                ".", tr("XMD (*.xmd)"));
    if (filename.isEmpty())
        return;
    setWindowFilePath(filename);
    QFile file(windowFilePath());
    QDataStream in;
    if (!openXMDFile(&file, in))
        return;
    in.setVersion(QDataStream::Qt_5_1);
    clear();
    readItems(in);
}

namespace {
void warning(QWidget *parent, const QString &title,
             const QString &text, const QString &detailedText=QString())
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2")
                               .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Warning);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->exec();
}
}

bool XMainWindow::openXMDFile(QFile *file, QDataStream &in)
{
    if (!file->open(QIODevice::ReadOnly)) {
        warning(this, tr("Error"), tr("Failed to open file: %1")
                .arg(file->errorString()));
        return false;
    }
    in.setDevice(file);
    int fileFormatIdentifier;
    Q_ASSERT(sizeof(fileFormatIdentifier) == sizeof(Xmd::FILE_FORMAT_IDENTIFIER));
    in >> fileFormatIdentifier;
    if (fileFormatIdentifier != Xmd::FILE_FORMAT_IDENTIFIER) {
        warning(this, tr("Error"),
                tr("%1 is not a %2 file").arg(file->fileName())
                .arg(QApplication::applicationName()));
        return false;
    }
    int versionNumber;
    Q_ASSERT(sizeof(versionNumber) == sizeof(Xmd::VERSION_NUMBER));
    in >> versionNumber;
    if (versionNumber > Xmd::VERSION_NUMBER) {
        warning(this, tr("Error"),
                tr("%1 needs a more recent version of %2")
                .arg(file->fileName())
                .arg(QApplication::applicationName()));
        return false;
    }
    return true;
}

void XMainWindow::del()
{
    foreach (QGraphicsItem *item, _scene->selectedItems()) {
        _scene->removeItem(item);
        delete item;
    }
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
    _scene->bringForwardSelectedItems();
}

void XMainWindow::sendBackward()
{
    _scene->sendBackwardSelectedItems();
}

void XMainWindow::group()
{
    _scene->group();
}

void XMainWindow::ungroup()
{
    _scene->ungroup();
}

void XMainWindow::rotate()
{
}

/// Clear previous selection and select items in the QList
void XMainWindow::selectItems(const QList<QGraphicsItem*> &items)
{
    Q_ASSERT(_scene);
    _scene->clearSelection();
    foreach (QGraphicsItem *item, items)
        item->setSelected(true);
}

namespace {
/// Move XGraphicsItem to pos() + QPointF(dx, dy)
void moveBy(QGraphicsItem *&item, const qreal dx, const qreal dy, XScene *xscene)
{
    Q_ASSERT(item);
    if (XGroup::Type != item->type()) {
        item->moveBy(dx, dy);
        return;
    }
    // Moving an XGroup object doesn't impact its child items' postions.
    // Therefore, manually move its child items recursively and
    // build a new XGroup with the moved child items.
    XGroup *xgroup = qgraphicsitem_cast<XGroup *>(item);
    Q_ASSERT(xgroup && xscene);
    QList<QGraphicsItem *> children = xgroup->childItems();
    QPointF xgroupOffset = xgroup->pos();
    xscene->destroyItemGroup(xgroup);
    XGroup *newXgroup = new XGroup;
    xscene->addItem(newXgroup); // Add a empty new XGroup object
    xscene->adjustZValue(newXgroup);
    foreach (QGraphicsItem *child, children) {
        moveBy(child, dx + xgroupOffset.x(), dy + xgroupOffset.y(), xscene);
        newXgroup->addToGroup(child); // should also add child to xscene
        Q_ASSERT(child->scene() == xscene);
    }
    item = newXgroup; // update item with a new XGroup object
}
} // namespace

void XMainWindow::readItems(QDataStream &in, const int offset, const bool select)
{
    QList<QGraphicsItem *> items;
    while (!in.atEnd())
        items << Xmd::readXGraphicsItem(in); // ZValue is loaded here
    //XScene::sortByZValue(items); // keep hierarchical relationship of items
    for (QList<QGraphicsItem *>::iterator childIter = items.begin();
         childIter != items.end(); ++childIter) {
        QGraphicsItem *&item = *childIter;
        Q_ASSERT(item);
        qDebug() << "readItems() item->pos() before addItem() - " << item->pos();
        _scene->addItem(item);
        qDebug() << "readItems() item->pos() after addItem() - " << item->pos();
        // don't adjust the ZValue when first pasting a cut item
        // or creating a new item by opening a file
        if (!offset)
            _scene->adjustZValue(item);
        moveBy(item, offset, offset, _scene); // XGroup item will be changed inside moveBy().
        QGraphicsItem *parent = item->parentItem();
        qDebug() << "readItems() parent type = " << (parent ? parent->type() : 0);
    }
    if (select)
        selectItems(items);
}

const QString &XMainWindow::mimeType(int typeId)
{
    Q_ASSERT(0 <= typeId && typeId < NUM_MIME_TYPES);
    /// Customized MIME type associated with QByteArray data
    static const QString mimeTypeStr[NUM_MIME_TYPES] = {
        "XType_MimeDataType", // XTYPE_MIME
    };
    return mimeTypeStr[typeId];
}

void XMainWindow::writeItems(QDataStream &out, const QList<QGraphicsItem*> &items)
{
    foreach (QGraphicsItem *item, items) {
        QGraphicsItem *parent = item->parentItem();
        qDebug() << "readItems() parent type = " << (parent? parent->type() : 0);
        if (!parent) // Only write top items here
            Xmd::writeXGraphicsItem(out, item); // child items will be written recursively
    }
}

void XMainWindow::copyItems(const QList<QGraphicsItem*> &items)
{
    QByteArray copiedItems;
    QDataStream outStream(&copiedItems, QIODevice::WriteOnly);
    writeItems(outStream, items);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(mimeType(), copiedItems);
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void XMainWindow::cut()
{
    QList<QGraphicsItem*> items = _scene->selectedItems();
    Q_ASSERT(!items.isEmpty());
    setPasteOffset(); // the first copy will be pasted in the same position
    copyItems(items);
    QListIterator<QGraphicsItem*> i(items);
    while (i.hasNext()) {
#if QT_VERSION >= 0x040600
        QScopedPointer<QGraphicsItem> item(i.next());
        _scene->removeItem(item.data());
#else
        QGraphicsItem *item = i.next();
        _scene->removeItem(item);
        delete item;
#endif
    }
}

void XMainWindow::copy()
{
    QList<QGraphicsItem*> items = _scene->selectedItems();
    Q_ASSERT(!items.isEmpty());
    setPasteOffset();
    incPasteOffset(); // the first copy will be pasted with a position offset
    copyItems(items);
}

void XMainWindow::paste()
{
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if (!mimeData)
        return; // paste nothing
    if (mimeData->hasFormat(mimeType())) {
        QByteArray copiedItems = mimeData->data(mimeType());
        QDataStream inStream(&copiedItems, QIODevice::ReadOnly);
        readItems(inStream, pasteOffset(), true); // paste and select only new items
        incPasteOffset(); // next copy will be pasted with a position offset
    }
}

void XMainWindow::setZoomScale(int newScalePercentage)
{
    qreal newScale = static_cast<qreal> (newScalePercentage) / 100.0;
    QMatrix oldMatrix = _view->matrix();
    _view->resetMatrix();
    _view->translate(oldMatrix.dx(), oldMatrix.dy());
    _view->scale(newScale, newScale);
}

void XMainWindow::initShortcut()
{
    _shortcut = new QShortcut *[NUM_SHORTCUTS];

    _shortcut[CTRL_A] = new QShortcut(QKeySequence::SelectAll, this);
    connect(_shortcut[CTRL_A], SIGNAL(activated()), this, SLOT(selectAllItems()));
}

void XMainWindow::selectAllItems()
{
    Q_ASSERT(_scene);
    foreach (QGraphicsItem *item, _scene->items())
        item->setSelected(true);
}
