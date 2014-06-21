#include "xdragdropwindow.h"
#include "ui_xdragdropwindow.h"

struct XDragDropWindowImpl
{
    XDragDropWindowImpl();
    ~XDragDropWindowImpl();

    Ui::XDragDropWindow *_ui;
};

XDragDropWindowImpl::XDragDropWindowImpl() :
    _ui(new Ui::XDragDropWindow)
{
}

XDragDropWindowImpl::~XDragDropWindowImpl()
{
    delete _ui;
}

XDragDropWindow::XDragDropWindow(QWidget *parent) :
    QMainWindow(parent),
    _impl(new XDragDropWindowImpl)
{
    _impl->_ui->setupUi(this);
}

XDragDropWindow::~XDragDropWindow()
{
    delete _impl;
}
