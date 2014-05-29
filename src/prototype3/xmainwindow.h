#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class XMainWindow;
}

class XMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

private:
    Ui::XMainWindow *ui;
};

#endif // XMAINWINDOW_H
