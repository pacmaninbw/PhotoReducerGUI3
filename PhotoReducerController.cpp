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
    connect(model, &PhotoReducerModel::initializeMainWindowSourceDirectory,
        mainWindow, &MainWindow::on_SourceDirectory_Changed);
    connect(model, &PhotoReducerModel::initializeMainWindowTargetDirectory,
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

void PhotoReducerController::connectOptionDialogOutToModelIn()
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

void PhotoReducerController::connectModelOutToOptionDialogIn()
{
    connect(model, &PhotoReducerModel::initializeOptionsDialogSourceDirectory,
        optionsDialog, &OptionsDialog::initializeSourceDirectoryLE);
    connect(model, &PhotoReducerModel::initializeOptionsDialogTargetDirectory,
        optionsDialog, &OptionsDialog::initializeTargetDirectoryLE);
    connect(model, &PhotoReducerModel::initializeOptionsDialogJPGFiles,
        optionsDialog, &OptionsDialog::initializeJPGFilesCB);
    connect(model, &PhotoReducerModel::initializeOptionsDialogPNGFiles,
        optionsDialog, &OptionsDialog::initializePNGFilesCB);
    connect(model, &PhotoReducerModel::initializeOptionsDialogFixFileNames,
        optionsDialog, &OptionsDialog::initializeFixFileNameCB);
    connect(model, &PhotoReducerModel::initializeOptionsDialogOverwrite,
        optionsDialog, &OptionsDialog::initializeOverwriteCB);

    connect(model, &PhotoReducerModel::initializeOptionsDialogMaxWidth,
        optionsDialog, &OptionsDialog::initializeMaxWidthLE);
    connect(model, &PhotoReducerModel::initializeOptionsDialogMaxHeight,
        optionsDialog, &OptionsDialog::initializeMaxHeightLE);
    connect(model, &PhotoReducerModel::initializeOptionsDialogScaleFactor,
        optionsDialog, &OptionsDialog::initializeScaleFactorLE);
    connect(model, &PhotoReducerModel::initializeOptionsDialogMaintainRatio,
        optionsDialog, &OptionsDialog::initializeMaintainRatioCB);
    connect(model, &PhotoReducerModel::initializeOptionsDialogDispalyResized,
        optionsDialog, &OptionsDialog::initializeDisplayResizedCB);
}

/*
 * Signals.
 */

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


