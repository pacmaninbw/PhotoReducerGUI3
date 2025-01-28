#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

#include "PhotoReducerModel.h"
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

signals:
    void sourceDirectoryLEChanged(QString newSrcDir);
    void targetDirectoryLEChanged(QString newTargetDir);
    void optionsDoneFindPhotoFiles(bool ready);
    void optionsJPGFileTypeCheckBoxChanged(bool checked);
    void optionsPNGFileTypecheckBoxChanged(bool checked);
    void optionsSafeWebNameCheckBoxChanged(bool checked);
    void optionsOverwriteCheckBoxChanged(bool checked);
    void optionsaddExtensionLEChanged(QString newExtension);


private slots:
    void on_sourceDirBrowsePushButton_clicked();
    void on_targetDirectoryLineEdit_textChanged();
    void on_sourceDirectoryLineEdit_textChanged();
    void on_targetDirectoryBrowsePushButton_clicked();
    void on_addExtensionLineEdit_editingFinished();
    void on_optionsButtonBox_accepted();

private:
    void setUpOtionsDialogUI();
    QGroupBox* setUpFileGroupBox();
    QGroupBox* setUpPhotoOptionGroupBox();
    QDialogButtonBox* setrUpOptionsButtonBox();
    QCheckBox* createNamedCheckBox(const QString &boxText, const char* objectName);
    QPushButton* createNamedButton(const QString &buttonText, const char* buttonName);
    QLineEdit* createNamedLineItem(const char* objectName, bool readOnly = false);
    QFormLayout* createNamedFormLayoutWithPolicy(const char *formName);
    QHBoxLayout* layOutSourceDirectory();
    QHBoxLayout* layOutTargetDirectory();

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
};

#endif  // OPTIONSDIALOG_H_
