#include "PhotoReducerModel.h"
#include <QDir>
#include <QString>

PhotoReducerModel::PhotoReducerModel(const char* modelName, QObject *parent)
    : QObject{parent}, displayResized{false}, maintainRatio{true}
{
    setObjectName(QString::fromUtf8(modelName));

    QString startDir = QDir::homePath();
    setSourceDirectory(startDir);
    setTargetDirectory(startDir);

    setPhotosToResizeCount(0);
    setPhotosToResizeCount(0);
}

void PhotoReducerModel::setResizedPhotoCount(std::size_t newValue)
{
    if (newValue != resizedPhotosCount) {
        resizedPhotosCount = newValue;
        emit resizedPhotosCountValueChanged(resizedPhotosCount);
    }
}

void PhotoReducerModel::incrementResizedPhotoCount()
{
    ++resizedPhotosCount;
    emit resizedPhotosCountValueChanged(resizedPhotosCount);
}

void PhotoReducerModel::optionsAddExtensionChanged(QString extension)
{
    resizedPostfix = extension.toStdString();
}

void PhotoReducerModel::setPhotosToResizeCount(std::size_t newValue)
{
    if (newValue != photosToResizeCount) {
        photosToResizeCount = newValue;
        emit resizedPhotosCountValueChanged(photosToResizeCount);
    }
}

void PhotoReducerModel::setSourceDirectory(QString newSrcDir)
{
    std::string newDir = newSrcDir.toStdString();
    if (newDir != sourceDirectory)
    {
        sourceDirectory = newDir;
        emit sourceDirectoryValueChanged(newSrcDir);
    }
}

void PhotoReducerModel::setTargetDirectory(QString newTargetDir)
{
    std::string newDir = newTargetDir.toStdString();
    if (newDir != targetDirectory)
    {
        targetDirectory = newDir;
        emit targetDirectoryValueChanged(newTargetDir);
    }
}

int PhotoReducerModel::qstringToInt(QString possibleNumber)
{
    int output = 0;
    bool ok;

    output = static_cast<std::size_t>(possibleNumber.toInt(&ok, 10));
    if (!ok)
    {
        output = -1;
    }

    return output;
}

/*
 * Slots
 */
void PhotoReducerModel::initializeMainWindow()
{
    emit initMainWindowSourceDirectory(QString::fromStdString(sourceDirectory));
    emit initMainWindowTargetDirectory(QString::fromStdString(targetDirectory));
}

void PhotoReducerModel::initializeOptionsDialog()
{
    OptionsInitStruct modelValues;
    modelValues.sourceDirectory = sourceDirectory;
    modelValues.targetDirectory = targetDirectory;
    modelValues.processJPGFiles = processJPGFiles;
    modelValues.processPNGFiles = processPNGFiles;
    modelValues.fixFileName = fixFileName;
    modelValues.overWriteFiles = overWriteFiles;
    modelValues.resizedPostfix = resizedPostfix;

    modelValues.maintainRatio = maintainRatio;
    modelValues.displayResized = displayResized;
    modelValues.maxWidth = maxWidth;
    modelValues.maxHeight = maxHeight;
    modelValues.scaleFactor = scaleFactor;

    emit initOptionsValues(modelValues);
}

void PhotoReducerModel::optionsSourceDirectoryEdited(QString newSrcDir)
{
    setSourceDirectory(newSrcDir);
}

void PhotoReducerModel::optionsTargetDirectoryEdited(QString newTargetDir)
{
    setTargetDirectory(newTargetDir);
}

void PhotoReducerModel::optionsMaxWidthChanged(QString maxWidthQS)
{
    if (!maxWidthQS.isEmpty())
    {
        int width = qstringToInt(maxWidthQS);
        if (width > 0)
        {
            maxWidth = width;
            emit clearOptionsWidthError(true);
        }
        else
        {
            emit optionsDialogMaxWidthError(
                "Max Height must be an integer value greater than zero!");
        }
    }
}

void PhotoReducerModel::optionsMaxHeightChanged(QString maxHeightQS)
{
    if (!maxHeightQS.isEmpty())
    {
        int height = qstringToInt(maxHeightQS);
        if (height > 0)
        {
            maxHeight = height;
            emit clearOptionsHeightError(true);
        }
        else
        {
            emit optionsDialogMaxHeightError(
                "Max Width must be an integer value greater than zero!");
        }
    }
}

void PhotoReducerModel::optionsScaleFactorChanged(QString scaleFactorQS)
{
    if (!scaleFactorQS.isEmpty())
    {
        int testscaleFactor = qstringToInt(scaleFactorQS);
        if (testscaleFactor > 20 && testscaleFactor < 90)
        {
            scaleFactor = testscaleFactor;
            emit clearOptionsScaleFactorError(true);
        }
        else
        {
            emit optionsDialogScaleFactorError("Scale Factor must be an integer value"
                " greater than 20 and less than 90!");
        }
    }
}

void PhotoReducerModel::optionsGoodFindFiles(bool optionsGood)
{
    
}

