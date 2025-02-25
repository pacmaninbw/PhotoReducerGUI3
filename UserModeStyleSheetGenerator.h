#ifndef USERMODESTYLESHEETGENERATOR_H_
#define USERMODESTYLESHEETGENERATOR_H_

#include <string>

class UserModeStyleSheetGenerator
{
public:
    UserModeStyleSheetGenerator();
    UserModeStyleSheetGenerator(bool usingDarkMode);
    void generateStyleSheet();
    std::string getStyleSheet();
    std::string getErrorStyle() const { return errorModeStyle; };
    
private:
    std::string getWidgetStyle(std::string theWidget);
    void commonInitializer(bool usingDarkMode);

    std::string sStyleSheet;
    std::string basicStyle;
    std::string textColor;
    std::string backgroundColor;
    std::string errorModeStyle;
    std::string dark = "black";
    std::string light = "white";
};

#endif // USERMODESTYLESHEETGENERATOR_H_


