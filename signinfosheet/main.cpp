//#include "signinfotable.h"
#include "signinfotabledialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList testPkgList;
    testPkgList.append("tree_1.6.0-1_i386.deb");
    testPkgList.append("mythes-en-us_1%3a3.3.0-2ubuntu3_all.deb");
    testPkgList.append("mythes-en-au_2.1-5.3ubuntu1_all.deb");
    testPkgList.append("mesa-common-dev_9.1.1-0ubuntu3_i386.deb");

//    QByteArray *jsondata;
//    SignInfoTable w(testPkgList, jsondata, 0);

    SignInfoTableDialog w(testPkgList, 0);

    w.show();

//    qDebug() << *jsondata;


    return a.exec();
}
