#include "mainwindow.h"
#include "OptionsDialog.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setUpUI();

    connect(optionsPushButton, &QPushButton::clicked, this, &MainWindow::on_optionsPushButton_Clicked);
    connect(resizePhotosButton, &QPushButton::clicked, this, &MainWindow::on_resizePhotosButton_Clicked);
}

MainWindow::~MainWindow()
{
    delete filesToResizeLabel;
    delete filesToResizeLcdNumber;
    delete resizedPhotosLabel;
    delete resizedPhotosLcdNumber;
    delete sourceDirectoryLabel;
    delete resizeProgressBar;
    delete sourceDirectoryValueLabel;
    delete targetDirectoryLabel;
    delete targetDirectoryValueLabel;
    delete optionsPushButton;
    delete resizePhotosButton;
    delete resizePhotosVBoxLayout;
    delete filesToResizeVBoxLayout;
    delete photoCountHBoxLayout;
    delete mwLayout;
    delete centralwidget;
}

/*
 * Slots
 */
void MainWindow::on_optionsPushButton_Clicked()
{
    OptionsDialog optionDialog(this);
    optionDialog.resize(500,500);


//    optionBox.setModel(photoReducermodel);

    if (optionDialog.exec() == QDialog::Accepted)
    {
    }
}

void MainWindow::on_resizePhotosButton_Clicked()
{
}

/*
 * Private UI methods
 */
void MainWindow::setUpUI()
{

    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    mwLayout = new QVBoxLayout(centralwidget);

    optionsPushButton = CreateNamedButton("Options", "optionsPushButton");
    mwLayout->addWidget(optionsPushButton, 0, Qt::AlignHCenter);

    setUpProgressDisplays();

    setUpDirectoryDisplays();

    resizePhotosButton = CreateNamedButton("Resize Photos", "resizePhotosButton");
    resizePhotosButton->setDisabled(true);
    mwLayout->addWidget(resizePhotosButton, 0, Qt::AlignHCenter);

    resize(mainWindowWidth, mainWindowHeight);

    setCentralWidget(centralwidget);
}

void MainWindow::setUpDirectoryDisplays()
{
    sourceDirectoryLabel = createNamedLabel("Source Directory", "sourceDirectoryLabel");
    mwLayout->addWidget(sourceDirectoryLabel, 0, Qt::AlignHCenter);

    sourceDirectoryValueLabel = createDirectoryDisplayLab("sourceDirectoryValueLabel");
    mwLayout->addWidget(sourceDirectoryValueLabel, 0, Qt::AlignHCenter);

    targetDirectoryLabel = createNamedLabel("Target Directory", "targetDirectoryLabel");
    mwLayout->addWidget(targetDirectoryLabel, 0, Qt::AlignHCenter);

    targetDirectoryValueLabel = createDirectoryDisplayLab("targetDirectoryValueLabel");
    mwLayout->addWidget(targetDirectoryValueLabel, 0, Qt::AlignHCenter);
}

void MainWindow::setUpProgressDisplays()
{
    resizeProgressBar = new QProgressBar(centralwidget);
    resizeProgressBar->setRange(0, 200);
    resizeProgressBar->setValue(100);
    resizeProgressBar->setGeometry(0, 0, 500, 50);
    resizeProgressBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    mwLayout->addWidget(resizeProgressBar, 0, Qt::AlignHCenter);

    photoCountHBoxLayout = new QHBoxLayout;
    mwLayout->addLayout(photoCountHBoxLayout, 0);

    filesToResizeVBoxLayout = new QVBoxLayout;
    photoCountHBoxLayout->addLayout(filesToResizeVBoxLayout, 0);

    resizePhotosVBoxLayout = new QVBoxLayout;
    photoCountHBoxLayout->addLayout(resizePhotosVBoxLayout, 0);

    filesToResizeLabel = createNamedLabel("Photos to Resize", "filesToResizeLabel");
    filesToResizeVBoxLayout->addWidget(filesToResizeLabel, 0, Qt::AlignHCenter);

    filesToResizeLcdNumber = createAndConfigureLCD("filesToResizeLcdNumber", 200);
    filesToResizeVBoxLayout->addWidget(filesToResizeLcdNumber, 0, Qt::AlignHCenter);

    resizedPhotosLabel = createNamedLabel("Resized Photos","resizedPhotosLabel");
    resizePhotosVBoxLayout->addWidget(resizedPhotosLabel, 0, Qt::AlignHCenter);

    resizedPhotosLcdNumber = createAndConfigureLCD("resizedPhotosLcdNumber", 100);
    resizePhotosVBoxLayout->addWidget(resizedPhotosLcdNumber, 0, Qt::AlignHCenter);
}

QLCDNumber *MainWindow::createAndConfigureLCD(const char *lcdName, const int initValue)
{
    QLCDNumber* lcd = new QLCDNumber;

    lcd->setObjectName(QString::fromUtf8(lcdName));

    QPalette palette = lcd->palette();
    palette.setColor(QPalette::Window, Qt::black);
    palette.setColor(QPalette::WindowText, Qt::green);
    lcd->setAutoFillBackground(true);
    lcd->setPalette(palette);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setDigitCount(lcdDigitCount);
    lcd->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lcd->setGeometry(0, 0, 200, lcdHeight);
    lcd->display(initValue);

    return lcd;
}

int MainWindow::getLabelWidth(QLabel *lab)
{
    QFont currentFont = lab->font();
    QFontMetrics fm(currentFont);
    return fm.horizontalAdvance(lab->text());
}

QLabel *MainWindow::createNamedLabel(const char *labText, const char *labName)
{
    QLabel* newLabel;

    newLabel = new QLabel(labText, centralwidget);
    newLabel->setObjectName(QString::fromUtf8(labName));
    newLabel->setGeometry(0, 0, getLabelWidth(newLabel), labelHeight);
    newLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return newLabel;
}

QLabel *MainWindow::createDirectoryDisplayLab(const char *labName)
{
    QString blankLabValue;
    for (int i = 0; i < 160; i++)
    {
        blankLabValue += ' ';
    }

    QLabel* newDisplay = new QLabel(blankLabValue, centralwidget);
    newDisplay->setObjectName(QString::fromUtf8(labName));
    newDisplay->setGeometry(0, 0, maxOjectWidth, labelHeight);
    newDisplay->setFrameShape(QFrame::Box);
    newDisplay->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return newDisplay;
}

QPushButton* MainWindow::CreateNamedButton(const char* buttonText, const char* buttonName)
{
    QPushButton* newButton = new QPushButton(buttonText, centralwidget);

    newButton->setObjectName(QString::fromUtf8(buttonName));
    newButton->setGeometry(0, 0, newButton->width(), buttonHeight);

    return newButton;
}
