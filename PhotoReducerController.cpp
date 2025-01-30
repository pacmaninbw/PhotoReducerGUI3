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
}

void PhotoReducerController::initMainWindowValuesAndShow()
{
    mainWindow->show();
}

void PhotoReducerController::connectModelAndOptionsDialogSignalsToSlots()
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
}


