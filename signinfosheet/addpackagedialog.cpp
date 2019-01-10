#include "addpackagedialog.h"
#include "ui_addpackagedialog.h"

#include <QMessageBox>
#include <QProcess>
#include <QDebug>

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
    init();
    getSysInfo();
    getPackageInfoByName();
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
                    QString(sysinfo.osver));
    }

    if (strlen(sysinfo.kernelver) == 0)
    {
        ui->runtimeKernelVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeKernelVersionLabel->setText(
                    QString(sysinfo.kernelver));
    }

    if (strlen(sysinfo.socversion) == 0)
    {
        ui->runtimeSocVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeSocVersionLabel->setText(
                    QString(sysinfo.socversion));
    }

    if (strlen(sysinfo.biosversion) == 0)
    {
        ui->runtimeFirmwareVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        QString firmName = QString(sysinfo.biosversion).split("(").at(0).trimmed();
        ui->runtimeFirmwareVersionLabel->setText(firmName);
    }

    if (strlen(sysinfo.ioversion) == 0)
    {
        ui->runtimeIoModuleVersionLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->runtimeIoModuleVersionLabel->setText(
                    QString(sysinfo.ioversion));
    }
}

void AddPackageDialog::getPackageInfoByName()
{
    ui->pkgNameLabel->setText(packageName);
    ui->pkgNameLabel->setToolTip(packageName);

    QProcess process;
    QString cmd = QString("dpkg -f %1").arg(packageName);

    process.start(cmd);
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();

    QString strOutPut = output;

    QStringList pkgInfo = strOutPut.split("\n");

    for (int i = 0; i < pkgInfo.count(); i++)
    {
        if (pkgInfo.at(i).contains("Version:"))
        {
            QString pkgVersion = pkgInfo.at(i).section(':', 1).trimmed();
            ui->pkgVersionLabel->setText(pkgVersion);
        }
        if (pkgInfo.at(i).contains("Architecture:"))
        {
            QString pkgArch = pkgInfo.at(i).section(":", 1).trimmed();
            ui->pkgArchLabel->setText(pkgArch);
        }
        if (pkgInfo.at(i).contains("Depends:"))
        {
            QString pkgDepends = pkgInfo.at(i).section(":", 1).trimmed();
            ui->pkgDependencyLabel->setText(pkgDepends);
            ui->pkgDependencyLabel->setToolTip(pkgDepends);
        }
    }
}

void AddPackageDialog::setTochangePkgInfo()
{
    QMap<QString, QMap<QString, QString> >::const_iterator itor = packageMap->find(packageName);
    QMap<QString, QString> packageInfoMap = itor.value();

    ui->productNameLineEdit->setText(packageInfoMap.value("productname"));
    ui->descTextEdit->setText(packageInfoMap.value("desc"));
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

    ui->installReasonTextEdit->setText(packageInfoMap.value("installreason"));
    ui->installResultTextEdit->setText(packageInfoMap.value("installresult"));
    ui->installWarningTextEdit->setText(packageInfoMap.value("installwarning"));

    if (operType == SHOWPKGINFO)
    {
//        setFocusPolicy(Qt::NoFocus);
        ui->productNameLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->descTextEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentOsVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentKernelVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentSocVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentFirmwareVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->developmentIoModuleVersionLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installReasonTextEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installResultTextEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
        ui->installWarningTextEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");

        ui->cancelButton->hide();
        ui->sureButton->hide();
    }
}

void AddPackageDialog::init()
{
    QRegExp regExp("^[-|0-9|A-Z|a-z|\.|^\s]{1,128}$");
    ui->developmentOsVersionLineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->developmentKernelVersionLineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->developmentSocVersionLineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->developmentFirmwareVersionLineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->developmentIoModuleVersionLineEdit->setValidator(new QRegExpValidator(regExp,this));
}

void AddPackageDialog::on_sureButton_clicked()
{
    QString productNameStr = ui->productNameLineEdit->text();
    QString descStr = ui->descTextEdit->toPlainText();
    QString nameStr = ui->pkgNameLabel->text();
    QString versionStr = ui->pkgVersionLabel->text();
    QString archStr = ui->pkgArchLabel->text();
    QString dependencyStr = ui->pkgDependencyLabel->text();

    QString devosVersionStr = ui->developmentOsVersionLineEdit->text();
    QString devkernelVersionStr = ui->developmentKernelVersionLineEdit->text();
    QString devsocVersionStr = ui->developmentSocVersionLineEdit->text();
    QString devfirmwareversionStr = ui->developmentFirmwareVersionLineEdit->text();
    QString deviomoduleVersionStr = ui->developmentIoModuleVersionLineEdit->text();

    QString runosVersionStr = ui->runtimeOsVersionLabel->text();
    QString runkernelVersionStr = ui->runtimeKernelVersionLabel->text();
    QString runsocVersionStr = ui->runtimeSocVersionLabel->text();
    QString runfirmwareVersionStr = ui->runtimeFirmwareVersionLabel->text();
    QString runiomoduleVersionStr = ui->runtimeIoModuleVersionLabel->text();

    QString installReasonStr = ui->installReasonTextEdit->toPlainText();
    QString installResultStr = ui->installResultTextEdit->toPlainText();
    QString installWarningStr = ui->installWarningTextEdit->toPlainText();

    if (productNameStr.isEmpty()
            || descStr.isEmpty()
            || devosVersionStr.isEmpty()
            || devkernelVersionStr.isEmpty()
            || devsocVersionStr.isEmpty()
            || devfirmwareversionStr.isEmpty()
            || deviomoduleVersionStr.isEmpty()
            || installReasonStr.isEmpty()
            || installResultStr.isEmpty()
            || installWarningStr.isEmpty())
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请确保所有必填内容非空")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }

    QMap<QString, QString> addPackageMap;

    addPackageMap.insert("productname", productNameStr);
    addPackageMap.insert("desc", descStr);
    addPackageMap.insert("name", nameStr);
    addPackageMap.insert("version", versionStr);
    addPackageMap.insert("arch", archStr);
    addPackageMap.insert("dependency", dependencyStr);

    addPackageMap.insert("devosversion", devosVersionStr);
    addPackageMap.insert("devkernelversion", devkernelVersionStr);
    addPackageMap.insert("devsocversion", devsocVersionStr);
    addPackageMap.insert("devfirmwareversion", devfirmwareversionStr);
    addPackageMap.insert("deviomoduleversion", deviomoduleVersionStr);

    addPackageMap.insert("runosversion", runosVersionStr);
    addPackageMap.insert("runkernelversion", runkernelVersionStr);
    addPackageMap.insert("runsocversion", runsocVersionStr);
    addPackageMap.insert("runfirmwareversion", runfirmwareVersionStr);
    addPackageMap.insert("runiomoduleversion", runiomoduleVersionStr);

    addPackageMap.insert("installreason", installReasonStr);
    addPackageMap.insert("installresult", installResultStr);
    addPackageMap.insert("installwarning", installWarningStr);

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

void AddPackageDialog::on_descTextEdit_textChanged()
{
    QString textContent = ui->descTextEdit->toPlainText();
    int length = textContent.count();
    int maxLength = 1024;
    if(length > maxLength)
    {
        QTextCursor cursor = ui->descTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection())
        {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        ui->descTextEdit->setTextCursor(cursor);
    }
}

void AddPackageDialog::on_installReasonTextEdit_textChanged()
{
    QString textContent = ui->installReasonTextEdit->toPlainText();
    int length = textContent.count();
    int maxLength = 1024;
    if(length > maxLength)
    {
        QTextCursor cursor = ui->installReasonTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection())
        {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        ui->installReasonTextEdit->setTextCursor(cursor);
    }
}

void AddPackageDialog::on_installResultTextEdit_textChanged()
{
    QString textContent = ui->installResultTextEdit->toPlainText();
    int length = textContent.count();
    int maxLength = 1024;
    if(length > maxLength)
    {
        QTextCursor cursor = ui->installResultTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection())
        {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        ui->installResultTextEdit->setTextCursor(cursor);
    }
}

void AddPackageDialog::on_installWarningTextEdit_textChanged()
{
    QString textContent = ui->installWarningTextEdit->toPlainText();
    int length = textContent.count();
    int maxLength = 1024;
    if(length > maxLength)
    {
        QTextCursor cursor = ui->installWarningTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection())
        {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        ui->installWarningTextEdit->setTextCursor(cursor);
    }
}
