#include "PhotoReducerController.h"
#include <QString>

PhotoReducerController::PhotoReducerController(const char* modelName, QObject *parent)
    : QObject{parent}
{
    setObjectName(QString::fromUtf8(modelName));

}

void PhotoReducerController::createModel()
{
    model = new PhotoReducerModel("TheModel", this);
}

void PhotoReducerController::creatMainWindow()
{
    mainWindow = new MainWindow();
    mainWindow->setObjectName("MainWindow");
}

void PhotoReducerController::connectModelAndMainWindowSignalsToSlots()
{
    connect(model, &PhotoReducerModel::initMainWindowSourceDirectory,
        mainWindow, &MainWindow::on_SourceDirectory_Changed);
    connect(model, &PhotoReducerModel::initMainWindowTargetDirectory,
        mainWindow, &MainWindow::on_TargetDirectory_Changed);

    connect(model, &PhotoReducerModel::resizedPhotosCountValueChanged,
        mainWindow, &MainWindow::on_resizedPhotos_valueChanged);
    connect(model, &PhotoReducerModel::photosToResizeCountValueChanged,
        mainWindow, &MainWindow::on_photosToResizeCount_ValueChanged);
    connect(model, &PhotoReducerModel::sourceDirectoryValueChanged,
        mainWindow, &MainWindow::on_SourceDirectory_Changed);
    connect(model, &PhotoReducerModel::targetDirectoryValueChanged,
        mainWindow, &MainWindow::on_TargetDirectory_Changed);
}

void PhotoReducerController::connectControllerAndModelSignalsToSlots()
{
    connect(this, &PhotoReducerController::mainWindowReadyForInitialization,
        model, &PhotoReducerModel::initializeMainWindow);
    connect(this, &PhotoReducerController::optionDialogReadyForInitialization,
        model, &PhotoReducerModel::initializeOptionsDialog);
    connect(this, &PhotoReducerController::resizeAllPhotos,
            model, &PhotoReducerModel::resizeAllPhotos);
    connect(model, &PhotoReducerModel::enableMainWindowResizePhotosButton, this,
        &PhotoReducerController::enableMainWindowResizePhotosButton);
    connect(model, &PhotoReducerModel::acceptOptionsDialog,
        this, &PhotoReducerController::acceptOptionsDialog);
}

void PhotoReducerController::connectControllerAndMainWindowSignalsToSlots()
{
    connect(mainWindow, &MainWindow::mainWindowOptionsButtonPressed, this,
        &PhotoReducerController::mainWindowOptionsButtonPressedCreateOptionsDialog);
    connect(mainWindow, &MainWindow::resizeAllPhotos, this,
        &PhotoReducerController::mainWindowResizePhotosButtonClicked);
    connect(this, &PhotoReducerController::enablePhotoResizing, mainWindow,
        &MainWindow::enableResizePhotosButton);
}

void PhotoReducerController::initMainWindowValuesAndShow()
{
    emit mainWindowReadyForInitialization();
    mainWindow->show();
}

void PhotoReducerController::connectModelAndOptionsDialogSignalsToSlots()
{
    connectOptionDialogOutToModelIn();
    connectModelOutToOptionDialogIn();
}

/*
 * Please pardon the massive amount of code repetition in these functions.
 * I tried creating tables of signals and slots by examining the contents
 * of the QObject header file and using a declaration I found there,
 * unfortunately signals and slots are only partially implemented at
 * compile time and it generated compilation errors.
 */
void PhotoReducerController::connectOptionDialogOutToModelIn()
{
    // File Options
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
    connect(optionsDialog, &OptionsDialog::optionsaddExtensionLEChanged,
        model, &PhotoReducerModel::optionsAddExtensionChanged);

    // Photo Options
    connect(optionsDialog, &OptionsDialog::optionsMaintainRatioCBChanged,
        model, &PhotoReducerModel::optionsMaintainRatioChanged);
    connect(optionsDialog, &OptionsDialog::optionsDisplayResizedCBChanged,
        model, &PhotoReducerModel::optionsDisplayResizedChanged);
    connect(optionsDialog, &OptionsDialog::optionsMaxWidthLEChanged,
        model, &PhotoReducerModel::optionsMaxWidthChanged);
    connect(optionsDialog, &OptionsDialog::optionsMaxHeightLEChanged,
        model, &PhotoReducerModel::optionsMaxHeightChanged);
    connect(optionsDialog, &OptionsDialog::optionsScaleFactorLEChanged,
        model, &PhotoReducerModel::optionsScaleFactorChanged);

    connect(optionsDialog, &OptionsDialog::optionsGoodFindFiles,
        model, &PhotoReducerModel::optionsGoodFindFiles);
        connect(optionsDialog, &OptionsDialog::validateOptionsDialog,
            model, &PhotoReducerModel::validateOptionsDialog);
    }

void PhotoReducerController::connectModelOutToOptionDialogIn()
{
    connect(model, &PhotoReducerModel::initOptionsValues, optionsDialog, &OptionsDialog::initOptionsValues);

    connect(model, &PhotoReducerModel::modelErrorSignal, optionsDialog, &OptionsDialog::onModelErrorSignal);
    connect(model, &PhotoReducerModel::modelClearError, optionsDialog, &OptionsDialog::onModelClearError);
}

/*
 * Slots
 */
void PhotoReducerController::mainWindowOptionsButtonPressedCreateOptionsDialog(bool doINeedSignalContents)
{
    optionsDialog = new OptionsDialog(mainWindow);
    optionsDialog->setObjectName("optionsDialog");
    connectModelAndOptionsDialogSignalsToSlots();
    emit optionDialogReadyForInitialization();
    optionsDialog->show();
}

void PhotoReducerController::acceptOptionsDialog()
{
    optionsDialog->accept();
}


