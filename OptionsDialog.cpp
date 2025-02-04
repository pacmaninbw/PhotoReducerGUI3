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
#include <QMessageBox>
#include <QPushButton>
#include <QString>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    setObjectName(QString::fromUtf8("Options"));

    setUpOtionsDialogUI();

/*
 * QMetaObject::connectSlotsByName() does not connect Dialog Button Box buttons
 * or checkboxes. This makes it necessary to connect the buttons and checkboxes
 * explicitly.
 */
    connectDialogButtons();
    connectFileGroupCheckBoxes();
    connectPhotoGroupCheckBoxes();

    QMetaObject::connectSlotsByName(this);
}

OptionsDialog::~OptionsDialog()
{
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

void  OptionsDialog::connectDialogButtons()
{
    QObject::connect(optionsButtonBox, &QDialogButtonBox::accepted,
        this, qOverload<>(&QDialog::accept));
        
    QObject::connect(optionsButtonBox, &QDialogButtonBox::rejected,
        this, qOverload<>(&QDialog::reject));
}

/*
 * Please pardon the repetition of code in the following 2 functions. I am still
 * researching how to pass a signal that needs to be emitted into a function.
 */
void OptionsDialog::connectPhotoGroupCheckBoxes()
{
    connect(maintainRatioCheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsMaintainRatioCBChanged(maintainRatioCheckBox->isChecked());
        }
    );
    connect(displayResizedCheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsDisplayResizedCBChanged(displayResizedCheckBox->isChecked());
        }
    );
}

void OptionsDialog::connectFileGroupCheckBoxes()
{
    connect(JPGFileTypeCheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsJPGFileTypeCheckBoxChanged(JPGFileTypeCheckBox->isChecked());
        }
    );
    connect(PNGFileTypecheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsPNGFileTypecheckBoxChanged(PNGFileTypecheckBox->isChecked());
        }
    );
    connect(fixFileNameCheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsSafeWebNameCheckBoxChanged(fixFileNameCheckBox->isChecked());
        }
    );
    connect(overwriteCheckBox, &QCheckBox::toggled, [this]()
        {
            emit optionsOverwriteCheckBoxChanged(overwriteCheckBox->isChecked());
        }
    );
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

void OptionsDialog::handelLineEditError(QString eMsg, QLineEdit *badLineEdit)
{
    QMessageBox errorMessageBox;
    errorMessageBox.critical(0,"Error:", eMsg);
    errorMessageBox.setFixedSize(500,200);
    badLineEdit->setStyleSheet("background-color: yellow;");
    optionsButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void OptionsDialog::clearErrorLineEdit(QLineEdit *correctedLineEdit)
{
    correctedLineEdit->setStyleSheet("background-color: white;");
}

void OptionsDialog::dirBrowsePushButtonClicked(QLineEdit* dirLineEdit, const char* dirText)
{
    QString textToChange = dirLineEdit->text();
    QString fileDialogTitle = dirText;
    fileDialogTitle += " Directory";

    textToChange = QFileDialog::getExistingDirectory(nullptr, fileDialogTitle,
        textToChange, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    dirLineEdit->setText(textToChange);
}

/*
 * Slots for the widgets.
 */
void OptionsDialog::on_optionsButtonBox_accepted()
{
    QString temp;
    bool hasNoErrors = true;

    emit optionsDoneFindPhotoFiles(hasNoErrors);

}


