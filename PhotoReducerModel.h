#ifndef PHOTOREDUCERMODEL_H_
#define PHOTOREDUCERMODEL_H_

#include <QObject>
#include <QString>
#include <string>

class PhotoReducerModel : public QObject
{
    Q_OBJECT

public:
    explicit PhotoReducerModel(const char * modelName, QObject *parent = nullptr);
    ~PhotoReducerModel() = default;
    QString getSourceDirectory() { return QString::fromStdString(sourceDirectory); };
    QString getTargetDirectory() { return QString::fromStdString(targetDirectory); };
    QString getRelocDirectory() const { return QString::fromStdString(relocDirectory); };
    QString getPhotoExtension() const { return QString::fromStdString(resizedPostfix); };
    bool getMakeWebSafe() const { return fixFileName; };
    bool getJPGFiles() const { return processJPGFiles; };
    void setOverwriteFiles(bool enable) { overWriteFiles = enable; };
    bool getOverwriteFiles() const { return overWriteFiles; };
    std::size_t getResizedPhotoCount() { return resizedPhotosCount; };
    std::size_t getPhotosToResizeCount() { return photosToResizeCount; };
    bool getMaintainRation() const { return maintainRatio; };
    bool getDisplayResized() const { return displayResized; };
    std::size_t getMaxWidth() const { return maxWidth; };
    std::size_t getMaxHeight() const { return maxHeight; };
    unsigned int getScaleFactor() const { return scaleFactor; };

public slots:
/*
 * File options slots.
 */
    void optionsSourceDirectoryEdited(QString newSrcDir);
    void optionsTargetDirectoryEdited(QString newTargetDir);
    void optionsJPGCheckBoxChanged(bool checked) { processJPGFiles = checked; };
    void optionsPNGCheckBoxChanged(bool checked) { processPNGFiles = checked; };
    void optionsSafeWebNameChanged(bool checked) { fixFileName = checked; };
    void optionsOverWriteFilesChanged(bool checked) { overWriteFiles = checked; };
    void optionsGoodFindFiles(bool optionsGood);
/*
 * Photo options slots.
 */
    

signals:
    void resizedPhotosCountValueChanged(std::size_t newValue);
    void photosToResizeCountValueChanged(std::size_t newValue);
    void sourceDirectoryValueChanged(QString newSrcDir);
    void targetDirectoryValueChanged(QString newTargetDir);


private slots:


private:
    void setResizedPhotoCount(std::size_t newValue);
    void incrementResizedPhotoCount();
    void setPhotosToResizeCount(std::size_t newValue);
    void setSourceDirectory(QString newSrcDir);
    void setTargetDirectory(QString newTargetDir);
    
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


