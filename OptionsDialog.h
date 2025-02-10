#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

#include "OptionErrorCode.h"
#include "OptionsInitStruct.h"
#include <QVariant>
#include <QAbstractButton>
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget* parent = nullptr);
    ~OptionsDialog();

public slots:
    void initOptionsValues(OptionsInitStruct modelValues);
    void onModelErrorSignal(OptionErrorSignalContents eMessage) { handelModelError(eMessage); };
    void onModelClearError(OptionErrorCode clearedError) { clearModelError(clearedError); };
    void highlightOverwriteCB(bool highlight)
    {
        overwriteCheckBox->setStyleSheet(
            highlight? "background-color: yellow;" : "background-color: none;");
    }

signals:
    void sourceDirectoryLEChanged(QString newSrcDir);
    void targetDirectoryLEChanged(QString newTargetDir);
    void optionsDoneFindPhotoFiles(bool ready);
    void optionsJPGFileTypeCheckBoxChanged(bool checked);
    void optionsPNGFileTypecheckBoxChanged(bool checked);
    void optionsSafeWebNameCheckBoxChanged(bool checked);
    void optionsOverwriteCheckBoxChanged(bool checked);
    void optionsaddExtensionLEChanged(QString newExtension);
    void optionsMaintainRatioCBChanged(bool checked);
    void optionsDisplayResizedCBChanged(bool checked);
    void optionsMaxWidthLEChanged(QString maxWidthQS);
    void optionsMaxHeightLEChanged(QString maxHeightQS);
    void optionsScaleFactorLEChanged(QString scaleFactorQS);
    void validateOptionsDialog();

private slots:
    void onAccept();
    void on_sourceDirBrowsePushButton_clicked() { dirBrowsePushButtonClicked(sourceDirectoryLineEdit, "Source"); };
    void on_targetDirectoryLineEdit_textChanged() { emit targetDirectoryLEChanged(targetDirectoryLineEdit->text()); };
    void on_sourceDirectoryLineEdit_textChanged() { emit sourceDirectoryLEChanged(sourceDirectoryLineEdit->text()); };
    void on_targetDirectoryBrowsePushButton_clicked() {dirBrowsePushButtonClicked(targetDirectoryLineEdit, "Target"); };
    void on_addExtensionLineEdit_editingFinished() { emit optionsaddExtensionLEChanged(addExtensionLineEdit->text()); };
    void on_maxWidthLineEdit_editingFinished() { emit optionsMaxWidthLEChanged(maxWidthLineEdit->text()); };
    void on_maxHeightLineEdit_editingFinished() { emit optionsMaxHeightLEChanged(maxHeightLineEdit->text()); };
    void on_scaleFactorLineEdit_editingFinished() { emit optionsScaleFactorLEChanged(scaleFactorLineEdit->text()); };

private:
    void setUpOtionsDialogUI();
    QGroupBox* setUpFileGroupBox();
    void connectFileGroupCheckBoxes();
    void connectPhotoGroupCheckBoxes();
    QGroupBox* setUpPhotoOptionGroupBox();
    QDialogButtonBox* setrUpOptionsButtonBox();
    QFormLayout* createNamedFormLayoutWithPolicy(const char *formName);    
    QHBoxLayout* layOutSourceDirectory();
    QHBoxLayout* layOutTargetDirectory();
    void handelModelError(const OptionErrorSignalContents &eMessage);
    void clearModelError(const OptionErrorCode clearedError);
    void showErrorDisableOKButton(QString error);
    void widgetHighlightError(const OptionErrorCode error, bool highlight);
    void handleMaintainRatioError(bool isError);
    void handleMissingSizeError(bool isError);
    void connectDialogButtons();
    void dirBrowsePushButtonClicked(QLineEdit* dirLineEdit, const char* dirText);
    QLineEdit* createNumericLineEdit(const char* objectName);
    QLineEdit* createDirectoryLineEdit(const char* objectName);

    QGroupBox* fileAndDirectoryGroupBox;
    QCheckBox* JPGFileTypeCheckBox;
    QCheckBox* PNGFileTypecheckBox;
    QCheckBox* fixFileNameCheckBox;
    QCheckBox* overwriteCheckBox;
    QLineEdit* sourceDirectoryLineEdit;
    QLineEdit* targetDirectoryLineEdit;
    QLineEdit* addExtensionLineEdit;
    QPushButton* sourceDirBrowsePushButton;
    QPushButton* targetDirectoryBrowsePushButton;
    QGroupBox* photoOptionsBox;
    QCheckBox* maintainRatioCheckBox;
    QCheckBox* displayResizedCheckBox;
    QLineEdit* maxWidthLineEdit;
    QLineEdit* maxHeightLineEdit;
    QLineEdit* scaleFactorLineEdit;
    QDialogButtonBox* optionsButtonBox;
    QFormLayout* photoOptionsLayout;
    QFormLayout* fileAndDirectorylayout;
    QVBoxLayout* optionsDialogLayout;

    const int groupBoxSpacing = 60;
    const int maxDigitsNumericLE = 5;
    const char* numericLEStyle = "width: 60px; background-color: white;";
    const char* numericLEStyleError = "width: 60px; background-color: yellow;";
    const char* directoryLEStyle = "width: 400px;";

    OptionErrorCode modelHasErrors = 0;
};

#endif  // OPTIONSDIALOG_H_
