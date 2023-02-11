cmake_minimum_required(VERSION 3.5)

project(YouCommon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network core)

set(PROJECT_SOURCES
    AboutWindow.ui
    AboutWindow.h
    AboutWindow.cpp

    LoadingWindow.ui
    LoadingWindow.h
    LoadingWindow.cpp

    LoginWindow.ui
    LoginWindow.h
    LoginWindow.cpp

    LoadingTimerThread.h
    LoadingTimerThread.cpp

    MediaEyeApplication.h
    MediaEyeApplication.cpp

    MediaEyeCommon.h
    MediaEyeCommon.cpp

    EyerQFlowLayout.h
    EyerQFlowLayout.cpp
)


add_library(YouCommon
    ${PROJECT_SOURCES}
)

target_link_libraries(YouCommon PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

set_target_properties(YouCommon PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS YouCommon
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
