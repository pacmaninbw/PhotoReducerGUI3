#include "DirectoryLineEdit.h"
#include <QFileDialog>

DirectoryLineEdit::DirectoryLineEdit(
    const char *dleName, const char* title, int leWidth, QWidget *parent)
: QLineEdit{parent}, fileDialogTitle{title}
{
    setObjectName(QString::fromUtf8(dleName));
    setStyleSheet("width: " + QString::number(leWidth) + "px;");
    setReadOnly(true);
}

void DirectoryLineEdit::focusInEvent(QFocusEvent *event)
{
    QString textToChange = text();

    textToChange = QFileDialog::getExistingDirectory(nullptr, fileDialogTitle,
        textToChange, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    setText(textToChange);

    QWidget::focusInEvent(event);
}
