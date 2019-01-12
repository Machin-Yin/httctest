#ifndef ADAPTERFACTORYDIALOG_H
#define ADAPTERFACTORYDIALOG_H

#include <QDialog>

namespace Ui {
class AdapterFactoryDialog;
}

class AdapterFactoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdapterFactoryDialog(QWidget *parent = 0);
    ~AdapterFactoryDialog();

private:
    Ui::AdapterFactoryDialog *ui;
};

#endif // ADAPTERFACTORYDIALOG_H
