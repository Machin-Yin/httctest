#include "selectpkgdialog.h"
#include "ui_selectpkgdialog.h"
#include <QMessageBox>

SelectPkgDialog::SelectPkgDialog(QMap<QString, QStringList> *comPkgMap, QMap<QString, QMap<QString, QString> > *packageMap, QString compName, QStringList *pkgNoChoose, QWidget *parent) :
    QDialog(parent),
    companyPkgMap(comPkgMap),
    pkgMap(packageMap),
    companyName(compName),
    packageNoChoose(pkgNoChoose),
    ui(new Ui::SelectPkgDialog)
{
    ui->setupUi(this);
    init();
    loadAllSelectItems();

    connect(ui->selectPkgTable, SIGNAL(itemChanged(QTableWidgetItem*)),
         this, SLOT(changed(QTableWidgetItem*)));
}

SelectPkgDialog::~SelectPkgDialog()
{
    delete ui;
}

void SelectPkgDialog::init()
{
    ui->selectPkgTable->setColumnWidth(0, 80);

    ui->selectPkgTable->horizontalHeader()->setResizeMode(0,QHeaderView::Fixed);
    ui->selectPkgTable->horizontalHeader()->setStretchLastSection(true);
}

void SelectPkgDialog::loadAllSelectItems()
{   
    for (int i = 0; i < packageNoChoose->count(); i++)
    {
        int row = ui->selectPkgTable->rowCount();
        ui->selectPkgTable->setRowCount(row + 1);

        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromUtf8("选择"));
        item0->setData(Qt::UserRole, QString::fromUtf8("选择"));
        item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *item1 = new QTableWidgetItem(packageNoChoose->at(i));
        ui->selectPkgTable->setItem(row, 0, item0);
        ui->selectPkgTable->setItem(row, 1, item1);

        ui->selectPkgTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        item0->setCheckState(Qt::Unchecked);
    }
}

void SelectPkgDialog::on_buttonBox_accepted()
{
    int rowCount = ui->selectPkgTable->rowCount();
    QString pkgName;

    for(int row = 0; row < rowCount; row++)
    {
        Qt::CheckState state = ui->selectPkgTable->item(row, 0)->checkState();

        if (Qt::Checked == state)
        {
            pkgName = ui->selectPkgTable->item(row, 1)->text();
            break;
        }
    }
    if (pkgName.isEmpty())
    {
        QMessageBox::information(this,
                            QObject::tr("提示"),
                            QObject::tr("请选择要添加的软件包"),
                            QMessageBox::Ok);
        return;
    }

    AddPackageDialog addPackageDialog(companyPkgMap, pkgMap, pkgName, companyName, packageNoChoose, ADDPKGINFO, this);   //companyname,companypkgmap
    connect(&addPackageDialog, SIGNAL(packageInfoChanged()), this, SLOT(updatePackageInfo()));
    addPackageDialog.exec();

}

void SelectPkgDialog::changed(QTableWidgetItem *item)
{
    int row = ui->selectPkgTable->row(item);
    Qt::CheckState state = item->checkState();
    if (state == Qt::Checked)
    {
        int rowCount = ui->selectPkgTable->rowCount();
        for (int i = 0; i< rowCount; i++)
        {
            if (i != row)
            {
                QTableWidgetItem *item = ui->selectPkgTable->item(i, 0);
                item->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void SelectPkgDialog::updatePackageInfo()
{
    emit packageChanged();
}

