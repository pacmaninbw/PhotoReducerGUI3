#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QVariant>
#include <QApplication>
#include <QLCDNumber>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

signals:

private slots:
    void on_optionsPushButtonClicked();


private:
    QWidget *centralwidget;
    QLCDNumber *filesToResizeLcdNumber;
    QLabel *filesToResizeLabel;
    QLabel *resizedPhotosLabel;
    QLCDNumber *resizedPhotosLcdNumber;
    QLabel *sourceDirectoryLabel;
    QLabel *sourceDirectoryValueLabel;
    QLabel *targetDirectoryLabel;
    QLabel *targetDirectoryValueLabel;
    QPushButton *optionsPushButton;
    QPushButton *resizePhotosButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

};
#endif // MAINWINDOW_H_

