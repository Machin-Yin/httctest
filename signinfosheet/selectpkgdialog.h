#ifndef SELECTPKGDIALOG_H
#define SELECTPKGDIALOG_H

#include "addpackagedialog.h"
#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class SelectPkgDialog;
}

enum PkgOperType{
    ADDPKG,
    CHANGEPKG
};

class SelectPkgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPkgDialog(QMap <QString, QStringList> *comPkgMap,
                             QMap <QString, QMap<QString, QString> > *packageMap,
                             QString compName,
                             QStringList *pkgNoChoose,
                             QWidget *parent = 0);
    ~SelectPkgDialog();

private:
    void init();
    void loadAllSelectItems();

private slots:
    void on_buttonBox_accepted();
    void changed(QTableWidgetItem *item);
    void updatePackageInfo();
signals:
    void packageChanged();
private:
    Ui::SelectPkgDialog *ui;
    QMap<QString, QStringList> *companyPkgMap; //<company, pkgs>
    QMap <QString, QMap<QString, QString> > *pkgMap;  //package info
    QString companyName;
    QStringList *packageNoChoose;
};

#endif // SELECTPKGDIALOG_H
