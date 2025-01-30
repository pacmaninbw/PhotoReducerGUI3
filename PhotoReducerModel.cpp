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

/*
 * Slots
 */
void PhotoReducerModel::initializeMainWindow()
{
    emit initializeMainWindowSourceDirectory(QString::fromStdString(sourceDirectory));
    emit initializeMainWindowTargetDirectory(QString::fromStdString(targetDirectory));
}

void PhotoReducerModel::optionsSourceDirectoryEdited(QString newSrcDir)
{
    setSourceDirectory(newSrcDir);
}

void PhotoReducerModel::optionsTargetDirectoryEdited(QString newTargetDir)
{
    setTargetDirectory(newTargetDir);
}

void PhotoReducerModel::optionsGoodFindFiles(bool optionsGood)
{
    
}

