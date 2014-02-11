#include "zoomwidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ZoomWidget)
{
    _ui->setupUi(this);

    _ui->zoomHorizontalSlider->setMinimum(MIN_SLIDER_VALUE);
    _ui->zoomHorizontalSlider->setMaximum(MAX_SLIDER_VALUE);
    _ui->zoomHorizontalSlider->setValue(MID_SLIDER_VALUE);

    _ui->zoomSpinBox->setMinimum(MIN_SPINBOX_VALUE);
    _ui->zoomSpinBox->setMaximum(MAX_SPINBOX_VALUE);
    _ui->zoomSpinBox->setValue(INIT_SPINBOX_VALUE);

    connect(_ui->zoomHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxValue(int)));
    connect(_ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValue(int)));
}

ZoomWidget::~ZoomWidget()
{
    delete _ui;
}

int ZoomWidget::spinBoxValueToSliderValue(int value)
{
    /// Linear mappings:
    /// 1) spinBox::(MIN_SPINBOX_VALUE ~ INIT_SPINBOX_VALUE) => slider::(MIN_SLIDER_VALUE ~ MID_SLIDER_VALUE)
    /// 2) spinBox::(INIT_SPINBOX_VALUE ~ MAX_SPINBOX_VALUE) => slider::(MID_SLIDER_VALUE ~ MAX_SLIDER_VALUE)
    Q_ASSERT(MIN_SPINBOX_VALUE <= value && value <= MAX_SPINBOX_VALUE);
    double a, b;
    if (value <= INIT_SPINBOX_VALUE) {
        a = double(MID_SLIDER_VALUE - MIN_SLIDER_VALUE) / double(INIT_SPINBOX_VALUE - MIN_SPINBOX_VALUE);
        b = MIN_SLIDER_VALUE - a * MIN_SPINBOX_VALUE;
    } else {
        a = double(MAX_SLIDER_VALUE - MID_SLIDER_VALUE) / double(MAX_SPINBOX_VALUE - INIT_SPINBOX_VALUE);
        b = MAX_SLIDER_VALUE - a * MAX_SPINBOX_VALUE;
    }
    return int(a * value + b + 0.5);
}

int ZoomWidget::sliderValueToSpinBoxValue(int value)
{
    /// Linear mappings:
    /// 1) slider::(MIN_SLIDER_VALUE ~ MID_SLIDER_VALUE) => spinBox::(MIN_SPINBOX_VALUE ~ INIT_SPINBOX_VALUE)
    /// 2) slider::(MID_SLIDER_VALUE ~ MAX_SLIDER_VALUE) => spinBox::(INIT_SPINBOX_VALUE ~ MAX_SPINBOX_VALUE)
    Q_ASSERT(MIN_SLIDER_VALUE <= value && value <= MAX_SLIDER_VALUE);
    double a, b;
    if (value <= MID_SLIDER_VALUE) {
        a = double(INIT_SPINBOX_VALUE - MIN_SPINBOX_VALUE) / double(MID_SLIDER_VALUE - MIN_SLIDER_VALUE);
        b = MIN_SPINBOX_VALUE - a * MIN_SLIDER_VALUE;
    } else {
        a = double(MAX_SPINBOX_VALUE - INIT_SPINBOX_VALUE) / double(MAX_SLIDER_VALUE - MID_SLIDER_VALUE);
        b = MAX_SPINBOX_VALUE - a * MAX_SLIDER_VALUE;
    }
    return int(a * value + b + 0.5);
}

void ZoomWidget::setSliderValue(int value)
{
    Q_ASSERT(_ui->zoomHorizontalSlider);
    disconnect(_ui->zoomHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxValue(int)));
    _ui->zoomHorizontalSlider->setValue(spinBoxValueToSliderValue(value));
    connect(_ui->zoomHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxValue(int)));
}

void ZoomWidget::setSpinBoxValue(int value)
{
    Q_ASSERT(_ui->zoomSpinBox);
    disconnect(_ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValue(int)));
    _ui->zoomSpinBox->setValue(sliderValueToSpinBoxValue(value));
    connect(_ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValue(int)));
}
