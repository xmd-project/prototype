#include "xmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMainWindow w;
    w.show();

    return a.exec();
}
