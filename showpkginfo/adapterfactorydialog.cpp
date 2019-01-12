#include "adapterfactorydialog.h"
#include "ui_adapterfactorydialog.h"

AdapterFactoryDialog::AdapterFactoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdapterFactoryDialog)
{
    ui->setupUi(this);
}

AdapterFactoryDialog::~AdapterFactoryDialog()
{
    delete ui;
}
