#include "zoomwidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ZoomWidget)
{
    _ui->setupUi(this);

    _ui->zoomSpinBox->setMinimum(MIN_SPINBOX_VALUE);
    _ui->zoomSpinBox->setMaximum(MAX_SPINBOX_VALUE);
    _ui->zoomSpinBox->setValue(INIT_SPINBOX_VALUE);
    connect(_ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(scaleChanged(int)));
    connect(_ui->zoomSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSliderValue(int)));

    _ui->zoomHorizontalSlider->setMinimum(MIN_SLIDER_VALUE);
    _ui->zoomHorizontalSlider->setMaximum(MAX_SLIDER_VALUE);
    _ui->zoomHorizontalSlider->setValue(MID_SLIDER_VALUE);
    _ui->zoomHorizontalSlider->setPageStep(SLIDER_PAGE_STEP);
    connect(_ui->zoomHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxValue(int)));

    connect(_ui->zoomInButton, SIGNAL(clicked()), this, SLOT(sliderPageUp()));
    connect(_ui->zoomOutButton, SIGNAL(clicked()), this, SLOT(sliderPageDown()));
}

ZoomWidget::~ZoomWidget()
{
    delete _ui;
}

void ZoomWidget::resetZoomScale()
{
    setSpinBoxValue(INIT_SPINBOX_VALUE);
}

inline int nearByInt(const qreal value)
{
    return value > 0 ? static_cast<int>(value + 0.5) : static_cast<int>(value - 0.5);
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
    double spinBoxValue = a * value + b;
    return nearByInt(spinBoxValue);
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
    double sliderValue = a * value + b;
    return nearByInt(sliderValue);
}

void ZoomWidget::setSliderValue(int spinBoxValue)
{
    Q_ASSERT(_ui->zoomHorizontalSlider);
    _ui->zoomHorizontalSlider->setValue(spinBoxValueToSliderValue(spinBoxValue));
}

void ZoomWidget::setSpinBoxValue(int sliderValue)
{
    Q_ASSERT(_ui->zoomSpinBox);
    _ui->zoomSpinBox->setValue(sliderValueToSpinBoxValue(sliderValue));
}

void ZoomWidget::sliderPageUp()
{
    Q_ASSERT(_ui->zoomHorizontalSlider);
    _ui->zoomHorizontalSlider->setValue(_ui->zoomHorizontalSlider->value() + SLIDER_PAGE_STEP);
}

void ZoomWidget::sliderPageDown()
{
    Q_ASSERT(_ui->zoomHorizontalSlider);
    _ui->zoomHorizontalSlider->setValue(_ui->zoomHorizontalSlider->value() - SLIDER_PAGE_STEP);
}
