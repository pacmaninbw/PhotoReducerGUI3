#ifndef PHOTOREDUCERCONTROLLER_H_
#define PHOTOREDUCERCONTROLLER_H_

#include "mainwindow.h"
#include "PhotoReducerModel.h"
#include "OptionsDialog.h"
#include <QObject>
#include <QString>

/*
 * The purpose of this class is to control the the Photo Reducer Tool. It
 * creates the model and the different views of the model. Most of the signals
 * and slots of the objects will be connected in this class.
 * 
 * Signals to create new views are handled by this class.
 */
class PhotoReducerController: public QObject
{
    Q_OBJECT

public:
    explicit PhotoReducerController(const char * controllerName, QObject *parent = nullptr);
    ~PhotoReducerController() = default;
    void createModel();
    void creatMainWindow();
    void connectModelAndMainWindowSignalsToSlots();
    void connectControllerAndModelSignalsToSlots();
    void connectControllerAndMainWindowSignalsToSlots();
    void initMainWindowValuesAndShow();

public slots:
    void mainWindowOptionsButtonPressedCreateOptionsDialog(bool doINeedSignalContents);

signals:
    void mainWindowReadyForInitialization();


private slots:


private:
    void createOptionsDialog();
    void connectModelAndOptionsDialogSignalsToSlots();

    PhotoReducerModel* model;
    MainWindow* mainWindow;
    OptionsDialog* optionsDialog;
};

#endif // PHOTOREDUCERCONTROLLER_H_


