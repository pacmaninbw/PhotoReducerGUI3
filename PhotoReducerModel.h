#ifndef PHOTOREDUCERMODEL_H_
#define PHOTOREDUCERMODEL_H_

#include <filesystem>
#include <opencv2/opencv.hpp>
#include "OptionErrorCode.h"
#include "OptionsInitStruct.h"
#include <QObject>
#include <QString>
#include <string>
#include <vector>

// std::filesystem can make lines very long.
namespace fs = std::filesystem;

struct PhotoFile
{
    std::string inputName;
    std::string outputName;
};
using PhotoFileList = std::vector<PhotoFile>;

using InputPhotoList = std::vector<fs::path>;

class PhotoReducerModel : public QObject
{
    Q_OBJECT

public:
    explicit PhotoReducerModel(const char * modelName, QObject *parent = nullptr);
    ~PhotoReducerModel() = default;

public slots:
    void initializeMainWindow();
    void initializeOptionsDialog();
    void resizeAllPhotos();
    void validateOptionsDialog();
/*
 * File options slots.
 */
    void optionsSourceDirectoryEdited(QString newSrcDir);
    void optionsTargetDirectoryEdited(QString newTargetDir);
    void optionsJPGCheckBoxChanged(bool checked) { processJPGFiles = checked; };
    void optionsPNGCheckBoxChanged(bool checked) { processPNGFiles = checked; };
    void optionsSafeWebNameChanged(bool checked) { fixFileName = checked; };
    void optionsOverWriteFilesChanged(bool checked)
    {
        overWriteFiles = checked;
        emit highlightOverWriteCB(false);
    };
    void optionsAddExtensionChanged(QString extension);
/*
 * Photo options slots.
 */
    void optionsMaxWidthChanged(QString maxWidthQS);
    void optionsMaxHeightChanged(QString maxHeightQS);
    void optionsScaleFactorChanged(QString scaleFactorQS);
    void optionsMaintainRatioChanged(bool checked) { maintainRatio = checked; };
    void optionsDisplayResizedChanged(bool checked) { displayResized = checked; };
    

signals:
    void initOptionsValues(OptionsInitStruct modelValues);
    void resizedPhotosCountValueChanged(std::size_t newValue);
    void photosToResizeCountValueChanged(std::size_t newValue);
    void sourceDirectoryValueChanged(QString newSrcDir);
    void targetDirectoryValueChanged(QString newTargetDir);
    void initMainWindowSourceDirectory(QString newSrcDir);
    void initMainWindowTargetDirectory(QString newTargetDir);
    void modelErrorSignal(OptionErrorSignalContents &errorSignal);
    void modelClearError(OptionErrorCode clearedError);
    void enableMainWindowResizePhotosButton();
    void highlightOverWriteCB(bool highlight);
    void acceptOptionsDialog();

private slots:


private:
    // UI releated functions
    void setResizedPhotoCount(std::size_t newValue);
    void incrementResizedPhotoCount();
    void setPhotosToResizeCount(std::size_t newValue);
    void setSourceDirectory(QString newSrcDir);
    void setTargetDirectory(QString newTargetDir);
    int qstringToInt(QString possibleNumber);
    void sendErrorSignal(OptionErrorCode code, QString eMessage);
    bool checkMaintainRatioErrors();
    bool clearMaintainRatioErrorIfSet();
    void photoSizeValueError(OptionErrorCode code, QString dimension);
    std::size_t processPhotoDimension(QString value, QString dimension, OptionErrorCode code);

    // Get all the photo files in the source directory the user specified.
    // Apply any name changes to the outout files.
    void buildPhotoInputAndOutputList();
    InputPhotoList findAllPhotos(fs::path& originsDir);
    void addFilesToListByExtension(std::filesystem::path& cwd, const std::string& extLC, 
        const std::string& extUC, InputPhotoList& photoList);
    std::string makeFileNameWebSafe(const std::string& inName);
    std::string makeOutputFileName(const fs::path& inputFile, const fs::path& targetDir);
    PhotoFileList copyInFileNamesToPhotoListAddOutFileNames(
        InputPhotoList& inFileList, fs::path& targetDir);
    
    // Process all the photo files found.
    void resizeAllPhotosInList();
    bool resizeAndSavePhoto(const PhotoFile& photoFile);
    cv::Mat resizeByUserSpecification(cv::Mat& photo);
    bool saveResizedPhoto(cv::Mat& resizedPhoto, const std::string webSafeName);
    cv::Mat resizePhotoByPercentage(cv::Mat& photo, const unsigned int percentage);
    cv::Mat resizePhotoByHeightMaintainGeometry(cv::Mat& photo);
    cv::Mat resizePhotoByWidthMaintainGeometry(cv::Mat& photo);
    cv::Mat resizePhoto(cv::Mat& photo, const std::size_t newWdith, const std::size_t newHeight);

/*
 * Private Variables.
 */
    std::size_t resizedPhotosCount = 0;
    std::size_t photosToResizeCount = 0;
    PhotoFileList photoFileList;
/*
 * File Options.
 */
    bool fixFileName = false;
    bool processJPGFiles = true;
    bool processPNGFiles = false;
    bool overWriteFiles = false;
    std::string sourceDirectory;
    std::string targetDirectory;
    std::string relocDirectory;
    std::string resizedPostfix;
    
/*
 * Photo Options.
 */
    bool displayResized = false;
    bool maintainRatio = false;
    std::size_t maxWidth = 0;
    std::size_t maxHeight = 0;
    unsigned int scaleFactor = 0;
    std::size_t attemptedOverwrites = 0;

    const unsigned int minScaleFactor = 20;
    const unsigned int maxScaleFactor = 90;
};

#endif // PHOTOREDUCERMODEL_H_


