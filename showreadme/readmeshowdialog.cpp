#include "readmeshowdialog.h"
#include <QDebug>
#include <QHeaderView>

ReadmeShowDialog::ReadmeShowDialog(QString readmeStr, QString titleStr, QWidget *parent):
    QDialog(parent),
    pathStr(readmeStr)
{
    setWindowTitle(titleStr);

    initUi();
    initWidget();
    addItem();

    connect(sureButton, SIGNAL(clicked()), this, SLOT(on_sureButton_clicked()));
}

void ReadmeShowDialog::initUi()
{
    setFixedSize(380, 400);

    tableWidget = new QTableWidget();
    sureButton = new QPushButton();
    mainLayout = new QVBoxLayout();
    botomLayout = new QHBoxLayout();

    botomLayout->addStretch();
    botomLayout->addWidget(sureButton);
    botomLayout->addStretch();

    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(botomLayout);

    mainLayout->setContentsMargins(20, 20, 20, 0);
    botomLayout->setContentsMargins(0, 10, 0, 15);

    setLayout(mainLayout);
}

void ReadmeShowDialog::initWidget()
{
    tableWidget->setColumnCount(2);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setFocusPolicy(Qt::NoFocus);
    tableWidget->setShowGrid(false);
    tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
    tableWidget->setColumnWidth(1, 0);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setVisible(false);

    sureButton->setText(QString::fromUtf8("确定"));
}

void ReadmeShowDialog::addItem()
{
    QStringList pathList = pathStr.split("\n");
    for (int i = 0; i < pathList.count(); i++)
    {
        QString path = pathList.at(i);
        QTableWidgetItem * pathItem =  new QTableWidgetItem(path);
        int row = tableWidget->rowCount();
        tableWidget->setRowCount(row+1);
        tableWidget->setItem(row, 0, pathItem);
    }
}

void ReadmeShowDialog::on_sureButton_clicked()
{
    close();
}

ReadmeShowDialog::~ReadmeShowDialog()
{

}
