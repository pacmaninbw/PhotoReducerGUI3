# Photo Reducer with QT GUI 

This project is created using only C++ code, QT Creator is not used except to generate the project and CMake files themselves.  

The basic controls and actions are the same as the [GUI Photo Reduction Tool](https://github.com/pacmaninbw/GUIPhotoReductionTool), but rather than use QT Creator to create the main window and the options dialog the code is all written by the developer. I found I wasn't learning enough about QT development by using QT Creator.  

## Goals  
The primary goal of this project is to learn QT 6.  

A secondary goal is to be able to implement the Model View Controller design pattern in QT using C++.

# Development Environment  
 - Ubuntu 22.04  
 - Visual Studio Code  
 - C++ 23  
 - gcc 12  
 - QT 6.2  
 - CMake

# Code Review  
The code here was presented as a question on the [Stack Exchange Q & A site Code Review](https://codereview.stackexchange.com/questions/295368/qt-6-c-model-view-view-model-graphic-photo-size-reducer-tool) on February 14, 2025. The branch [CodeReviewSource](https://github.com/pacmaninbw/PhotoReducerGUI3/tree/CodeReviewSource) is the exact code that was presented at that time.  

## Issues Found Through Code Review  
 - Prefer standard C++ features over QT provided features.  
 - The views can't be resize properly (can't make very small windows).  
 - The user should be able to edit values in the line edits.  
 - Users using a dark theme with white text are unable to see the value of the line edits after an error has been corrected.  
 - Prefer regular number display (Label or LineEdit) over the QLCDNumber display.  
 - The MainWindow class has unnecessary variables.  
 - The Model View ViewModel implementation is not correct, the current PhotoReducerModel class should be separated into a Model and a ViewModel.  
 - The Signals and Slots feature of QT is somewhat dated, Signals can still be used but there are alternatives to Slots that don't require the MOC.  

The issues found will be added as issues to the repository.  
