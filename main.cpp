#include "PhotoReducerController.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication theApp(argc, argv);

    PhotoReducerController controller("TheController");
    controller.createModel();
    controller.creatMainWindow();
    controller.connectModelAndMainWindowSignalsToSlots();
    controller.initMainWindowValuesAndShow();
    controller.connectControllerAndModelSignalsToSlots();
    
    
    return theApp.exec();
}
