#include "createNamedQTWidget.h"
#include "OptionsDialog.h"

#include <QVariant>
#include <QAbstractButton>
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    setObjectName(QString::fromUtf8("Options"));

    setUpOtionsDialogUI();

    QObject::connect(optionsButtonBox, &QDialogButtonBox::accepted,
        this, qOverload<>(&QDialog::accept));
        
    QObject::connect(optionsButtonBox, &QDialogButtonBox::rejected,
        this, qOverload<>(&QDialog::reject));

    QMetaObject::connectSlotsByName(this);
}

OptionsDialog::~OptionsDialog()
{
}

void OptionsDialog::on_sourceDirBrowsePushButton_clicked()
{
    QString sourceDir = sourceDirectoryLineEdit->text();

    sourceDir = QFileDialog::getExistingDirectory(nullptr, "Source Directory",
        sourceDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    sourceDirectoryLineEdit->setText(sourceDir);
}

void OptionsDialog::on_targetDirectoryLineEdit_textChanged()
{
    emit targetDirectoryLEChanged(targetDirectoryLineEdit->text());
}

void OptionsDialog::on_sourceDirectoryLineEdit_textChanged()
{
    emit sourceDirectoryLEChanged(sourceDirectoryLineEdit->text());
}

void OptionsDialog::on_targetDirectoryBrowsePushButton_clicked()
{
    QString targetDir = targetDirectoryLineEdit->text();

    targetDir = QFileDialog::getExistingDirectory(nullptr, "Target Directory",
        targetDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    targetDirectoryLineEdit->setText(targetDir);
}

void OptionsDialog::on_addExtensionLineEdit_editingFinished()
{
    emit optionsaddExtensionLEChanged(addExtensionLineEdit->text());
}

void OptionsDialog::on_optionsButtonBox_accepted()
{
    QString temp;
    bool hasNoErrors = true;

    emit optionsDoneFindPhotoFiles(hasNoErrors);

}

void OptionsDialog::setUpOtionsDialogUI()
{
    optionsDialogLayout = new QVBoxLayout;
    optionsDialogLayout->setObjectName("optionsDialogLayout");
    optionsDialogLayout->addWidget(setUpFileGroupBox(), 0, Qt::AlignHCenter);
    optionsDialogLayout->addWidget(setUpPhotoOptionGroupBox(), 0, Qt::AlignHCenter);

    optionsButtonBox = setrUpOptionsButtonBox();
    optionsDialogLayout->addWidget(optionsButtonBox, 0, Qt::AlignHCenter);

    optionsDialogLayout->setSpacing(groupBoxSpacing);

    setLayout(optionsDialogLayout);

    QString dialogTitle = windowTitle();
    dialogTitle += " Options:";

    resize(500, 500);

    setWindowTitle(dialogTitle);
}

QGroupBox* OptionsDialog::setUpPhotoOptionGroupBox()
{
    photoOptionsBox = new QGroupBox("Photo Options", this);

    QFormLayout* photoOptionsLayout =
        createNamedFormLayoutWithPolicy("photoOptionsLayout");

    maintainRatioCheckBox = createNameQTWidgetWithText<QCheckBox>(
        "Maintain Ratio", "maintainRatioCheckBox", this);
    photoOptionsLayout->addRow(maintainRatioCheckBox);

    displayResizedCheckBox = createNameQTWidgetWithText<QCheckBox>(
        "Display Resized Photo", "displayResizedCheckBox", this);
    photoOptionsLayout->addRow(displayResizedCheckBox);

    maxWidthLineEdit = createNamedQTWidget<QLineEdit>("maxWidthLineEdit", this);
    photoOptionsLayout->addRow("Maximum Photo Width", maxWidthLineEdit);

    maxHeightLineEdit = createNamedQTWidget<QLineEdit>("maxHeightLineEdit", this);
    photoOptionsLayout->addRow("Maximum Photo Height", maxHeightLineEdit);

    scaleFactorLineEdit = createNamedQTWidget<QLineEdit>("scaleFactorLineEdit", this);
    photoOptionsLayout->addRow("Scale Factor", scaleFactorLineEdit);

    photoOptionsBox->setLayout(photoOptionsLayout);

    return photoOptionsBox;
}

QDialogButtonBox *OptionsDialog::setrUpOptionsButtonBox()
{
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);

    buttonBox->setObjectName(QString::fromUtf8("optionsButtonBox"));
    buttonBox->setGeometry(QRect(0, 500, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    return buttonBox;
}

QGroupBox* OptionsDialog::setUpFileGroupBox()
{
    QFormLayout* fileAndDirectorylayout = createNamedFormLayoutWithPolicy(
        "fileAndDirectorylayout");

    JPGFileTypeCheckBox = createNameQTWidgetWithText<QCheckBox>(
        "JPG files", "JPGFileTypeCheckBox", this);
    fileAndDirectorylayout->addRow(JPGFileTypeCheckBox);

    PNGFileTypecheckBox = createNameQTWidgetWithText<QCheckBox>(
        "PNG Files", "PNGFileTypecheckBox", this);
    fileAndDirectorylayout->addRow(PNGFileTypecheckBox);

    fixFileNameCheckBox = createNameQTWidgetWithText<QCheckBox>(
        "Safe Web Name", "fixFileNameCheckBox", this);
    fileAndDirectorylayout->addRow(fixFileNameCheckBox);

    overwriteCheckBox = createNameQTWidgetWithText<QCheckBox>(
        "Overwrite Existing Files", "overwriteCheckBox", this);
    fileAndDirectorylayout->addRow(overwriteCheckBox);
    
    fileAndDirectorylayout->addRow("Source Directory", layOutSourceDirectory());
    fileAndDirectorylayout->addRow("Target Directory", layOutTargetDirectory());

    addExtensionLineEdit = createNamedQTWidget<QLineEdit>("addExtensionLineEdit", this);
    fileAndDirectorylayout->addRow("Add Extension", addExtensionLineEdit);

    fileAndDirectoryGroupBox = new QGroupBox("File Type and Directory Options", this);
    fileAndDirectoryGroupBox->setLayout(fileAndDirectorylayout);

    return fileAndDirectoryGroupBox;
}

QFormLayout* OptionsDialog::createNamedFormLayoutWithPolicy(const char *formName)
{
    QFormLayout* newFormLayout = createNamedQTWidget<QFormLayout>(formName);
    newFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    return newFormLayout;
}

QHBoxLayout *OptionsDialog::layOutSourceDirectory()
{
    QHBoxLayout *srcDirLayout = new QHBoxLayout;
    srcDirLayout->setObjectName("srcDirLayout");

    sourceDirectoryLineEdit = createNamedQTWidget<QLineEdit>("sourceDirectoryLineEdit", this);
    sourceDirectoryLineEdit->setReadOnly(true);
    srcDirLayout->addWidget(sourceDirectoryLineEdit);

    sourceDirBrowsePushButton = createNameQTWidgetWithText<QPushButton>(
        "Browse", "sourceDirBrowsePushButton", this);
    srcDirLayout->addWidget(sourceDirBrowsePushButton);

    return srcDirLayout;
}

QHBoxLayout *OptionsDialog::layOutTargetDirectory()
{
    QHBoxLayout *targetDirLayout = new QHBoxLayout();
    targetDirLayout->setObjectName("targetDirLayout");

    targetDirectoryLineEdit = createNamedQTWidget<QLineEdit>("targetDirectoryLineEdit", this);
    targetDirectoryLineEdit->setReadOnly(true);
    targetDirectoryBrowsePushButton = createNameQTWidgetWithText<QPushButton>(
        "Browse", "targetDirectoryBrowsePushButton", this);

    targetDirLayout->addWidget(targetDirectoryLineEdit);
    targetDirLayout->addWidget(targetDirectoryBrowsePushButton);

    return targetDirLayout;
}
