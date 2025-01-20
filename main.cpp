#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication theApp(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    
    return theApp.exec();
}
