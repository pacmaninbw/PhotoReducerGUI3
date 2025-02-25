#include <QApplication>
#include <QString>
#include "SignalRouterController.h"
#include "UserModeStyleSheetGenerator.h"
#include <QGuiApplication>
#include <QPalette>
#include <QStyleHints>

static inline bool isDarkMode()
{
    #if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    const auto scheme = QGuiApplication::styleHints()->colorScheme();
    return scheme == Qt::ColorScheme::Dark;
#else
    const QPalette defaultPalette;
    const auto text = defaultPalette.color(QPalette::WindowText);
    const auto window = defaultPalette.color(QPalette::Window);
    return text.lightness() > window.lightness();
#endif // QT_VERSION
}

int main(int argc, char *argv[])
{
/*
 * This is a workaround for Ubuntu 22.04. The QAplication on Ubuntu 22.04 
 * ignores Wayland which ius providing the dark mode.
 */
    UserModeStyleSheetGenerator styleSheetGenerator(isDarkMode());
    styleSheetGenerator.generateStyleSheet();
    std::string stylesBasedOnUserMode = styleSheetGenerator.getStyleSheet();

    QApplication theApp(argc, argv);

    theApp.setStyleSheet(QString::fromStdString(stylesBasedOnUserMode));

    SignalRouterController routerController("TheController");
    routerController.createModel();
    routerController.connectControllerAndModelSignalsToSlots();
    routerController.creatMainWindow();
    routerController.connectModelAndMainWindowSignalsToSlots();
    routerController.connectControllerAndMainWindowSignalsToSlots();
    routerController.initMainWindowValuesAndShow();
    
    
    return theApp.exec();
}
