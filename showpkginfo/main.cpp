#include "showpkginfodialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowPkgInfoDialog w;
    w.show();

    return a.exec();
}
