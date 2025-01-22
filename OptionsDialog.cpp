#include "OptionsDialog.h"
#include <QVariant>
#include <QAbstractButton>
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
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

    setUpFileGroupBox();

}

OptionsDialog::~OptionsDialog()
{

}

void OptionsDialog::setUpPhotoOptionGroupBox()
{
}

QCheckBox *OptionsDialog::createAndInit(const QString &boxText, const char* newObjectName)
{
    QCheckBox* newCheckBox = new QCheckBox(boxText, this);
    newCheckBox->setObjectName(QString::fromUtf8(newObjectName));

    return newCheckBox;
}

void OptionsDialog::setUpFileGroupBox()
{
    JPGFileTypeCheckBox = createAndInit("JPG files", "JPGFileTypeCheckBox");
    PNGFileTypecheckBox = createAndInit("PNG Files", "PNGFileTypecheckBox");
    fixFileNameCheckBox = createAndInit("Safe Web Name", "fixFileNameCheckBox");
    overwriteCheckBox = createAndInit("Overwrite Existing Files", "overwriteCheckBox");
    
    sourceDirectoryLineEdit = new QLineEdit(this);
    sourceDirBrowsePushButton = new QPushButton("Browse Source Directory", this);
//    QHBoxLayout *srcDirLayout = new QHBoxLayout(this);
//    srcDirLayout->addWidget(sourceDirectoryLineEdit);
//    srcDirLayout->addWidget(sourceDirBrowsePushButton);
    targetDirectoryLineEdit = new QLineEdit(this);
    targetDirectoryBrowsePushButton = new QPushButton("Browse Target Directory", this);
//    QHBoxLayout *targetDirLayout = new QHBoxLayout(this);
//    targetDirLayout->addWidget(targetDirectoryLineEdit);
//    targetDirLayout->addWidget(targetDirectoryBrowsePushButton);
    addExtensionLineEdit = new QLineEdit(this);

    fileAndDirectorylayout = new QFormLayout(this);
    fileAndDirectorylayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    fileAndDirectorylayout->addRow(JPGFileTypeCheckBox);
    fileAndDirectorylayout->addRow(PNGFileTypecheckBox);
    fileAndDirectorylayout->addRow(fixFileNameCheckBox);
    fileAndDirectorylayout->addRow(overwriteCheckBox);
    fileAndDirectorylayout->addRow("Source Directory", sourceDirectoryLineEdit);
    fileAndDirectorylayout->addRow("Target Directory", targetDirectoryLineEdit);
    fileAndDirectorylayout->addRow("Add Extension", addExtensionLineEdit);
    fileAndDirectoryGroupBox = new QGroupBox("File Type and Directory Options", this);
    fileAndDirectoryGroupBox->setLayout(fileAndDirectorylayout);
}

