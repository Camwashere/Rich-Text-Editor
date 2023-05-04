cmake_minimum_required(VERSION 3.5)

project(RichTextEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Qml)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Tools/TextEditor/editor.h
        Tools/TextEditor/editor.cpp
        Tools/TextEditor/editor.ui
        Tools/TextEditor/Logic/textexpression.h
        Tools/TextEditor/Logic/textexpression.cpp
        Tools/TextEditor/Logic/token.h
        Tools/TextEditor/Logic/token.cpp
        Tools/TextEditor/Logic/lexer.h
        Tools/TextEditor/Logic/lexer.cpp
        Tools/ColorPicker/colorpicker.h
        Tools/ColorPicker/colorpicker.cpp
        Tools/TextEditor/Logic/shuntingyard.h
        Tools/TextEditor/Logic/shuntingyard.cpp
        Core/id.h Core/id.cpp
        Core/variable.h
        Core/variable.cpp
        Core/fundamental.h Core/fundamental.cpp
        Resources/resources.qrc

)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RichTextEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RichTextEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RichTextEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RichTextEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RichTextEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Qml)

set_target_properties(RichTextEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS RichTextEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RichTextEditor)
endif()
