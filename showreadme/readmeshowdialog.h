#ifndef READMESHOWDIALOG_H
#define READMESHOWDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class ReadmeShowDialog : public QDialog
{
    Q_OBJECT

public:
    ReadmeShowDialog(QString readmeStr, QString titleStr, QWidget *parent = 0);
    ~ReadmeShowDialog();
private:
    void initUi();
    void initWidget();
    void addItem();

private slots:
    void on_sureButton_clicked();

private:
    QString pathStr;
    QTableWidget *tableWidget;
    QPushButton *sureButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *botomLayout;
};

#endif // READMESHOWDIALOG_H
