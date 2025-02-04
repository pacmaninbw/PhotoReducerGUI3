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
}

void PhotoReducerController::connectControllerAndMainWindowSignalsToSlots()
{
    connect(mainWindow, &MainWindow::mainWindowOptionsButtonPressed, this,
        &PhotoReducerController::mainWindowOptionsButtonPressedCreateOptionsDialog);
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

    connect(optionsDialog, &OptionsDialog::optionsDoneFindPhotoFiles,
        model, &PhotoReducerModel::optionsGoodFindFiles);
}

void PhotoReducerController::connectModelOutToOptionDialogIn()
{
    connect(model, &PhotoReducerModel::initOptionsSourceDirectory, optionsDialog, &OptionsDialog::initSrcDirLE);
    connect(model, &PhotoReducerModel::initOptionsTargetDirectory, optionsDialog, &OptionsDialog::initTargetDirLE);
    connect(model, &PhotoReducerModel::initOptionsJPGFiles, optionsDialog, &OptionsDialog::initJPGFilesCB);
    connect(model, &PhotoReducerModel::initOptionsPNGFiles, optionsDialog, &OptionsDialog::initPNGFilesCB);
    connect(model, &PhotoReducerModel::initOptionsFixFileNames, optionsDialog, &OptionsDialog::initFixFileNameCB);
    connect(model, &PhotoReducerModel::initOptionsAddExtension, optionsDialog, &OptionsDialog::initExtensionLE);
    connect(model, &PhotoReducerModel::initOptionsOverwrite, optionsDialog, &OptionsDialog::initOverwriteCB);

    connect(model, &PhotoReducerModel::initOptionsMaxWidth, optionsDialog, &OptionsDialog::initMaxWidthLE);
    connect(model, &PhotoReducerModel::initOptionsMaxHeight, optionsDialog, &OptionsDialog::initMaxHeightLE);
    connect(model, &PhotoReducerModel::initOptionsScaleFactor, optionsDialog, &OptionsDialog::initScaleFactorLE);
    connect(model, &PhotoReducerModel::initOptionsMaintainRatio, optionsDialog, &OptionsDialog::initMaintainRatioCB);
    connect(model, &PhotoReducerModel::initOptionsDispalyResized, optionsDialog, &OptionsDialog::initDisplayResizedCB);

    connect(model, &PhotoReducerModel::optionsDialogMaxWidthError, optionsDialog, &OptionsDialog::onMaxWidthError);
    connect(model, &PhotoReducerModel::optionsDialogMaxHeightError, optionsDialog, &OptionsDialog::onMaxHeightError);
    connect(model, &PhotoReducerModel::optionsDialogScaleFactorError, optionsDialog, &OptionsDialog::onScaleFactorError);
    connect(model, &PhotoReducerModel::clearOptionsWidthError, optionsDialog, &OptionsDialog::onClearWidthError);
    connect(model, &PhotoReducerModel::clearOptionsHeightError, optionsDialog, &OptionsDialog::onClearHeightError);
    connect(model, &PhotoReducerModel::clearOptionsScaleFactorError, optionsDialog, &OptionsDialog::onClearScaleFactorError);
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


