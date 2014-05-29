#ifndef XZOOMWIDGET_H
#define XZOOMWIDGET_H

#include <QWidget>

namespace Ui {
class XZoomWidget;
}

class XZoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XZoomWidget(QWidget *parent = 0);
    ~XZoomWidget();

private:
    Ui::XZoomWidget *_ui;
};

#endif // XZOOMWIDGET_H
