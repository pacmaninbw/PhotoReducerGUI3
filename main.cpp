#include "PhotoReducerController.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication theApp(argc, argv);

    PhotoReducerController controller("TheController");
    controller.createModel();
    controller.connectControllerAndModelSignalsToSlots();
    controller.creatMainWindow();
    controller.connectModelAndMainWindowSignalsToSlots();
    controller.initMainWindowValuesAndShow();
    
    
    return theApp.exec();
}
