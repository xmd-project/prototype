#include "zoomwidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomWidget)
{
    ui->setupUi(this);
}

ZoomWidget::~ZoomWidget()
{
    delete ui;
}
