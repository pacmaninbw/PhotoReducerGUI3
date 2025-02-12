#include "createNamedQTWidget.h"
#include "DirectoryLineEdit.h"
#include "NumericLineEdit.h"
#include "OptionsDialog.h"
#include <QVariant>
#include <QAbstractButton>
#include <QApplication>
#include <QCheckBox>
#include <QCloseEvent>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
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

    maxWidthLineEdit = new NumericLineEdit("maxWidthLineEdit");
    photoOptionsLayout->addRow("Maximum Photo Width", maxWidthLineEdit);

    maxHeightLineEdit = new NumericLineEdit("maxHeightLineEdit");
    photoOptionsLayout->addRow("Maximum Photo Height", maxHeightLineEdit);

    scaleFactorLineEdit = new NumericLineEdit("scaleFactorLineEdit");
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
    
    sourceDirectoryLineEdit = new DirectoryLineEdit("sourceDirectoryLineEdit", "Source Directory", directorLEWidth, this);
    fileAndDirectorylayout->addRow("Source Directory", sourceDirectoryLineEdit);

    targetDirectoryLineEdit = new DirectoryLineEdit("targetDirectoryLineEdit", "Target Directory", directorLEWidth, this);
    fileAndDirectorylayout->addRow("Target Directory", targetDirectoryLineEdit);

    addExtensionLineEdit = createNamedQTWidget<QLineEdit>("addExtensionLineEdit", this);
    addExtensionLineEdit->setStyleSheet("width: 200px;");
    addExtensionLineEdit->setMaxLength(20);
    fileAndDirectorylayout->addRow("Add Extension", addExtensionLineEdit);

    fileAndDirectoryGroupBox = new QGroupBox("File Type and Directory Options", this);
    fileAndDirectoryGroupBox->setLayout(fileAndDirectorylayout);

    return fileAndDirectoryGroupBox;
}

void  OptionsDialog::connectDialogButtons()
{
    QObject::connect(optionsButtonBox, &QDialogButtonBox::accepted,
        this, &OptionsDialog::onAccept);
        
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

void OptionsDialog::handelModelError(const OptionErrorSignalContents &eMessage)
{
    OptionErrorCode eCode = eMessage.errorCode;
    modelHasErrors |= eCode;
    widgetHighlightError(eCode, true);
    showErrorDisableOKButton(eMessage.errorMessage);
}

void OptionsDialog::clearModelError(const OptionErrorCode clearedError)
{
    modelHasErrors &= ~clearedError;
    widgetHighlightError(clearedError, false);    
    if (!modelHasErrors)
    {
        optionsButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void OptionsDialog::showErrorDisableOKButton(QString error)
{
    QMessageBox errorMessageBox;
    errorMessageBox.critical(0,"Error:", error);
    errorMessageBox.setFixedSize(500,200);

    optionsButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void OptionsDialog::widgetHighlightError(const OptionErrorCode error, bool highlight)
{
    NumericLineEdit* widgetToChange = nullptr;

    switch (error)
    {
        default: 
            showErrorDisableOKButton("Unknown error code!");
            return;
        case maintainRatioError:
            handleMaintainRatioError(highlight);
            return;
        case missingSizeError:
            handleMissingSizeError(highlight);
            return;
        case maxWidthError:
            widgetToChange = maxWidthLineEdit;
            break;
        case maxHeightError:
            widgetToChange = maxHeightLineEdit;
            break;
        case scaleFactorError:
            widgetToChange = scaleFactorLineEdit;
            break;
    }

    if (widgetToChange)
    {
        widgetToChange->highlightError(highlight);
    }
}

/*
 * Multiple widgets need to be changed.
 * The maintain ratio error indicates that both width and height have
 * been specified which can cause ratio errors.
 */
void OptionsDialog::handleMaintainRatioError(bool isError)
{
    maintainRatioCheckBox->setStyleSheet(isError? "background-color: yellow;" :
        "background-color: none;");
    maxWidthLineEdit->highlightError(isError);
    maxHeightLineEdit->highlightError(isError);
}

/*
 * Multiple widgets need to be changed.
 */
void OptionsDialog::handleMissingSizeError(bool isError)
{
    maxWidthLineEdit->highlightError(isError);
    maxHeightLineEdit->highlightError(isError);
    scaleFactorLineEdit->highlightError(isError);
}

/*
 * Slots for the widgets.
 */
void OptionsDialog::onAccept()
{
    if (modelHasErrors)
    {
        QMessageBox::warning(this, "Errors", "Please correct the errors highlighted in yellow before closing.");
    }
    else
    {
        emit validateOptionsDialog();
    }
}

void OptionsDialog::initOptionsValues(OptionsInitStruct modelValues)
{
    sourceDirectoryLineEdit->setText(QString::fromStdString(modelValues.sourceDirectory));
    targetDirectoryLineEdit->setText(QString::fromStdString(modelValues.targetDirectory));
    JPGFileTypeCheckBox->setChecked(modelValues.processJPGFiles);
    PNGFileTypecheckBox->setChecked(modelValues.processPNGFiles);
    fixFileNameCheckBox->setChecked(modelValues.fixFileName);
    overwriteCheckBox->setChecked(modelValues.overWriteFiles);
    addExtensionLineEdit->setText(QString::fromStdString(modelValues.resizedPostfix));

    maintainRatioCheckBox->setChecked(modelValues.maintainRatio);
    displayResizedCheckBox->setChecked(modelValues.displayResized);
    maxWidthLineEdit->setText(((modelValues.maxWidth > 0)?
        QString::number(modelValues.maxWidth) : QString("")));
    maxHeightLineEdit->setText(((modelValues.maxWidth > 0)?
        QString::number(modelValues.maxHeight) : QString("")));
    scaleFactorLineEdit->setText(((modelValues.maxWidth > 0)?
        QString::number(modelValues.scaleFactor) : QString("")));
}

