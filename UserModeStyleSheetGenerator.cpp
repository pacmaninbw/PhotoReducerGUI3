#include <QGuiApplication>
#include <QPalette>
#include <QStyleHints>
#include <string>
#include <vector>
#include "UserModeStyleSheetGenerator.h"

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

UserModeStyleSheetGenerator::UserModeStyleSheetGenerator()
{
    commonInitializer(isDarkMode());
}

/*
 * This is a workaround for Ubuntu 22.04. The QAplication on Ubuntu 22.04 
 * ignores Wayland which ius providing the dark mode.
 */
UserModeStyleSheetGenerator::UserModeStyleSheetGenerator(bool usingDarkMode)
{
    commonInitializer(usingDarkMode);
}

static std::vector<std::string> widgetsToStyle =
{
    "QLineEdit",
    "QPushButton"
};

void UserModeStyleSheetGenerator::generateStyleSheet()
{
    for (auto widget: widgetsToStyle)
    {
        sStyleSheet += getWidgetStyle(widget);
    }
}

std::string UserModeStyleSheetGenerator::getStyleSheet()
{
    return sStyleSheet;
}

std::string UserModeStyleSheetGenerator::getWidgetStyle(std::string theWidget)
{
    std::string styledWidget(theWidget);

    styledWidget += " {" + basicStyle + "}\n";

    return styledWidget;
}

void UserModeStyleSheetGenerator::commonInitializer(bool usingDarkMode)
{
    if (usingDarkMode)
    {
        textColor = light;
        backgroundColor = dark;
    }
    else
    {
        textColor = dark;
        backgroundColor = light;
    }

    basicStyle = "background-color: " + backgroundColor + ";" + "color: " + textColor + ";";
    errorModeStyle = "background-color: yellow; color: " + dark + ";";
}
