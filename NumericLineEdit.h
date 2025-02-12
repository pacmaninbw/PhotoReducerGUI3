#ifndef NUMERICLINEDIT_H_
#define NUMERICLINEDIT_H_

#include <QLineEdit>
#include <QFileDialog>
#include <QFocusEvent>
class NumericLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit NumericLineEdit(const char* nleName, QWidget *parent = nullptr)
    : QLineEdit{parent}
    {
        setObjectName(QString::fromUtf8(nleName));
        setStyleSheet(numericLEStyle);
        setMaxLength(maxDigitsNumericLE);
    }

/*
 * Due to how message boxes change the focus when reporting error conditions,
 * how the line edit gains and loses focus is important. Multiple signals
 * for editing were being reported when the user didn't edit.
 */
    void focusInEvent(QFocusEvent *event)
    {
        if (event->reason() == Qt::MouseFocusReason ||
            event->reason() == Qt::TabFocusReason ||
            event->reason() == Qt::BacktabFocusReason ||
            event->reason() == Qt::ShortcutFocusReason)
        {
            sendMySiginal = true;
        }
        QWidget::focusInEvent(event);
    }

    void focusOutEvent(QFocusEvent *event)
    {
        if (event->reason() == Qt::MouseFocusReason ||
            event->reason() == Qt::TabFocusReason ||
            event->reason() == Qt::BacktabFocusReason ||
            event->reason() == Qt::ShortcutFocusReason)
        {
            if (isModified())
            {
                emit userEditComplete(text());
            }
        }
        sendMySiginal = false;
        QWidget::focusInEvent(event);
    }
    
    void highlightError(bool isError)
    {
    	setStyleSheet(isError? numericLEStyleError : numericLEStyle);
    }

signals:
    void userEditComplete(QString);


private:
    bool sendMySiginal = false;
    const int maxDigitsNumericLE = 5;
    const char* numericLEStyle = "width: 60px; background-color: white;";
    const char* numericLEStyleError = "width: 60px; background-color: yellow;";

};

#endif // NUMERICLINEDIT_H_


