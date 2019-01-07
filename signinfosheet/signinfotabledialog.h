#ifndef SIGNINFOTABLEDIALOG_H
#define SIGNINFOTABLEDIALOG_H

#include <QDialog>
#include <QSplitter>
#include "addcompanydialog.h"
#include "addpackagedialog.h"
#include "selectpkgdialog.h"
#include "companydetaildialog.h"

namespace Ui {
class SignInfoTableDialog;
}

class SignInfoTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignInfoTableDialog(QStringList pkgList, QWidget *parent = 0);
    ~SignInfoTableDialog();

private slots:
    void factoryTableAddItem();
    void packageTableAddItem();
    void on_addFactoryButton_clicked();
    void on_modifyFactoryButton_clicked();
    void on_viewFactoryButton_clicked();
    void on_deleteFactoryButton_clicked();
    void on_addPackageButton_clicked();
    void on_modifyPackageButton_clicked();
    void on_viewPackageButton_clicked();
    void on_deletePackageButton_clicked();
    void on_cancelButton_clicked();
    void on_sureButton_clicked();

private:
    void initTableHeader();

private:
    Ui::SignInfoTableDialog *ui;
    QStringList packageNames;
    QStringList packageNoChoose;
    QMap <QString, QMap<QString, QString> > companyMap;  //<company, QMap<info,value>
    QMap <QString, QStringList> compPkgMap;     //company contain's package
    QMap <QString, QMap<QString, QString> > packageMap;  //package info
    QByteArray *json;
};

#endif // SIGNINFOTABLEDIALOG_H
