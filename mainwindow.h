#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QVariant>
#include <QApplication>
#include <QLCDNumber>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QRect>
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
    void on_optionsPushButton_Clicked();

private:
/*
 * Size and positioning constants.
 */
    const int mainWindowWidth = 800;
    const int maxOjectWidth = static_cast<int>(mainWindowWidth * 0.8);
    const int mainWindowHorizontalCenter = static_cast<int>(mainWindowWidth / 2);
    const int mainWindowHeight = 661;
    const int lcdHeight = 23;
    const int labelHeight = 17;
    const int verticleSpace = 20;
    const int buttonHeight = 25;

    void setUpUI();
    void setUpDirectoryDisplays();
    QLCDNumber* createAndConfigureLCD(const char* lcdName);
    QRect calculateHorizontalCenteredObjectRect(int objectWidth, int objectHeigth);
    int getLabelWidth(QLabel* lab);
    QLabel* createCenteredLabel(const char *labText, const char* labName);
    QLabel* createDirectoryDisplayLab(const char* labName);

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
    int currentHeight = 20;
    int itemLineCount = 0;
};
#endif // MAINWINDOW_H_

