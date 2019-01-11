#ifndef SHOWPKGINFODIALOG_H
#define SHOWPKGINFODIALOG_H

#include <QDialog>

namespace Ui {
class ShowPkgInfoDialog;
}

class ShowPkgInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowPkgInfoDialog(QWidget *parent = 0);
    ~ShowPkgInfoDialog();

private:
    Ui::ShowPkgInfoDialog *ui;
};

#endif // SHOWPKGINFODIALOG_H
