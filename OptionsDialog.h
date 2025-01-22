#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

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

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

public slots:

signals:

private slots:

private:
    void setUpFileGroupBox();
    void setUpPhotoOptionGroupBox();
    QCheckBox* createAndInit(const QString &boxText, const char* objectName);
    QGroupBox *fileAndDirectoryGroupBox;
    QFormLayout *fileAndDirectorylayout;
    QCheckBox *JPGFileTypeCheckBox;
    QCheckBox *PNGFileTypecheckBox;
    QCheckBox *fixFileNameCheckBox;
    QCheckBox *overwriteCheckBox;
    QLineEdit *sourceDirectoryLineEdit;
    QLineEdit *targetDirectoryLineEdit;
    QLineEdit *addExtensionLineEdit;
    QPushButton *sourceDirBrowsePushButton;
    QPushButton *targetDirectoryBrowsePushButton;
    QGroupBox *photoOptionsBox;
    QFormLayout *photoOptionsLayout;
    QCheckBox *maintainRatioCheckBox;
    QCheckBox *displayResizedCheckBox;
    QLineEdit *maxWidthLineEdit;
    QLineEdit *maxHeightLineEdit;
    QLineEdit *scaleFactorLineEdit;
    QLabel *scaleFactorLabel;
};

#endif  // OPTIONSDIALOG_H_
