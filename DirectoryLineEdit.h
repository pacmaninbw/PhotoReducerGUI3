#ifndef DIRECTORYLINEEDIT_H_
#define DIRECTORYLINEEDIT_H_

#include <QLineEdit>

class DirectoryLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit DirectoryLineEdit(const char* dleName, const char* title, int leWidth, QWidget *parent = nullptr);
    void focusInEvent(QFocusEvent *event);

private:
    QString fileDialogTitle;
};

#endif // DIRECTORYLINEEDIT_H_


