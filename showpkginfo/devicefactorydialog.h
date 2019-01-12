#ifndef DEVICEFACTORYDIALOG_H
#define DEVICEFACTORYDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceFactoryDialog;
}

class DeviceFactoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceFactoryDialog(QWidget *parent = 0);
    ~DeviceFactoryDialog();

private:
    Ui::DeviceFactoryDialog *ui;
};

#endif // DEVICEFACTORYDIALOG_H
