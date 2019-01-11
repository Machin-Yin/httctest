#include "showpkginfodialog.h"
#include "ui_showpkginfodialog.h"

ShowPkgInfoDialog::ShowPkgInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowPkgInfoDialog)
{
    ui->setupUi(this);
}

ShowPkgInfoDialog::~ShowPkgInfoDialog()
{
    delete ui;
}
