#include "mainwindow.h"
#include "OptionsDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    constexpr int mainWindowWidth = 800;
    constexpr int mainWindowHeight = 661;

    resize(mainWindowWidth, mainWindowHeight);

    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    optionsPushButton = new QPushButton("Options", centralwidget);
    optionsPushButton->setObjectName("optionsPushButton");

    setCentralWidget(centralwidget);

    connect(optionsPushButton, &QPushButton::clicked, this, &MainWindow::on_optionsPushButton_Clicked);
}

MainWindow::~MainWindow()
{
}

QLCDNumber *MainWindow::createAndConfigureLCD(const char *lcdName)
{
    QLCDNumber* lcd = new QLCDNumber;

    QPalette palette = lcd->palette();
    palette.setColor(QPalette::Window, Qt::black); // Set background color to black
    palette.setColor(QPalette::WindowText, Qt::green); // Set text color to green
    lcd->setAutoFillBackground(true);
    lcd->setPalette(palette);
    lcd->setSegmentStyle(QLCDNumber::Flat);

    return lcd;
}

void MainWindow::on_optionsPushButton_Clicked()
{
    OptionsDialog optionDialog(this);
    optionDialog.resize(500,500);


//    optionBox.setModel(photoReducermodel);

    if (optionDialog.exec() == QDialog::Accepted)
    {
    }
}

