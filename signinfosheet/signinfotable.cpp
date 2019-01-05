#include "signinfotable.h"
#include "ui_signinfotable.h"
#include "/home/httc/work/fdsrc/softwareInstaller_mergeFD/GUI/include/gui/zyj_info.h"

#include <QFile>

SignInfoTable::SignInfoTable(QStringList pkgNames, QByteArray *jsonData, QWidget *parent) :
    QDialog(parent),
    packageNames(pkgNames),
    ui(new Ui::SignInfoTable)
{
    ui->setupUi(this);
    init();
    parseProvince();
    getZyjSysInfo();
    connect(ui->provinceComboBox, SIGNAL(activated(QString)), this, SLOT(parseCity(QString)));
}

SignInfoTable::~SignInfoTable()
{
    delete ui;
}

void SignInfoTable::init()
{
    ui->developmentPkgDevInfoTextEdit->setStyleSheet("background-color:transparent;");
    ui->runtimeDevInfoTextEdit->setStyleSheet("background-color:transparent;");
}

void SignInfoTable::parseProvince()
{
    QFile fileProvince(PROVINCE_JSON_FILE);
    if(!fileProvince.open( QIODevice::ReadOnly | QIODevice::Text )) {
         return ;
    }

    QByteArray jsonByteArray = fileProvince.readAll();
    fileProvince.close();

    QJson::Parser parser;
    bool ok;
    QVariantList provinceLists =
        parser.parse(jsonByteArray, &ok).toList();

    if (!ok)
    {
       qDebug("An error occured during parsing");
       return ;
    }

    ui->provinceComboBox->addItem("");
    foreach (QVariant each, provinceLists)
    {
       QVariantMap passedMap = each.toMap();
       provinceMap.insert(passedMap["name"].toString(), passedMap["code"].toString());
       ui->provinceComboBox->addItem(passedMap["name"].toString());
    }
}

void SignInfoTable::getZyjSysInfo()
{
    sysinfo_zyj sysinfo;
//    get_zyj_sysinfo(&sysinfo);
    if (strlen(sysinfo.osver) == 0)
    {
      ui->runtimeOsVersionLineEdit->setText(
            QString::fromUtf8("Unknown"));
    }
    else
    {
      ui->runtimeOsVersionLineEdit->setText(
                 sysinfo.osver);
    }

    if (strlen(sysinfo.kernelver) == 0)
    {
      ui->runtimeOsVersionLineEdit->setText(
            QString::fromUtf8("Unknown"));
    }
    else
    {
      ui->runtimeOsVersionLineEdit->setText(
                 sysinfo.kernelver);
    }

    if (strlen(sysinfo.socversion) == 0)
    {
      ui->runtimeOsVersionLineEdit->setText(
            QString::fromUtf8("Unknown"));
    }
    else
    {
      ui->runtimeOsVersionLineEdit->setText(
                 sysinfo.socversion);
    }

    if (strlen(sysinfo.biosversion) == 0)
    {
      ui->runtimeOsVersionLineEdit->setText(
            QString::fromUtf8("Unknown"));
    }
    else
    {
      ui->runtimeOsVersionLineEdit->setText(
                 sysinfo.biosversion);
    }

    if (strlen(sysinfo.ioversion) == 0)
    {
      ui->runtimeOsVersionLineEdit->setText(
            QString::fromUtf8("Unknown"));
    }
    else
    {
      ui->runtimeOsVersionLineEdit->setText(
                 sysinfo.ioversion);
    }
}

void SignInfoTable::parseCity(QString pkgName)
{
    QFile fileCity(CITY_JSON_FILE);
    if(!fileCity.open( QIODevice::ReadOnly | QIODevice::Text )) {
         return ;
    }

    QByteArray jsonByteArray = fileCity.readAll();
    fileCity.close();

    QJson::Parser parser;
    bool ok;
    QVariantList cityLists =
        parser.parse(jsonByteArray, &ok).toList();

    if (!ok)
    {
       qDebug("An error occured during parsing");
       return ;
    }

    QString code;
    QMap<QString, QString>::const_iterator itor = provinceMap.find(pkgName);
    while (itor != provinceMap.end() && itor.key() == pkgName)
    {
        code = itor.value();
        ++itor;
    }

    ui->cityComboBox->clear();
    ui->cityComboBox->addItem("");
    foreach (QVariant each, cityLists)
    {
       QVariantMap passedMap = each.toMap();
       if (passedMap["provinceCode"].toString() == code)
       {
           ui->cityComboBox->addItem(passedMap["name"].toString());
       }
    }
}
