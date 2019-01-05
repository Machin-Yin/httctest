#include "companydetaildialog.h"
#include "ui_companydetaildialog.h"

CompanyDetailDialog::CompanyDetailDialog(QMap<QString, QMap<QString, QString> > factoryMap, QString factoryName, QWidget *parent) :
    QDialog(parent),
    factMap(factoryMap),
    factName(factoryName),
    ui(new Ui::CompanyDetailDialog)
{
    ui->setupUi(this);
    showComanyDetail();
}

CompanyDetailDialog::~CompanyDetailDialog()
{
    delete ui;
}

void CompanyDetailDialog::showComanyDetail()
{
    QMap <QString, QMap <QString, QString> >::const_iterator iter = factMap.find(factName);
    QMap <QString, QString>  currentCompanyMap = iter.value();
    ui->contactLabel->setText(currentCompanyMap.value("contactname"));
    ui->mobileLabel->setText(currentCompanyMap.value("mobilephone"));
    ui->phoneLabel->setText(currentCompanyMap.value("telephone"));
    ui->dateLabel->setText(currentCompanyMap.value("date"));
    ui->factoryLabel->setText(currentCompanyMap.value("companyname"));
    ui->proLabel->setText(currentCompanyMap.value("province"));
    ui->cityLabel->setText(currentCompanyMap.value("city"));
}
