#include "mainwindow.h"
#include "PhotoReducerModel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication theApp(argc, argv);

    PhotoReducerModel theModel;

    MainWindow mainWindow;
    mainWindow.show();
    
    return theApp.exec();
}
