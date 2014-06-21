#ifndef XDRAGDROPWINDOW_H
#define XDRAGDROPWINDOW_H

#include <QMainWindow>

struct XDragDropWindowImpl;

class XDragDropWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit XDragDropWindow(QWidget *parent = 0);
    ~XDragDropWindow();

private:
    XDragDropWindowImpl *_impl;
};

#endif // XDRAGDROPWINDOW_H
