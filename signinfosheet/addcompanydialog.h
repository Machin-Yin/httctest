#ifndef ADDCOMPANYDIALOG_H
#define ADDCOMPANYDIALOG_H

#include <QDialog>
#include <QMap>
#include "parser.h"
#include "serializer.h"

namespace Ui {
class AddCompanyDialog;
}

enum CompOperType{
    ADDCOMP,
    CHANGECOMP
};

class AddCompanyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompanyDialog(QMap <QString, QMap<QString, QString> > *companyMap,
                              CompOperType type,
                              QString currentComp,
                              QWidget *parent = 0);
    ~AddCompanyDialog();
private:
    void createCities();
    void parseProvince();
    void getCurrentTime();
    void setTochangeCompInfo();

private slots:
    void parseCity(QString proName);
    void on_cancelButton_clicked();
    void on_sureButton_clicked();

signals:
    void companyChanged();

private:
    Ui::AddCompanyDialog *ui;
    CompOperType operType;
    QString changeComp;
    QStringList provinceList;
    QMap <QString, QStringList> proCityMap;
    QStringList  cityList;
//    QMap <QString, QString> provinceMap;
    QMap<QString, QMap<QString, QString> > *allCompanyMap;

};

#endif // ADDCOMPANYDIALOG_H
