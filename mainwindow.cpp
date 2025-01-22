#include "mainwindow.h"
#include "OptionsDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    optionsPushButton = new QPushButton("Options", this);
    QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_optionsPushButtonClicked()
{
    OptionsDialog optionDialog(this);

//    optionBox.setModel(photoReducermodel);

    optionDialog.show();
    if (optionDialog.exec() == QDialog::Accepted)
    {
    }
}

