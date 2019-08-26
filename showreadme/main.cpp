#include "readmeshowdialog.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("filepath.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QTextStream in(&file);
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        process_line(line);
//    }
    QString filePath = in.readAll();

    QString title = QString::fromUtf8("放权文件列表");
    ReadmeShowDialog w(filePath, title, 0);
    w.show();

    return a.exec();
}
