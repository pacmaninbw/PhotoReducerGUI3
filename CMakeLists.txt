cmake_minimum_required(VERSION 3.31)

project(PhotoReducerGUI3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
        include/createNamedQTWidget.h
        include/DirectoryLineEdit.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        OptionsDialog.cpp 
        OptionsDialog.h
        OptionsInitStruct.h
        OptionErrorCode.h
        include/NumericLineEdit.h
    	PhotoReducerModel.h
        PhotoReducerModel.cpp
        SignalRouterController.h
        SignalRouterController.cpp
        UserModeStyleSheetGenerator.h
        UserModeStyleSheetGenerator.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PhotoReducerGUI3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PhotoReducerGUI3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PhotoReducerGUI3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PhotoReducerGUI3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PhotoReducerGUI3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})
target_include_directories(PhotoReducerGUI3 PRIVATE include)


set_target_properties(PhotoReducerGUI3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhotoReducerGUI3)
endif()
