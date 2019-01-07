#include "addpackagedialog.h"
#include "ui_addpackagedialog.h"
#include "/home/httc/work/fdsrc/softwareInstaller_mergeFD/GUI/include/gui/zyj_info.h"

AddPackageDialog::AddPackageDialog(QMap<QString, QStringList> *compPkgMap, QMap<QString, QMap<QString, QString> > *pkgMap, QString pkgName, QString compName, QStringList *pkgNoSelect, PkgInfoOperType type, QWidget *parent) :
    QDialog(parent),
    companyPkgMap(compPkgMap),
    packageMap(pkgMap),
    packageName(pkgName),
    companyName(compName),
    packageNoSelect(pkgNoSelect),
    operType(type),
    ui(new Ui::AddPackageDialog)
{
    ui->setupUi(this);
    ui->pkgNameLabel->setText(pkgName);
    if (operType == CHANGEPKGINFO || operType == SHOWPKGINFO)
    {
        setTochangePkgInfo();
    }
}

AddPackageDialog::~AddPackageDialog()
{
    delete ui;
}

void AddPackageDialog::getSysInfo()
{
    sysinfo_zyj sysinfo;
    //    get_zyj_sysinfo(&sysinfo);
    if (strlen(sysinfo.osver) == 0)
    {
        ui->runtimeOsVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeOsVersionLabel->setText(
                    sysinfo.osver);
    }

    if (strlen(sysinfo.kernelver) == 0)
    {
        ui->runtimeKernelVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeKernelVersionLabel->setText(
                    sysinfo.kernelver);
    }

    if (strlen(sysinfo.socversion) == 0)
    {
        ui->runtimeSocVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeSocVersionLabel->setText(
                    sysinfo.socversion);
    }

    if (strlen(sysinfo.biosversion) == 0)
    {
        ui->runtimeFirmwareVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeFirmwareVersionLabel->setText(
                    sysinfo.biosversion);
    }

    if (strlen(sysinfo.ioversion) == 0)
    {
        ui->runtimeIoModuleVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeIoModuleVersionLabel->setText(
                    sysinfo.ioversion);
    }
}

void AddPackageDialog::setTochangePkgInfo()
{
    QMap<QString, QMap<QString, QString> >::const_iterator itor = packageMap->find(packageName);
    QMap<QString, QString> packageInfoMap = itor.value();

    ui->productNameLineEdit->setText(packageInfoMap.value("productname"));
    ui->descLineEdit->setText(packageInfoMap.value("desc"));
    ui->pkgNameLabel->setText(packageInfoMap.value("name"));
    ui->pkgVersionLabel->setText(packageInfoMap.value("version"));
    ui->pkgArchLabel->setText(packageInfoMap.value("arch"));
    ui->pkgDependencyLabel->setText(packageInfoMap.value("dependency"));

    ui->developmentOsVersionLineEdit->setText(packageInfoMap.value("devosversion"));
    ui->developmentKernelVersionLineEdit->setText(packageInfoMap.value("devkernelversion"));
    ui->developmentSocVersionLineEdit->setText(packageInfoMap.value("devsocversion"));
    ui->developmentFirmwareVersionLineEdit->setText(packageInfoMap.value("devfirmwareversion"));
    ui->developmentIoModuleVersionLineEdit->setText(packageInfoMap.value("deviomoduleversion"));

    ui->runtimeOsVersionLabel->setText(packageInfoMap.value("runosversion"));
    ui->runtimeKernelVersionLabel->setText(packageInfoMap.value("runkernelversion"));
    ui->runtimeSocVersionLabel->setText(packageInfoMap.value("runsocversion"));
    ui->runtimeFirmwareVersionLabel->setText(packageInfoMap.value("runfirmwareversion"));
    ui->runtimeIoModuleVersionLabel->setText(packageInfoMap.value("runiomoduleversion"));

    ui->installReasonLineEdit->setText(packageInfoMap.value("installreason"));
    ui->installResultLineEdit->setText(packageInfoMap.value("installresult"));
    ui->installWarningLineEdit->setText(packageInfoMap.value("installwarning"));

    if (operType == SHOWPKGINFO)
    {
//        setFocusPolicy(Qt::NoFocus);
        ui->productNameLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->descLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentOsVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentKernelVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentSocVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentFirmwareVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentIoModuleVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installReasonLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installResultLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installWarningLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");

        ui->cancelButton->hide();
        ui->sureButton->hide();
    }
}

void AddPackageDialog::on_sureButton_clicked()
{
    QMap<QString, QString> addPackageMap;

    addPackageMap.insert("productname", ui->productNameLineEdit->text());
    addPackageMap.insert("desc", ui->descLineEdit->text());
    addPackageMap.insert("name", ui->pkgNameLabel->text());
    addPackageMap.insert("version", ui->pkgVersionLabel->text());
    addPackageMap.insert("arch", ui->pkgArchLabel->text());
    addPackageMap.insert("dependency", ui->pkgDependencyLabel->text());

    addPackageMap.insert("devosversion", ui->developmentOsVersionLineEdit->text());
    addPackageMap.insert("devkernelversion", ui->developmentKernelVersionLineEdit->text());
    addPackageMap.insert("devsocversion", ui->developmentSocVersionLineEdit->text());
    addPackageMap.insert("devfirmwareversion", ui->developmentFirmwareVersionLineEdit->text());
    addPackageMap.insert("deviomoduleversion", ui->developmentIoModuleVersionLineEdit->text());

    addPackageMap.insert("runosversion", ui->runtimeOsVersionLabel->text());
    addPackageMap.insert("runkernelversion", ui->runtimeKernelVersionLabel->text());
    addPackageMap.insert("runsocversion", ui->runtimeSocVersionLabel->text());
    addPackageMap.insert("runfirmwareversion", ui->runtimeFirmwareVersionLabel->text());
    addPackageMap.insert("runiomoduleversion", ui->runtimeIoModuleVersionLabel->text());

    addPackageMap.insert("installreason", ui->installReasonLineEdit->text());
    addPackageMap.insert("installresult", ui->installResultLineEdit->text());
    addPackageMap.insert("installwarning", ui->installWarningLineEdit->text());

    if (operType == ADDPKGINFO)
    {
        QStringList pkgList;
        if (companyPkgMap->contains(companyName))
        {
            QMap<QString, QStringList>::const_iterator itor = companyPkgMap->find(companyName);
            while (itor != companyPkgMap->end() && itor.key() == companyName) {
                pkgList = itor.value();
                itor++;
            }
        }
        pkgList.append(packageName);

        companyPkgMap->insert(companyName, pkgList);
        packageNoSelect->removeOne(packageName);
    }

    packageMap->insert(packageName, addPackageMap);

    emit packageInfoChanged();

    close();
}

void AddPackageDialog::on_cancelButton_clicked()
{
    close();
}
