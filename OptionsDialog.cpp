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

#if 0
    updateModelFileOptions();

    if (updateModelPhotoOptions())
    {
        hasErrors = true;
    }

    if (hasErrors)
    {
        showErrorMessages();
    }
#endif
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

    setWindowTitle(dialogTitle);
}

QGroupBox* OptionsDialog::setUpPhotoOptionGroupBox()
{
    photoOptionsBox = new QGroupBox("Photo Options", this);

    QFormLayout* photoOptionsLayout =
        createNamedFormLayoutWithPolicy("photoOptionsLayout");

    maintainRatioCheckBox = createNamedCheckBox(
        "Maintain Ratio", "maintainRatioCheckBox");
    photoOptionsLayout->addRow(maintainRatioCheckBox);

    displayResizedCheckBox = createNamedCheckBox(
        "Display Resized Photo", "displayResizedCheckBox");
    photoOptionsLayout->addRow(displayResizedCheckBox);

    maxWidthLineEdit = createNamedLineItem("maxWidthLineEdit");
    photoOptionsLayout->addRow("Maximum Photo Width", maxWidthLineEdit);

    maxHeightLineEdit = createNamedLineItem("maxHeightLineEdit");
    photoOptionsLayout->addRow("Maximum Photo Height", maxHeightLineEdit);

    scaleFactorLineEdit = createNamedLineItem("scaleFactorLineEdit");
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

    JPGFileTypeCheckBox = createNamedCheckBox("JPG files", "JPGFileTypeCheckBox");
    fileAndDirectorylayout->addRow(JPGFileTypeCheckBox);

    PNGFileTypecheckBox = createNamedCheckBox("PNG Files", "PNGFileTypecheckBox");
    fileAndDirectorylayout->addRow(PNGFileTypecheckBox);

    fixFileNameCheckBox = createNamedCheckBox("Safe Web Name", "fixFileNameCheckBox");
    fileAndDirectorylayout->addRow(fixFileNameCheckBox);

    overwriteCheckBox = createNamedCheckBox("Overwrite Existing Files", "overwriteCheckBox");
    fileAndDirectorylayout->addRow(overwriteCheckBox);
    
    fileAndDirectorylayout->addRow("Source Directory", layOutSourceDirectory());
    fileAndDirectorylayout->addRow("Target Directory", layOutTargetDirectory());

    addExtensionLineEdit = createNamedLineItem("addExtensionLineEdit");
    fileAndDirectorylayout->addRow("Add Extension", addExtensionLineEdit);

    fileAndDirectoryGroupBox = new QGroupBox("File Type and Directory Options", this);
    fileAndDirectoryGroupBox->setLayout(fileAndDirectorylayout);

    return fileAndDirectoryGroupBox;
}

QCheckBox* OptionsDialog::createNamedCheckBox(const QString &boxText, const char* newObjectName)
{
    QCheckBox* newCheckBox = new QCheckBox(boxText, this);
    newCheckBox->setObjectName(QString::fromUtf8(newObjectName));

    return newCheckBox;
}

QPushButton* OptionsDialog::createNamedButton(const QString &buttonText, const char *buttonName)
{
    QPushButton* newbutton = new QPushButton(buttonText, this);
    newbutton->setObjectName(QString::fromUtf8(buttonName));

    return newbutton;
}

QLineEdit* OptionsDialog::createNamedLineItem(const char *objectName, bool readOnly)
{
    QLineEdit* newLineEdit = new QLineEdit(this);
    newLineEdit->setObjectName(QString::fromUtf8(objectName));
    newLineEdit->setReadOnly(readOnly);

    return newLineEdit;
}

QFormLayout* OptionsDialog::createNamedFormLayoutWithPolicy(const char *formName)
{
    QFormLayout* newFormLayout = new QFormLayout;
    newFormLayout->setObjectName(QString::fromUtf8(formName));
    newFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    return newFormLayout;
}

QHBoxLayout *OptionsDialog::layOutSourceDirectory()
{
    QHBoxLayout *srcDirLayout = new QHBoxLayout;
    srcDirLayout->setObjectName("srcDirLayout");

    sourceDirectoryLineEdit = createNamedLineItem("sourceDirectoryLineEdit", true);
    srcDirLayout->addWidget(sourceDirectoryLineEdit);

    sourceDirBrowsePushButton = createNamedButton("Browse", "sourceDirBrowsePushButton");
    srcDirLayout->addWidget(sourceDirBrowsePushButton);

    return srcDirLayout;
}

QHBoxLayout *OptionsDialog::layOutTargetDirectory()
{
    QHBoxLayout *targetDirLayout = new QHBoxLayout();
    targetDirLayout->setObjectName("targetDirLayout");

    targetDirectoryLineEdit = createNamedLineItem("targetDirectoryLineEdit", true);
    targetDirectoryBrowsePushButton = createNamedButton(
        "Browse", "targetDirectoryBrowsePushButton");

    targetDirLayout->addWidget(targetDirectoryLineEdit);
    targetDirLayout->addWidget(targetDirectoryBrowsePushButton);

    return targetDirLayout;
}
