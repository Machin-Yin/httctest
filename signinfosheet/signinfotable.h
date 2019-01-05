#ifndef SIGNINFOTABLE_H
#define SIGNINFOTABLE_H

#include "addcompanydialog.h"
#include "selectpkgdialog.h"
#include "addpackagedialog.h"
#include "serializer.h"

#include <QDialog>
#include <QMap>
#include <QStringList>

namespace Ui {
class SignInfoTable;
}

class SignInfoTable : public QDialog
{
    Q_OBJECT

public:
    explicit SignInfoTable(QStringList pkgNames,QByteArray *jsonData, QWidget *parent = 0);
    ~SignInfoTable();
private:
    void createConnection();
    void clearPackageInfo();
    void setPackageInfo(QMap <QString, QString> pkgInfoMap);

private slots:
    void companyComAddItem();
    void packageComAddItem();
    void on_addCompanyButton_clicked();
    void on_changeCompanyButton_clicked();
    void on_selectPkgButton_clicked();
    void on_reSelectPkgButton_clicked();
    void showCompanyInfo(QString compName);

    void on_addPkgButton_clicked();
    void on_changePkgButton_clicked();
    void updatePackageInfo();
    void showPackageInfo(QString packageName);

    void on_saveButton_clicked();

private:
    Ui::SignInfoTable *ui;
    QStringList packageNames;
    QStringList packageNoChoose;
    QMap <QString, QString> provinceMap;
    QMap <QString, QMap<QString, QString> > companyMap;  //<company, QMap<info,value>
    QMap <QString, QStringList> compPkgMap;     //company contain's package
    QMap <QString, QMap<QString, QString> > packageMap;  //package info
    QByteArray *json;
};

#endif // SIGNINFOTABLE_H
