#include "devicefactorydialog.h"
#include "ui_devicefactorydialog.h"

DeviceFactoryDialog::DeviceFactoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceFactoryDialog)
{
    ui->setupUi(this);
}

DeviceFactoryDialog::~DeviceFactoryDialog()
{
    delete ui;
}
