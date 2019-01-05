#ifndef ADDPACKAGEDIALOG_H
#define ADDPACKAGEDIALOG_H

#include <QDialog>
#include "/home/httc/work/fdsrc/softwareInstaller_mergeFD/GUI/include/gui/zyj_info.h"

namespace Ui {
class AddPackageDialog;
}

enum PkgInfoOperType{
    ADDPKGINFO,
    CHANGEPKGINFO,
    SHOWPKGINFO
};

class AddPackageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPackageDialog(QMap<QString, QStringList> *compPkgMap, QMap <QString, QMap<QString, QString> > *pkgMap, QString pkgName, QString compName, QStringList *pkgNoSelect,PkgInfoOperType type, QWidget *parent = 0);
    ~AddPackageDialog();

private:
    void getSysInfo();
    void setTochangePkgInfo();
    void showPkgInfo();

private slots:
    void on_buttonBox_accepted();

signals:
    void packageInfoChanged();

private:
    Ui::AddPackageDialog *ui;
    QMap<QString, QStringList> *companyPkgMap;
    QMap<QString, QMap<QString, QString> > *packageMap; //  <package name, info>
    QString packageName;
    QString companyName;
    QStringList *packageNoSelect;
    PkgInfoOperType operType;
};

#endif // ADDPACKAGEDIALOG_H
