#include "signinfotabledialog.h"
#include "ui_signinfotabledialog.h"
#include <QDebug>
#include <QMessageBox>

SignInfoTableDialog::SignInfoTableDialog(QStringList pkgList, QWidget *parent) :
    QDialog(parent),
    packageNames(pkgList),
    packageNoChoose(pkgList),
    ui(new Ui::SignInfoTableDialog)
{
    ui->setupUi(this);
    initTableHeader();
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
    ui->factoryTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);


    ui->packageTable->setSelectionBehavior(QAbstractItemView::SelectRows); //行选择
    ui->packageTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->packageTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    ui->packageTable->horizontalHeader()->setResizeMode(1, QHeaderView::Interactive);
//    ui->packageTable->horizontalHeader()->setResizeMode(2, QHeaderView::Interactive);
    ui->packageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->packageTable->horizontalHeader()->setStretchLastSection(true);
    ui->packageTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
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
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要修改信息的厂商"),
                            QMessageBox::Ok);
        return;
    }
    QString currentFactory = ui->factoryTable->item(currentRow, 0)->text();

    AddCompanyDialog companyDialog(&companyMap, CHANGECOMP, currentFactory, this);
    companyDialog.setWindowTitle(QObject::tr("修改厂商信息"));
    connect(&companyDialog, SIGNAL(companyChanged()), this, SLOT(factoryTableAddItem()));
    companyDialog.exec();

}


void SignInfoTableDialog::on_viewFactoryButton_clicked()
{
    int currentRow = ui->factoryTable->currentRow();
    if (currentRow == -1)
    {
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要查看详情的厂商"),
                            QMessageBox::Ok);
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
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要删除的厂商"),
                            QMessageBox::Ok);
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
    int currentRow = ui->factoryTable->currentRow();
    qDebug() << "currentRow == " << currentRow;

    if (currentRow == -1)
    {
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要添加软件包的厂商"),
                            QMessageBox::Ok);
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
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要修改信息的软件"),
                            QMessageBox::Ok);
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
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要查看详情的软件"),
                            QMessageBox::Ok);
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
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要删除的软件"),
                            QMessageBox::Ok);
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
