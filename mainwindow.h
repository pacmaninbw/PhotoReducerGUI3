#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QVariant>
#include <QApplication>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QRect>
#include <QStatusBar>
#include <QVBoxLayout>
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
    void on_resizePhotosButton_Clicked();

private:
/*
 * Size and positioning constants.
 */
    const int mainWindowWidth = 800;
    const int mainWindowHeight = 500;
    const int maxOjectWidth = static_cast<int>(mainWindowWidth * 0.8);
    const int lcdHeight = 23;
    const int labelHeight = 17;
    const int buttonHeight = 25;
    const int lcdDigitCount = 5;

    void setUpUI();
    void setUpDirectoryDisplays();
    void setUpProgressDisplays();
    QLCDNumber* createAndConfigureLCD(const char* lcdName, const int initValue = 0);
    int getLabelWidth(QLabel* lab);
    QLabel* createNamedLabel(const char* labText, const char* labName);
    QLabel* createDirectoryDisplayLab(const char* labName);
    QPushButton* CreateNamedButton(const char* buttonText, const char* buttonName);

    QWidget* centralwidget;
    QVBoxLayout* mwLayout;
    QHBoxLayout* photoCountHBoxLayout;
    QVBoxLayout* filesToResizeVBoxLayout;
    QLabel* filesToResizeLabel;
    QLCDNumber* filesToResizeLcdNumber;
    QVBoxLayout* resizePhotosVBoxLayout;
    QLabel* resizedPhotosLabel;
    QLCDNumber* resizedPhotosLcdNumber;
    QLabel* sourceDirectoryLabel;
    QProgressBar* resizeProgressBar;
    QLabel* sourceDirectoryValueLabel;
    QLabel* targetDirectoryLabel;
    QLabel* targetDirectoryValueLabel;
    QPushButton* optionsPushButton;
    QPushButton* resizePhotosButton;
    QMenuBar* menubar;
    QStatusBar* statusbar;
};
#endif // MAINWINDOW_H_

