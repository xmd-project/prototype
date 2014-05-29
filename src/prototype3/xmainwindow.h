#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class XMainWindow;
}

struct XMainWindowImpl;

class XMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

private:
    Ui::XMainWindow *_ui;
    XMainWindowImpl *_impl;
};

#endif // XMAINWINDOW_H
