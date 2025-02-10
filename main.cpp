#include "SignalRouterController.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication theApp(argc, argv);

    SignalRouterController routerController("TheController");
    routerController.createModel();
    routerController.connectControllerAndModelSignalsToSlots();
    routerController.creatMainWindow();
    routerController.connectModelAndMainWindowSignalsToSlots();
    routerController.connectControllerAndMainWindowSignalsToSlots();
    routerController.initMainWindowValuesAndShow();
    
    
    return theApp.exec();
}
