#include <QDir>
#include "mainwindow.h"
#include "OptionsDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setUpUI();

    connect(optionsPushButton, &QPushButton::clicked, this, &MainWindow::on_optionsPushButton_Clicked);
}

MainWindow::~MainWindow()
{
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

/*
 * Private UI methods
 */
void MainWindow::setUpUI()
{
    resize(mainWindowWidth, mainWindowHeight);

    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    optionsPushButton = new QPushButton("Options", centralwidget);
    optionsPushButton->setObjectName("optionsPushButton");
    optionsPushButton->setGeometry(calculateHorizontalCenteredObjectRect(optionsPushButton->width(), buttonHeight));
    currentHeight += buttonHeight + verticleSpace;

    setUpDirectoryDisplays();

    setCentralWidget(centralwidget);
}

void MainWindow::setUpDirectoryDisplays()
{
    sourceDirectoryLabel = createCenteredLabel("Source Directory", "sourceDirectoryLabel");
    sourceDirectoryValueLabel = createDirectoryDisplayLab("sourceDirectoryValueLabel");

    targetDirectoryLabel = createCenteredLabel("Target Directory", "targetDirectoryLabel");
    targetDirectoryValueLabel = createDirectoryDisplayLab("targetDirectoryValueLabel");
}

QLCDNumber *MainWindow::createAndConfigureLCD(const char *lcdName)
{
    QLCDNumber* lcd = new QLCDNumber;

    lcd->setObjectName(QString::fromUtf8(lcdName));

    QPalette palette = lcd->palette();
    palette.setColor(QPalette::Window, Qt::black); // Set background color to black
    palette.setColor(QPalette::WindowText, Qt::green); // Set text color to green
    lcd->setAutoFillBackground(true);
    lcd->setPalette(palette);
    lcd->setSegmentStyle(QLCDNumber::Flat);

    return lcd;
}

QRect MainWindow::calculateHorizontalCenteredObjectRect(int objectWidth, int objectHeigth)
{
    int offsetBase = static_cast<int>(objectWidth / 2);
    int leftX = mainWindowHorizontalCenter - offsetBase;
    int topY = currentHeight;

    return QRect(leftX, topY, objectWidth, objectHeigth);
}

int MainWindow::getLabelWidth(QLabel *lab)
{
    QFont currentFont = lab->font();
    QFontMetrics fm(currentFont);
    return fm.horizontalAdvance(lab->text());
}

QLabel *MainWindow::createCenteredLabel(const char *labText, const char *labName)
{
    QLabel* newLabel;

    newLabel = new QLabel(labText, centralwidget);
    newLabel->setObjectName(QString::fromUtf8(labName));
    newLabel->setGeometry(calculateHorizontalCenteredObjectRect(
        getLabelWidth(newLabel), labelHeight));
    currentHeight += labelHeight + verticleSpace;

    return newLabel;
}

QLabel *MainWindow::createDirectoryDisplayLab(const char *labName)
{
    QLabel* newDisplay = new QLabel(centralwidget);
    newDisplay->setObjectName(QString::fromUtf8(labName));
    newDisplay->setGeometry(calculateHorizontalCenteredObjectRect(maxOjectWidth, labelHeight));
    newDisplay->setFrameShape(QFrame::Box);
    currentHeight += labelHeight + verticleSpace;

    return newDisplay;
}
