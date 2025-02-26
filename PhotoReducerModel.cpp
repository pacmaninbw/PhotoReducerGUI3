#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iterator>
#include <opencv2/opencv.hpp>
#include "PhotoReducerModel.h"
#include <QDir>
#include <QMessageBox>
#include <QString>
#include <ranges>
#include <string>
#include <vector>

PhotoReducerModel::PhotoReducerModel(const char* modelName, QObject *parent)
    : QObject{parent}, displayResized{false}, maintainRatio{true}
{
    setObjectName(QString::fromUtf8(modelName));

    QString startDir = QDir::homePath();
    setSourceDirectory(startDir);
    setTargetDirectory(startDir);

    setResizedPhotoCount(0);
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
        emit photosToResizeCountValueChanged(photosToResizeCount);
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
    bool ok;

    int output = static_cast<std::size_t>(possibleNumber.toInt(&ok, 10));
    if (!ok)
    {
        output = -1;
    }

    return output;
}

void PhotoReducerModel::setErrorSendErrorSignal(OptionErrorCode code, QString eMessage)
{
    errorMask |= code;

    OptionErrorSignalContents eSignalContents;
    eSignalContents.errorCode = code;
    eSignalContents.errorMessage = eMessage;
    emit modelErrorSignal(eSignalContents);
}

void PhotoReducerModel::clearError(OptionErrorCode code)
{
    if (hasThisError(code))
    {
        errorMask &= ~code;
        emit modelClearError(code);
    }
}

bool PhotoReducerModel::checkMaintainRatioErrors()
{
    if (maintainRatio && maxWidth && maxHeight)
    {
        setErrorSendErrorSignal(maintainRatioError, "To maintain the ratio of the picture, "
            "only one of Max Width or Max Height may be specified!");
        return true;
    }
    else
    {
        clearMaintainRatioErrorIfSet();
    }

    return false;
}

bool PhotoReducerModel::clearMaintainRatioErrorIfSet()
{
    if (hasThisError(maintainRatioError))
    {
        clearError(maintainRatioError);
        return true;
    }

    return false;
}

void PhotoReducerModel::clearMissingSizeErrorIfSet(std::size_t newSize)
{
    if (newSize > 0 && hasThisError(missingSizeError))
    {
        clearError(missingSizeError);
    }
}

void PhotoReducerModel::photoSizeValueError(OptionErrorCode code, QString dimension)
{
    QString errorText = "Max " + dimension + " must be an integer value greater than zero!";
    setErrorSendErrorSignal(code, errorText);
}

std::size_t PhotoReducerModel::processPhotoDimension(QString value, QString dimension, OptionErrorCode code)
{
    int newValue = 0;

    if (value.isEmpty())
    {
        // if value was previously set and this is correcting an error
        clearMaintainRatioErrorIfSet();
    }
    else
    {
        newValue = qstringToInt(value);
        if (newValue > 0)
        {
            if (!checkMaintainRatioErrors())
            {
                clearError(code);
            }
        }
        else
        {
            // if value was not previously set and this is correcting an error
            if (!(newValue == 0 && clearMaintainRatioErrorIfSet()))
            {
                photoSizeValueError(code, dimension);
                newValue = 0;
            }
        }
    }

    return static_cast<std::size_t>(newValue);
}

void PhotoReducerModel::reportAnyAttemptedOverwrites()
{
    if (attemptedOverwrites)
    {
        QString overwriteMsg = QString::number(attemptedOverwrites);
        overwriteMsg += " photos will not be resized because existing files "
            "would be overwritten. To overwrite these files open the options"
            " dialog and click the Overwrite checkbox";
        QMessageBox warningMessageBox;
        warningMessageBox.warning(0,"Warning:", overwriteMsg);
        warningMessageBox.setFixedSize(500,200);
    }
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

    if (!overWriteFiles && attemptedOverwrites)
    {
        emit highlightOverWriteCB(true);
    }
}

void PhotoReducerModel::resizeAllPhotos()
{
    resizeAllPhotosInList();
}

void PhotoReducerModel::validateOptionsDialog()
{
    if (!hasPhotoSize())
    {
        setErrorSendErrorSignal(missingSizeError, "Please provide a new size for the photo!");
    }
    else if (!checkMaintainRatioErrors())
    {
        buildPhotoInputAndOutputList();
        reportAnyAttemptedOverwrites();
        emit acceptOptionsDialog();
    }
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
    maxWidth = processPhotoDimension(maxWidthQS, "Width", maxWidthError);
    checkMaintainRatioErrors();
    clearMissingSizeErrorIfSet(maxWidth);
}

void PhotoReducerModel::optionsMaxHeightChanged(QString maxHeightQS)
{
    maxHeight = processPhotoDimension(maxHeightQS, "Height", maxHeightError);
    checkMaintainRatioErrors();
    clearMissingSizeErrorIfSet(maxHeight);
}

void PhotoReducerModel::optionsScaleFactorChanged(QString scaleFactorQS)
{
    if (!scaleFactorQS.isEmpty())
    {
        int testscaleFactor = qstringToInt(scaleFactorQS);
        if (testscaleFactor >= minScaleFactor && testscaleFactor <= maxScaleFactor)
        {
            scaleFactor = testscaleFactor;
            clearError(scaleFactorError);
            clearMissingSizeErrorIfSet(scaleFactorError);
        }
        else
        {
            QString eText = "Scale Factor must be an integer value between " + 
                QString::number(minScaleFactor) + " and " +
                QString::number(minScaleFactor);
            setErrorSendErrorSignal(scaleFactorError, eText);
        }
    }
}

/*
 * Model Business Logic Implementation
 */

/*
 * The following code originated in the 2 previous versions of the Photo Reduction Tool
 * in the file photofilefinder.[h,cpp]. It has been modified to be a part of the model,
 * which decreases the number of parameters of some functions. Since the tool allows
 * the user to chose the directories to use, some error checking is no longer needed.
 */
void PhotoReducerModel::buildPhotoInputAndOutputList()
{
    fs::path sourceDir = sourceDirectory;
    attemptedOverwrites = 0;    // Clear any previous overwrite attempts

    InputPhotoList inputPhotoList = findAllPhotos(sourceDir);
    
    if (inputPhotoList.size())
    {
        fs::path targetDir = targetDirectory;
        photoFileList = copyInFileNamesToPhotoListAddOutFileNames(inputPhotoList, targetDir);
        setPhotosToResizeCount(photoFileList.size());
        emit enableMainWindowResizePhotosButton();
    }
}

InputPhotoList PhotoReducerModel::findAllPhotos(fs::path &originsDir)
{
    InputPhotoList tempFileList;

    if (processJPGFiles)
    {
        addFilesToListByExtension(originsDir, ".jpg", ".JPG", tempFileList);
    }

    if (processPNGFiles)
    {
        addFilesToListByExtension(originsDir, ".png", ".PNG", tempFileList);
    }

    return tempFileList;
}

void PhotoReducerModel::addFilesToListByExtension(
    std::filesystem::path &cwd, const std::string &extLC,
    const std::string &extUC, InputPhotoList &photoList
)
{
    auto is_match = [extLC, extUC](auto f) {
        return f.path().extension().string() == extLC ||
            f.path().extension().string() == extUC;
    };

    auto files = fs::directory_iterator{ cwd }
        | std::views::filter([](auto& f) { return f.is_regular_file(); })
        | std::views::filter(is_match);

    std::ranges::copy(files, std::back_inserter(photoList));
}

std::string PhotoReducerModel::makeFileNameWebSafe(const std::string &inName)
{
    std::string webSafeName;

    auto toUnderScore = [](unsigned char c) -> unsigned char { return std::isalnum(c)? c : '_'; };

    std::ranges::transform(inName, std::back_inserter(webSafeName), toUnderScore);

    return webSafeName;
}

std::string PhotoReducerModel::makeOutputFileName(const fs::path &inputFile, const fs::path &targetDir)
{
    std::string ext = inputFile.extension().string();
    std::string outputFileName = inputFile.stem().string();

    if (fixFileName)
    {
        outputFileName = makeFileNameWebSafe(outputFileName);
    }

    if (!resizedPostfix.empty())
    {
        outputFileName += "." + resizedPostfix;
    }

    outputFileName += ext;

    fs::path targetFile = targetDir;
    targetFile.append(outputFileName);

    if (fs::exists(targetFile) && !overWriteFiles)
    {
        ++attemptedOverwrites;
        targetFile.clear();
    }

    return targetFile.string();
}

PhotoFileList PhotoReducerModel::copyInFileNamesToPhotoListAddOutFileNames(
    InputPhotoList &inFileList, fs::path &targetDir)
{
    PhotoFileList photoFileList;

    for (auto const& file: inFileList)
    {
        PhotoFile currentPhoto;
        currentPhoto.inputName = file.string();
        currentPhoto.outputName = makeOutputFileName(file, targetDir);
        photoFileList.push_back(currentPhoto);
    }

    return photoFileList;
}

/*
 * Resize all photos in the list of photo files.
 *
 * The following code originated in the 2 previous versions of the Photo Reduction Tool
 * in the file PhotoResizer.[h,cpp]. It has been modified to be a part of the model,
 * which decreases the number of parameters of some functions.
 */
void PhotoReducerModel::resizeAllPhotosInList()
{
    for (auto photo: photoFileList)
    {
        if (resizeAndSavePhoto(photo))
        {
            incrementResizedPhotoCount();
        }
    }
}

bool PhotoReducerModel::resizeAndSavePhoto(const PhotoFile &photoFile)
{
    // Possibly file already exists and user did not specify --overwrite
    if (photoFile.outputName.empty())
    {
        return false;
    }

    cv::Mat photo = cv::imread(photoFile.inputName);
    if (photo.empty()) {
        QString eMsg = "Could not read photo ";
        eMsg += QString::fromStdString(photoFile.inputName);
        QMessageBox errorMessageBox;
        errorMessageBox.critical(0,"Error:", eMsg);
        errorMessageBox.setFixedSize(500,300);

        return false;
    }

    cv::Mat resized = resizeByUserSpecification(photo);

    if (displayResized)
    {
        cv::imshow("Resized Photo", resized);
        cv::waitKey(0);
    }

    return saveResizedPhoto(resized, photoFile.outputName);
}

cv::Mat PhotoReducerModel::resizeByUserSpecification(cv::Mat &photo)
{
    if (maxWidth > 0 && maxHeight > 0)
    {
        return resizePhoto(photo, maxWidth, maxHeight);
    }

    if (scaleFactor > 0)
    {
        return resizePhotoByPercentage(photo, scaleFactor);
    }

    if (maintainRatio)
    {
        if (maxWidth > 0)
        {
            return resizePhotoByWidthMaintainGeometry(photo);
        }
        if (maxHeight > 0)
        {
            return resizePhotoByHeightMaintainGeometry(photo);
        }
        return photo;
    }
    else
    {
        if (maxWidth > 0 && maxHeight == 0)
        {
            return resizePhotoByWidthMaintainGeometry(photo);
        }
        if (maxHeight > 0 && maxWidth == 0)
        {
            return resizePhotoByHeightMaintainGeometry(photo);
        }
    }

    return photo;
}

bool PhotoReducerModel::saveResizedPhoto(cv::Mat &resizedPhoto, const std::string webSafeName)
{
    bool saved = cv::imwrite(webSafeName, resizedPhoto);

    if (!saved) {
        QString eMsg = "Could not write photo ";
        eMsg += QString::fromStdString(webSafeName);
        QMessageBox errorMessageBox;
        errorMessageBox.critical(0,"Error:", eMsg);
        errorMessageBox.setFixedSize(500,300);

    }

    // Prevent memory leak.
    resizedPhoto.release();

    return saved;
}

cv::Mat PhotoReducerModel::resizePhotoByPercentage(cv::Mat &photo, const unsigned int percentage)
{
    double percentMult = static_cast<double>(percentage)/100.0;

// Retain the current photo geometry.
    std::size_t newWidth = static_cast<int>(photo.cols * percentMult);
    std::size_t newHeight = static_cast<int>(photo.rows * percentMult);

    return resizePhoto(photo, newWidth, newHeight);
}

cv::Mat PhotoReducerModel::resizePhotoByHeightMaintainGeometry(cv::Mat &photo)
{
    if (static_cast<std::size_t>(photo.rows)  <= maxHeight)
    {
        return photo;
    }

    double ratio = static_cast<double>(maxHeight) / static_cast<double>(photo.rows);
    std::size_t newWidth = static_cast<int>(photo.cols * ratio);

    return resizePhoto(photo, newWidth, maxHeight);
}

cv::Mat PhotoReducerModel::resizePhotoByWidthMaintainGeometry(cv::Mat &photo)
{
    if (static_cast<std::size_t>(photo.cols)  <= maxWidth)
    {
        return photo;
    }

    double ratio = static_cast<double>(maxWidth) / static_cast<double>(photo.cols);
    std::size_t newHeight = static_cast<int>(photo.rows * ratio);

    return resizePhoto(photo, maxWidth, newHeight);
}

cv::Mat PhotoReducerModel::resizePhoto(cv::Mat &photo, const std::size_t newWdith, const std::size_t newHeight)
{
    cv::Size newSize(newWdith, newHeight);

    cv::Mat resizedPhoto;

    cv::resize(photo, resizedPhoto, newSize, 0, 0, cv::INTER_AREA);

    // Prevent memory leak
    photo.release();

    return resizedPhoto;
}
