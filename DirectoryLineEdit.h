#ifndef DIRECTORYLINEEDIT_H_
#define DIRECTORYLINEEDIT_H_

#include <QLineEdit>
#include <QFileDialog>
#include <QFocusEvent>
class DirectoryLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit DirectoryLineEdit(const char* dleName, const char* title, int leWidth, QWidget *parent = nullptr)
    : QLineEdit{parent}, fileDialogTitle{title}
    {
        setObjectName(QString::fromUtf8(dleName));
        setStyleSheet("width: " + QString::number(leWidth) + "px;");
        setReadOnly(true);
    }

    void focusInEvent(QFocusEvent *event)
    {
        if (event->reason() == Qt::MouseFocusReason ||
            event->reason() == Qt::TabFocusReason)
        {
            QString textToChange = text();
    
            textToChange = QFileDialog::getExistingDirectory(nullptr, fileDialogTitle,
                textToChange, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        
            setText(textToChange);    
        }
        QWidget::focusInEvent(event);
    }
    

private:
    QString fileDialogTitle;
};

#endif // DIRECTORYLINEEDIT_H_


