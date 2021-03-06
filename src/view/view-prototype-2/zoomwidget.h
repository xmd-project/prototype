#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QWidget>

namespace Ui {
class ZoomWidget;
}

class ZoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomWidget(QWidget *parent = 0);
    ~ZoomWidget();
    void resetZoomScale();

signals:
    void scaleChanged(int newScale);

private slots:
    void setSliderValue(int spinBoxValue);
    void setSpinBoxValue(int sliderValue);
    void sliderPageUp();
    void sliderPageDown();

private:
    Ui::ZoomWidget *_ui;

private:
    enum {
        MIN_SLIDER_VALUE = 0, MAX_SLIDER_VALUE = 200, MID_SLIDER_VALUE = 100, SLIDER_PAGE_STEP=10,
        MIN_SPINBOX_VALUE = 10, MAX_SPINBOX_VALUE = 400, INIT_SPINBOX_VALUE = 100
    };
    static int spinBoxValueToSliderValue(int value);
    static int sliderValueToSpinBoxValue(int value);
};

#endif // ZOOMWIDGET_H
