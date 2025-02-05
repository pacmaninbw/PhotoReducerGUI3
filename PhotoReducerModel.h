#ifndef PHOTOREDUCERMODEL_H_
#define PHOTOREDUCERMODEL_H_

#include "OptionsInitStruct.h"
#include <QObject>
#include <QString>
#include <string>
#include <vector>

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
    void setResizedPhotoCount(std::size_t newValue);
    void incrementResizedPhotoCount();
    void setPhotosToResizeCount(std::size_t newValue);
    void setSourceDirectory(QString newSrcDir);
    void setTargetDirectory(QString newTargetDir);
    int qstringToInt(QString possibleNumber);
    
    std::size_t resizedPhotosCount;
    std::size_t photosToResizeCount;
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
};

#endif // PHOTOREDUCERMODEL_H_


