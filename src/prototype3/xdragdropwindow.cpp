#include "xdragdropwindow.h"
#include "ui_xdragdropwindow.h"

XDragDropWindow::XDragDropWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::XDragDropWindow)
{
    _ui->setupUi(this);
}

XDragDropWindow::~XDragDropWindow()
{
    delete _ui;
}
