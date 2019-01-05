#ifndef COMPANYDETAILDIALOG_H
#define COMPANYDETAILDIALOG_H

#include <QMap>
#include <QDialog>

namespace Ui {
class CompanyDetailDialog;
}

class CompanyDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyDetailDialog(QMap <QString, QMap<QString, QString> > factoryMap, QString factoryName, QWidget *parent = 0);
    ~CompanyDetailDialog();
private:
    void showComanyDetail();

private:
    Ui::CompanyDetailDialog *ui;
    QMap <QString, QMap<QString, QString> > factMap;
    QString factName;
};

#endif // COMPANYDETAILDIALOG_H
