#include "nodewidget.h"
#include "ui_nodewidget.h"

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::NodeWidget)
{
    ui->setupUi(this);
}

NodeWidget::~NodeWidget()
{
    delete ui;
}
