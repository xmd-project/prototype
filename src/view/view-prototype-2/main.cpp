#include "xmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(view_prototype);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/images/app.png"));

    XMainWindow w;
    w.show();

    return a.exec();
}
