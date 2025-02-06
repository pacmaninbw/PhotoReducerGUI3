#ifndef PHOTOREDUCERMODEL_H_
#define PHOTOREDUCERMODEL_H_

#include <filesystem>
#include <opencv2/opencv.hpp>
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
/*
 * File options slots.
 */
    void optionsSourceDirectoryEdited(QString newSrcDir);
    void optionsTargetDirectoryEdited(QString newTargetDir);
    void optionsJPGCheckBoxChanged(bool checked) { processJPGFiles = checked; };
    void optionsPNGCheckBoxChanged(bool checked) { processPNGFiles = checked; };
    void optionsSafeWebNameChanged(bool checked) { fixFileName = checked; };
    void optionsOverWriteFilesChanged(bool checked) { overWriteFiles = checked; };
    void optionsAddExtensionChanged(QString extension);
    void optionsGoodFindFiles(bool optionsGood);
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
    void optionsDialogMaxWidthError(QString eMsg);
    void optionsDialogMaxHeightError(QString eMsg);
    void optionsDialogScaleFactorError(QString eMsg);
    void optionsDialogMaintainRatioError(QString eMsg);
    void optionsDialogAttemptedOverwrite(QString eMsg);
    void clearOptionsWidthError(bool good);
    void clearOptionsHeightError(bool good);
    void clearOptionsScaleFactorError(bool good);

private slots:


private:
    // UI releated functions
    void setResizedPhotoCount(std::size_t newValue);
    void incrementResizedPhotoCount();
    void setPhotosToResizeCount(std::size_t newValue);
    void setSourceDirectory(QString newSrcDir);
    void setTargetDirectory(QString newTargetDir);
    int qstringToInt(QString possibleNumber);

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
    std::size_t resizedPhotosCount;
    std::size_t photosToResizeCount;
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
};

#endif // PHOTOREDUCERMODEL_H_


