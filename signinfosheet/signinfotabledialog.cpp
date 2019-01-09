#include "signinfotabledialog.h"
#include "ui_signinfotabledialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>

SignInfoTableDialog::SignInfoTableDialog(QStringList pkgList, QWidget *parent) :
    QDialog(parent),
    packageNames(pkgList),
    packageNoChoose(pkgList),
    ui(new Ui::SignInfoTableDialog)
{
    ui->setupUi(this);
    initTableHeader();
    getPlatInfo();
    connect(ui->factoryTable, SIGNAL(itemSelectionChanged()), this, SLOT(packageTableAddItem()));
}

SignInfoTableDialog::~SignInfoTableDialog()
{
    delete ui;
}

void SignInfoTableDialog::factoryTableAddItem()
{
    ui->factoryTable->setRowCount(0);
    QMap <QString, QMap<QString, QString> >::iterator itor;

    for (itor = companyMap.begin(); itor != companyMap.end(); itor++)
    {
        int row = ui->factoryTable->rowCount();
        ui->factoryTable->setRowCount(row+1);

        QMap <QString, QString> factoryInfo = itor.value();

        QTableWidgetItem * facItem =  new QTableWidgetItem(factoryInfo["companyname"]);
        QTableWidgetItem * conItem = new QTableWidgetItem(factoryInfo["contactname"]);
        QTableWidgetItem * mobItem = new QTableWidgetItem(factoryInfo["mobilephone"]);

        ui->factoryTable->setItem(row, 0, facItem);
        ui->factoryTable->setItem(row, 1, conItem);
        ui->factoryTable->setItem(row, 2, mobItem);
    }

}

void SignInfoTableDialog::packageTableAddItem()
{
    ui->packageTable->setRowCount(0);

    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        return;
    }

    ui->packageTable->setRowCount(0);

    QString currentFactory = ui->factoryTable->item(currentRow, 0)->text();

    QStringList pkgList;
    QMap <QString, QStringList>::const_iterator iter = compPkgMap.find(currentFactory);
    while (iter != compPkgMap.end() && iter.key() == currentFactory) {
        pkgList = iter.value();
        iter++;
    }

    for (int i = 0; i < pkgList.count(); i++)
    {
        int row = ui->packageTable->rowCount();
        ui->packageTable->setRowCount(row+1);

        QString pkgName = pkgList.at(i);
        QMap <QString, QString> pkgInfoMap;
        QMap <QString, QMap<QString, QString> >::const_iterator itor = packageMap.find(pkgName);
        while (itor != packageMap.end() && itor.key() == pkgName) {
            pkgInfoMap = itor.value();
            itor++;
        }

        QTableWidgetItem * pkgNameItem =  new QTableWidgetItem(pkgInfoMap["name"]);
        QTableWidgetItem * proNameItem = new QTableWidgetItem(pkgInfoMap["productname"]);
//        QTableWidgetItem * mobItem = new QTableWidgetItem(factoryInfo[""]);

        ui->packageTable->setItem(row, 0, pkgNameItem);
        ui->packageTable->setItem(row, 1, proNameItem);
//        ui->factoryTable->setItem(row, 2, mobItem);

    }

}

void SignInfoTableDialog::initTableHeader()
{
    ui->factoryTable->setSelectionBehavior(QAbstractItemView::SelectRows); //行选择
    ui->factoryTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->factoryTable->horizontalHeader()->setResizeMode(0, QHeaderView::Interactive);
//    ui->factoryTable->horizontalHeader()->setResizeMode(2, QHeaderView::Interactive);
    ui->factoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->factoryTable->horizontalHeader()->setStretchLastSection(true);
//    ui->factoryTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui->packageTable->setSelectionBehavior(QAbstractItemView::SelectRows); //行选择
    ui->packageTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->packageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->packageTable->horizontalHeader()->setStretchLastSection(true);
}

void SignInfoTableDialog::on_addFactoryButton_clicked()
{
    AddCompanyDialog companyDialog(&companyMap, ADDCOMP,"", this);
    connect(&companyDialog, SIGNAL(companyChanged()), this, SLOT(factoryTableAddItem()));
    companyDialog.exec();
}


void SignInfoTableDialog::on_modifyFactoryButton_clicked()
{

    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要修改信息的厂商")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QString currentFactory = ui->factoryTable->item(currentRow, 0)->text();

    AddCompanyDialog companyDialog(&companyMap, CHANGECOMP, currentFactory, this);
    companyDialog.setWindowTitle(QString::fromUtf8("修改厂商信息"));
    connect(&companyDialog, SIGNAL(companyChanged()), this, SLOT(factoryTableAddItem()));
    companyDialog.exec();

}

void SignInfoTableDialog::on_viewFactoryButton_clicked()
{
    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要查看详情的厂商")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QString factoryName = ui->factoryTable->item(currentRow, 0)->text();
    CompanyDetailDialog companyDetailDialog(companyMap, factoryName, this);
    companyDetailDialog.exec();
}

void SignInfoTableDialog::on_deleteFactoryButton_clicked()
{
    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要删除的厂商")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();
        return;
    }
    QStringList pkgList;
    QString currentFactory = ui->factoryTable->item(currentRow, 0)->text();
    QMap <QString, QStringList>::const_iterator iter = compPkgMap.find(currentFactory);
    while (iter != compPkgMap.end() && iter.key() == currentFactory) {
        pkgList = iter.value();
        iter++;
    }
    for (int i = 0; i < pkgList.count(); i++)
    {
        packageNoChoose.append(pkgList.at(i));
    }

    compPkgMap.remove(currentFactory);
    companyMap.remove(currentFactory);

    factoryTableAddItem();
    packageTableAddItem();
}

void SignInfoTableDialog::on_addPackageButton_clicked()
{
    if (packageNoChoose.isEmpty())
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("没有可供添加的软件包")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }

    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要添加软件包的厂商")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }

    QString compName = ui->factoryTable->item(currentRow, 0)->text();

    SelectPkgDialog selectPkgDialog(&compPkgMap, &packageMap, compName,&packageNoChoose, this);
    connect(&selectPkgDialog, SIGNAL(packageChanged()), this, SLOT(packageTableAddItem()));
    selectPkgDialog.exec();
}

void SignInfoTableDialog::on_modifyPackageButton_clicked()
{
    int currentRow = ui->packageTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要修改信息的软件")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QString pkgName = ui->packageTable->item(currentRow, 0)->text();
    int compRow = ui->factoryTable->currentRow();
    QString companyName = ui->factoryTable->item(compRow, 0)->text();
    AddPackageDialog addPackageDialog(&compPkgMap, &packageMap, pkgName, companyName, &packageNoChoose, CHANGEPKGINFO, this);
    connect(&addPackageDialog, SIGNAL(packageInfoChanged()), this, SLOT(packageTableAddItem()));
    addPackageDialog.exec();
}

void SignInfoTableDialog::on_viewPackageButton_clicked()
{
    int currentRow = ui->packageTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要查看详情的软件")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QString currentPackage = ui->packageTable->item(currentRow, 0)->text();
    AddPackageDialog addPackageDialog(&compPkgMap, &packageMap, currentPackage, "", &packageNoChoose, SHOWPKGINFO, this);
    addPackageDialog.exec();
}

void SignInfoTableDialog::on_deletePackageButton_clicked()
{
    int currentRow = ui->packageTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请选择要删除的软件")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QString currentPackage = ui->packageTable->item(currentRow, 0)->text();

    QStringList pkgList;
    int fctoryCurrentRow = ui->factoryTable->currentRow();
    QString currentFactory = ui->factoryTable->item(fctoryCurrentRow, 0)->text();
    QMap <QString, QStringList>::const_iterator iter = compPkgMap.find(currentFactory);
    while (iter != compPkgMap.end() && iter.key() == currentFactory) {
        pkgList = iter.value();
        iter++;
    }
    pkgList.removeOne(currentPackage);
    compPkgMap.insert(currentFactory,pkgList);

    packageMap.remove(currentPackage);
    packageNoChoose.append(currentPackage);
    packageTableAddItem();
}


void SignInfoTableDialog::on_sureButton_clicked()
{
    if (!packageNoChoose.isEmpty())
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请对所有软件包添加信息")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }
    QVariantList type;
    QVariantMap factory;  //对象

    QVariantList company;	//数组

    QMap <QString, QMap<QString, QString> >::iterator itor;
    for (itor = companyMap.begin(); itor != companyMap.end(); ++itor)
    {
        QMap<QString, QString> compInfoMap = itor.value();

        QVariantMap contactInfo;
        contactInfo.insert("mobilephone", compInfoMap["mobilephone"]);
        contactInfo.insert("telephone", compInfoMap["telephone"]);

        QVariantMap addressInfo;
        addressInfo.insert("province", compInfoMap["province"]);
        addressInfo.insert("city", compInfoMap["city"]);

        QVariantMap platformInfo;
        platformInfo.insert("type", ui->platTypeLabel->text());
        platformInfo.insert("form", ui->platFormLabel->text());

        QVariantList productInfo;	//数组

        QMap<QString, QStringList>::const_iterator iter = compPkgMap.find(compInfoMap["companyname"]);
        QStringList productInfoList = iter.value();
        for (int i = 0; i < productInfoList.count(); i++)
        {
            QString proName = productInfoList.at(i);
            QMap <QString, QMap<QString, QString> >::const_iterator iterator = packageMap.find(proName);
            QMap <QString, QString> proInfoMap = iterator.value();

            QVariantList dependencyInfo;
            QStringList depends = proInfoMap["dependency"].split(" ");
            for (int i = 0; i < depends.count(); i++)
            {
               QVariantMap depend;
               depend.insert("dependedlib", depends.at(i));
               dependencyInfo.append(depend);
            }

            QVariantMap developmentPkgDevInfo;
            developmentPkgDevInfo.insert("name", proInfoMap["name"]);
            developmentPkgDevInfo.insert("version", proInfoMap["version"]);
            developmentPkgDevInfo.insert("arch", proInfoMap["arch"]);
            developmentPkgDevInfo.insert("dependency", dependencyInfo);
            developmentPkgDevInfo.insert("osversion", proInfoMap["devosversion"]);
            developmentPkgDevInfo.insert("kernelversion", proInfoMap["devkernelversion"]);
            developmentPkgDevInfo.insert("socversion", proInfoMap["devsocversion"]);
            developmentPkgDevInfo.insert("firmwareversion", proInfoMap["devfirmwareversion"]);
            developmentPkgDevInfo.insert("iomoduleversion", proInfoMap["deviomoduleversion"]);
            developmentPkgDevInfo.insert("desc", proInfoMap["desc"]);

            QVariantMap runtimeDevInfo;
            runtimeDevInfo.insert("osversion", proInfoMap["runosversion"]);
            runtimeDevInfo.insert("kernelversion", proInfoMap["runkernelversion"]);
            runtimeDevInfo.insert("socversion", proInfoMap["runsocversion"]);
            runtimeDevInfo.insert("firmwareversion", proInfoMap["runfirmwareversion"]);
            runtimeDevInfo.insert("iomoduleversion", proInfoMap["runiomoduleversion"]);

            QVariantMap proInfo;
            proInfo.insert("productname", proInfoMap["productname"]);
            proInfo.insert("developmentpkgdevinfo", developmentPkgDevInfo);
            proInfo.insert("runtimedevinfo", runtimeDevInfo);
            proInfo.insert("installreason", proInfoMap["installreason"]);
            proInfo.insert("installresult", proInfoMap["installresult"]);
            proInfo.insert("installwarning", proInfoMap["installwarning"]);

            productInfo.append(proInfo);
        }

        QVariantMap comp;
        comp.insert("contactname", compInfoMap["contactname"]);
        comp.insert("contactinfo", contactInfo);
        comp.insert("date", compInfoMap["date"]);
        comp.insert("companyname", compInfoMap["companyname"]);
        comp.insert("addressinfo", addressInfo);
        comp.insert("platform", platformInfo);
        comp.insert("productinfo", productInfo);

        company.append(comp);
    }

       factory.insert("nonadapterfactory", company);
       type.append(factory);

       QJson::Serializer serializer;
       bool ok;
       QByteArray jsondata = serializer.serialize(type);
       json = &jsondata;

       qDebug() << "json == " << json;

       close();
}

void SignInfoTableDialog::on_cancelButton_clicked()
{
    close();
}

void SignInfoTableDialog::getPlatInfo()
{
    sysinfo_zyj sysinfo;
//    get_zyj_sysinfo(&sysinfo);

    QString osName = QString(sysinfo.osname);
    qDebug() << "sysinfo.osname == " << sysinfo.osname;
    qDebug() << "osName == " << osName;
    if (osName.isEmpty())
    {
        ui->platTypeLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        ui->platTypeLabel->setText(
                    osName);
    }
    if (osName.isEmpty())
    {
        ui->platFormLabel->setText(
                    QString::fromUtf8("Unknown"));
    }
    else
    {
        if (osName.contains(QString::fromUtf8("桌面")))
        {
            ui->platFormLabel->setText(
                        QString::fromUtf8("客户端"));
        }
//        ui->platFormLabel->setText(
//                    QString::fromUtf8("客户端"));
    }

}

