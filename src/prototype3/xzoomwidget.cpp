#include "xzoomwidget.h"
#include "ui_xzoomwidget.h"

XZoomWidget::XZoomWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::XZoomWidget)
{
    _ui->setupUi(this);
}

XZoomWidget::~XZoomWidget()
{
    delete _ui;
}
