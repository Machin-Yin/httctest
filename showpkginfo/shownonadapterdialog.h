#ifndef SHOWNONADAPTERDIALOG_H
#define SHOWNONADAPTERDIALOG_H

#include <QDialog>

namespace Ui {
class ShowNonAdapterDialog;
}

class ShowNonAdapterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowNonAdapterDialog(QWidget *parent = 0);
    ~ShowNonAdapterDialog();

private:
    Ui::ShowNonAdapterDialog *ui;
};

#endif // SHOWNONADAPTERDIALOG_H
