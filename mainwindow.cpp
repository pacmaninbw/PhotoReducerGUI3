#include "mainwindow.h"
#include "OptionsDialog.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    model = new PhotoReducerModel("model", this);
    connectModelAndMainWindowSignalsToSlots();

    setUpMainWindowUI();

    connect(optionsPushButton, &QPushButton::clicked, this, &MainWindow::on_optionsPushButton_Clicked);
    connect(resizePhotosButton, &QPushButton::clicked, this, &MainWindow::on_resizePhotosButton_Clicked);

    repaint();

}

MainWindow::~MainWindow()
{
    delete model;
}

/*
 * Slots
 */
void MainWindow::connectModelAndMainWindowSignalsToSlots()
{
    connect(model, &PhotoReducerModel::resizedPhotosCountValueChanged,
        this, &MainWindow::on_resizedPhotos_valueChanged);
    connect(model, &PhotoReducerModel::photosToResizeCountValueChanged,
        this, &MainWindow::on_photosToResizeCount_ValueChanged);
    connect(model, &PhotoReducerModel::sourceDirectoryValueChanged,
        this, &MainWindow::on_SourceDirectory_Changed);
    connect(model, &PhotoReducerModel::targetDirectoryValueChanged,
        this, &MainWindow::on_TargetDirectory_Changed);
}

void MainWindow::connectModelAndOptionsSignelsAndSlots(OptionsDialog* optionsDialog)
{
    connect(optionsDialog, &OptionsDialog::sourceDirectoryLEChanged,
        model, &PhotoReducerModel::optionsSourceDirectoryEdited);
    connect(optionsDialog, &OptionsDialog::targetDirectoryLEChanged,
        model, &PhotoReducerModel::optionsTargetDirectoryEdited);
    connect(optionsDialog, &OptionsDialog::optionsJPGFileTypeCheckBoxChanged,
        model, &PhotoReducerModel::optionsJPGCheckBoxChanged);
    connect(optionsDialog, &OptionsDialog::optionsPNGFileTypecheckBoxChanged,
        model, &PhotoReducerModel::optionsPNGCheckBoxChanged);
    connect(optionsDialog, &OptionsDialog::optionsSafeWebNameCheckBoxChanged,
        model, &PhotoReducerModel::optionsSafeWebNameChanged);
    connect(optionsDialog, &OptionsDialog::optionsOverwriteCheckBoxChanged,
        model, &PhotoReducerModel::optionsOverWriteFilesChanged);

    connect(optionsDialog, &OptionsDialog::optionsDoneFindPhotoFiles,
        model, &PhotoReducerModel::optionsGoodFindFiles);
}

void MainWindow::on_resizedPhotos_valueChanged(std::size_t resizedPhotoCount)
{
    resizedPhotosLcdNumber->display(static_cast<int>(resizedPhotoCount));
    resizeProgressBar->setValue(static_cast<int>(resizedPhotoCount));
}

void MainWindow::on_photosToResizeCount_ValueChanged(std::size_t photosToResize)
{
    filesToResizeLcdNumber->display(static_cast<int>(photosToResize));
}

void MainWindow::on_SourceDirectory_Changed(QString srcDir)
{
    sourceDirectoryValue->setText(srcDir);
}

void MainWindow::on_TargetDirectory_Changed(QString targetDir)
{
    targetDirectoryValue->setText(targetDir);
}

void MainWindow::on_optionsPushButton_Clicked()
{
    OptionsDialog optionDialog(this);
//    optionDialog.resize(500,500);

    connectModelAndOptionsSignelsAndSlots(&optionDialog);

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
void MainWindow::setUpMainWindowUI()
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

    sourceDirectoryValue = createDirectoryDisplayLab("sourceDirectoryValue");
    mwLayout->addWidget(sourceDirectoryValue, 0, Qt::AlignHCenter);
    sourceDirectoryValue->setText(model->getSourceDirectory());

    targetDirectoryLabel = createNamedLabel("Target Directory", "targetDirectoryLabel");
    mwLayout->addWidget(targetDirectoryLabel, 0, Qt::AlignHCenter);

    targetDirectoryValue = createDirectoryDisplayLab("targetDirectoryValue");
    mwLayout->addWidget(targetDirectoryValue, 0, Qt::AlignHCenter);
    targetDirectoryValue->setText(model->getTargetDirectory());
}

void MainWindow::setUpProgressDisplays()
{
    photoCountHBoxLayout = new QHBoxLayout;
    mwLayout->addLayout(photoCountHBoxLayout, 0);

    filesToResizeVBoxLayout = new QVBoxLayout;
    photoCountHBoxLayout->addLayout(filesToResizeVBoxLayout, 0);

    resizePhotosVBoxLayout = new QVBoxLayout;
    photoCountHBoxLayout->addLayout(resizePhotosVBoxLayout, 0);

    filesToResizeLabel = createNamedLabel("Photos to Resize", "filesToResizeLabel");
    filesToResizeVBoxLayout->addWidget(filesToResizeLabel, 0, Qt::AlignHCenter);

    filesToResizeLcdNumber = createAndConfigureLCD(
        "filesToResizeLcdNumber", model->getPhotosToResizeCount());
    filesToResizeVBoxLayout->addWidget(filesToResizeLcdNumber, 0, Qt::AlignHCenter);

    resizedPhotosLabel = createNamedLabel("Resized Photos","resizedPhotosLabel");
    resizePhotosVBoxLayout->addWidget(resizedPhotosLabel, 0, Qt::AlignHCenter);

    resizedPhotosLcdNumber = createAndConfigureLCD(
        "resizedPhotosLcdNumber", model->getResizedPhotoCount());
    resizePhotosVBoxLayout->addWidget(resizedPhotosLcdNumber, 0, Qt::AlignHCenter);

    resizeProgressBar = createAndConfigureProgressBar(
        "resizeProgressBar", model->getResizedPhotoCount());
    mwLayout->addWidget(resizeProgressBar, 0, Qt::AlignHCenter);
}

QLCDNumber *MainWindow::createAndConfigureLCD(const char *lcdName, const int initValue)
{
    QLCDNumber* lcd = new QLCDNumber;

    lcd->setObjectName(QString::fromUtf8(lcdName));

    QString lcdStyle = generateWidthAndHeightStyleString(lcdWidth, lcdHeight);
    lcdStyle += " background-color: black; color: yellow;";
    lcd->setStyleSheet(lcdStyle);

    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setDigitCount(lcdDigitCount);
    lcd->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lcd->display(initValue);

    return lcd;
}

QProgressBar *MainWindow::createAndConfigureProgressBar(const char* objectName, const int initValue)
{
    QProgressBar* progressBar = new QProgressBar(centralwidget);
    progressBar->setObjectName(QString::fromUtf8(objectName));
    progressBar->setRange(0, 200);
    progressBar->setValue(initValue);

    progressBar->setStyleSheet(generateWidthAndHeightStyleString(
        static_cast<int>(maxOjectWidth * 0.7), progressBarHeight));

    progressBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return progressBar;
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
    newLabel->setStyleSheet(generateWidthAndHeightStyleString(getLabelWidth(newLabel), labelHeight));
    newLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return newLabel;
}

QLineEdit* MainWindow::createDirectoryDisplayLab(const char *labName)
{
    QLineEdit* newDisplay = new QLineEdit(centralwidget);
    newDisplay->setObjectName(QString::fromUtf8(labName));
    newDisplay->setReadOnly(true);

    QString displayStyle = generateWidthAndHeightStyleString(maxOjectWidth, labelHeight);
    newDisplay->setStyleSheet(displayStyle);

    newDisplay->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return newDisplay;
}

QPushButton* MainWindow::CreateNamedButton(const char* buttonText, const char* buttonName)
{
    QPushButton* newButton = new QPushButton(buttonText, centralwidget);

    newButton->setObjectName(QString::fromUtf8(buttonName));
    newButton->setStyleSheet(generateWidthAndHeightStyleString(newButton->width(), buttonHeight));

    return newButton;
}

QString MainWindow::generateWidthAndHeightStyleString(const int width, const int height)
{
    QString widthAndHeightStyleString("width: ");
    widthAndHeightStyleString += QString::number(width) + "; height:";
    widthAndHeightStyleString += QString::number(height) += ";";

    return widthAndHeightStyleString;
}

