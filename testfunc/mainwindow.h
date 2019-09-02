#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    void test1();
    void test2();
    void test3();
    int test4();
    void test5();
    void test6();  //生成不重复的随机数
    void test7();  //生成0-n的随机数
    void test8();  //a-z A-Z 的随机数
    void test9();  //write file
    void test10(); //QStringList left
    void test11(); //QStringList clear
    void test12(); // qstring to unsigned char*
    void test13(); // messagebox close n secons
    void test14(); // qstring cut
    void test15(); //
    void test16(); //
    void test17(); // char **arr    delete
    void test18(); // char **arr    delete

    bool lineEditLimitInput(const QString inStr, QString *retStr, int limit);
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    void paintEvent(QPaintEvent *event);
    bool getInvertColor(int x, int y, QColor &color);
    void showEvent( QShowEvent * event);

private slots:
//    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QImage m_image;
};

#endif // MAINWINDOW_H
