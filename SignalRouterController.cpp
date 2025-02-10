#include "SignalRouterController.h"
#include <QString>

SignalRouterController::SignalRouterController(const char* objectName, QObject *parent)
    : QObject{parent}
{
    setObjectName(QString::fromUtf8(objectName));

}

void SignalRouterController::createModel()
{
    model = new PhotoReducerModel("TheModel", this);
}

void SignalRouterController::creatMainWindow()
{
    mainWindow = new MainWindow();
    mainWindow->setObjectName("MainWindow");
}

void SignalRouterController::connectModelAndMainWindowSignalsToSlots()
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

void SignalRouterController::connectControllerAndModelSignalsToSlots()
{
    connect(this, &SignalRouterController::mainWindowReadyForInitialization,
        model, &PhotoReducerModel::initializeMainWindow);
    connect(this, &SignalRouterController::optionDialogReadyForInitialization,
        model, &PhotoReducerModel::initializeOptionsDialog);
    connect(this, &SignalRouterController::resizeAllPhotos,
            model, &PhotoReducerModel::resizeAllPhotos);
    connect(model, &PhotoReducerModel::enableMainWindowResizePhotosButton, this,
        &SignalRouterController::enableMainWindowResizePhotosButton);
    connect(model, &PhotoReducerModel::acceptOptionsDialog,
        this, &SignalRouterController::acceptOptionsDialog);
}

void SignalRouterController::connectControllerAndMainWindowSignalsToSlots()
{
    connect(mainWindow, &MainWindow::mainWindowOptionsButtonPressed, this,
        &SignalRouterController::mainWindowOptionsButtonPressedCreateOptionsDialog);
    connect(mainWindow, &MainWindow::resizeAllPhotos, this,
        &SignalRouterController::mainWindowResizePhotosButtonClicked);
    connect(this, &SignalRouterController::enablePhotoResizing, mainWindow,
        &MainWindow::enableResizePhotosButton);
}

void SignalRouterController::initMainWindowValuesAndShow()
{
    emit mainWindowReadyForInitialization();
    mainWindow->show();
}

void SignalRouterController::connectModelAndOptionsDialogSignalsToSlots()
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
void SignalRouterController::connectOptionDialogOutToModelIn()
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

        connect(optionsDialog, &OptionsDialog::validateOptionsDialog,
            model, &PhotoReducerModel::validateOptionsDialog);
    }

void SignalRouterController::connectModelOutToOptionDialogIn()
{
    connect(model, &PhotoReducerModel::initOptionsValues, optionsDialog, &OptionsDialog::initOptionsValues);

    connect(model, &PhotoReducerModel::modelErrorSignal, optionsDialog, &OptionsDialog::onModelErrorSignal);
    connect(model, &PhotoReducerModel::modelClearError, optionsDialog, &OptionsDialog::onModelClearError);
    connect(model, &PhotoReducerModel::highlightOverWriteCB, optionsDialog, &OptionsDialog::highlightOverwriteCB);
}

/*
 * Slots
 */
void SignalRouterController::mainWindowOptionsButtonPressedCreateOptionsDialog(bool doINeedSignalContents)
{
    optionsDialog = new OptionsDialog(mainWindow);
    optionsDialog->setObjectName("optionsDialog");
    connectModelAndOptionsDialogSignalsToSlots();
    emit optionDialogReadyForInitialization();
    optionsDialog->show();
}

void SignalRouterController::acceptOptionsDialog()
{
    optionsDialog->accept();
}


