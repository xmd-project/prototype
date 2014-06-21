#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <QMainWindow>

struct XMainWindowImpl;

class XMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

private:
    XMainWindowImpl *_impl;
};

#endif // XMAINWINDOW_H
