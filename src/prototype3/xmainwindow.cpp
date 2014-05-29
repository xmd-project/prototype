#include "xmainwindow.h"
#include "ui_xmainwindow.h"

XMainWindow::XMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XMainWindow)
{
    ui->setupUi(this);
}

XMainWindow::~XMainWindow()
{
    delete ui;
}
