#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

#include "DirectoryLineEdit.h"
#include "NumericLineEdit.h"
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
    void on_targetDirectoryLineEdit_textChanged() { emit targetDirectoryLEChanged(targetDirectoryLineEdit->text()); };
    void on_sourceDirectoryLineEdit_textChanged() { emit sourceDirectoryLEChanged(sourceDirectoryLineEdit->text()); };
    void on_addExtensionLineEdit_editingFinished() { emit optionsaddExtensionLEChanged(addExtensionLineEdit->text()); };
    void on_maxWidthLineEdit_userEditComplete(QString newValue) { emit optionsMaxWidthLEChanged(newValue); };
    void on_maxHeightLineEdit_userEditComplete(QString newValue) { emit optionsMaxHeightLEChanged(newValue); };
    void on_scaleFactorLineEdit_userEditComplete(QString newValue) { emit optionsScaleFactorLEChanged(newValue); };

private:
    void setUpOtionsDialogUI();
    QGroupBox* setUpFileGroupBox();
    void connectFileGroupCheckBoxes();
    void connectPhotoGroupCheckBoxes();
    QGroupBox* setUpPhotoOptionGroupBox();
    QDialogButtonBox* setUpOptionsButtonBox();
    QFormLayout* createNamedFormLayoutWithPolicy(const char *formName);    
    void handelModelError(const OptionErrorSignalContents &eMessage);
    void clearModelError(const OptionErrorCode clearedError);
    void showErrorDisableOKButton(QString error);
    void widgetHighlightError(const OptionErrorCode error, bool highlight);
    void handleMaintainRatioError(bool isError);
    void handleMissingSizeError(bool isError);
    void connectDialogButtons();

    QGroupBox* fileAndDirectoryGroupBox;
    QCheckBox* JPGFileTypeCheckBox;
    QCheckBox* PNGFileTypecheckBox;
    QCheckBox* fixFileNameCheckBox;
    QCheckBox* overwriteCheckBox;
    DirectoryLineEdit* sourceDirectoryLineEdit;
    DirectoryLineEdit* targetDirectoryLineEdit;
    QLineEdit* addExtensionLineEdit;
    QGroupBox* photoOptionsBox;
    QCheckBox* maintainRatioCheckBox;
    QCheckBox* displayResizedCheckBox;
    NumericLineEdit* maxWidthLineEdit;
    NumericLineEdit* maxHeightLineEdit;
    NumericLineEdit* scaleFactorLineEdit;
    QDialogButtonBox* optionsButtonBox;
    QFormLayout* photoOptionsLayout;
    QFormLayout* fileAndDirectorylayout;
    QVBoxLayout* optionsDialogLayout;

    const int groupBoxSpacing = 60;
    const int directorLEWidth = 400;

    OptionErrorCode modelHasErrors = 0;
};

#endif  // OPTIONSDIALOG_H_
