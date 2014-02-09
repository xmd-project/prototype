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

private:
    Ui::ZoomWidget *ui;
};

#endif // ZOOMWIDGET_H
