cmake_minimum_required(VERSION 3.5)

project(YouPicker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui

        YouPickerAppConfig.hpp 
        YouPickerAppConfig.cpp

        YouPickerLoading.hpp 
        YouPickerLoading.cpp 

        YouPickerLogin.hpp 
        YouPickerLogin.cpp

        YPSessionListWindow.hpp
        YPSessionListWindow.cpp
        YPSessionListWindow.ui

        YPSessionCreateWindow.hpp
        YPSessionCreateWindow.cpp
        YPSessionCreateWindow.ui
)

set(Qrc_Files
    you-picker.qrc
    )

qt_add_resources(QRC_FILES ${Qrc_Files})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YouPicker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QRC_FILES}
    )
else()
    add_executable(YouPicker
        ${PROJECT_SOURCES}
        ${QRC_FILES}
    )
endif()

target_link_libraries(YouPicker PRIVATE
    YouCommon

    YouPickerSession

    EyerSQLite

    EyerCore
    EyerThread

    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

set_target_properties(YouPicker PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS YouPicker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(YouPicker)
endif()
