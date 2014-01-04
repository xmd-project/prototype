#include "nodewidget.h"
#include "ui_nodewidgetexample.h"

NodeWidget::NodeWidget(QWidget *parent) :
    QWidget(parent), _ui(new Ui::NodeWidget)
{
    _ui->setupUi(this);
}

NodeWidget::~NodeWidget()
{
    delete _ui;
}
