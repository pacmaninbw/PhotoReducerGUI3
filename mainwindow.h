#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QVariant>
#include <QApplication>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QRect>
#include <QStatusBar>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_resizedPhotos_valueChanged(std::size_t value);
    void on_photosToResizeCount_ValueChanged(std::size_t photosToResize);
    void on_SourceDirectory_Changed(QString srcDir);
    void on_TargetDirectory_Changed(QString targetDir);
    void enableResizePhotosButton() { resizePhotosButton->setEnabled(true); };

signals:
    void mainWindowOptionsButtonPressed(bool doINeedSignalContents);
    void resizeAllPhotos();

private slots:
    void on_optionsPushButton_Clicked();
    void on_resizePhotosButton_Clicked();

private:
    void setUpMainWindowUI();
    void setUpDirectoryDisplays();
    void setUpProgressDisplays();
    QLCDNumber* createAndConfigureLCD(const char* lcdName, const int initValue = 0);
    QProgressBar* createAndConfigureProgressBar(const char* objectName, const int initValue = 0);
    int getLabelWidth(QLabel* lab);
    QLabel* createNamedLabel(const char* labText, const char* labName);
    QLineEdit* createDirectoryDisplayLab(const char* labName);
    QPushButton* CreateNamedButton(const char* buttonText, const char* buttonName);
    QString generateWidthAndHeightStyleString(const int width, const int height);
/*
 * Size and positioning constants.
 */
    const int mainWindowWidth = 800;
    const int mainWindowHeight = 500;
    const int maxOjectWidth = static_cast<int>(mainWindowWidth * 0.8);
    const int lcdHeight = 23;
    const int lcdWidth = 200;
    const int labelHeight = 17;
    const int buttonHeight = 25;
    const int progressBarHeight = 60;
    const int lcdDigitCount = 5;

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
    QLineEdit* sourceDirectoryValue;
    QLabel* targetDirectoryLabel;
    QLineEdit* targetDirectoryValue;
    QPushButton* optionsPushButton;
    QPushButton* resizePhotosButton;
    QMenuBar* menubar;
    QStatusBar* statusbar;
};
#endif // MAINWINDOW_H_

