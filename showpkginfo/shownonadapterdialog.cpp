#include "shownonadapterdialog.h"
#include "ui_shownonadapterdialog.h"

ShowNonAdapterDialog::ShowNonAdapterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowNonAdapterDialog)
{
    ui->setupUi(this);
}

ShowNonAdapterDialog::~ShowNonAdapterDialog()
{
    delete ui;
}
