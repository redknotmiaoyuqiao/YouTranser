cmake_minimum_required(VERSION 3.5)

project(YouTranser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network core)

INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

set(PROJECT_SOURCES
        main.cpp

        MainWindow.cpp
        MainWindow.h
        MainWindow.ui

        YouTransMainWindow.hpp
        YouTransMainWindow.cpp
        YouTransMainWindow.ui

        YouTransConfig.hpp
        YouTransConfig.cpp
        YouTransConfig.ui

        YouTransAboutWindow.hpp
        YouTransAboutWindow.cpp
        YouTransAboutWindow.ui

        TaskItem.hpp
        TaskItem.cpp
        TaskItem.ui

        TaskItemStatusLabel.hpp
        TaskItemStatusLabel.cpp

        YouTransAppConfig.hpp
        YouTransAppConfig.cpp

        YouTransLoading.hpp
        YouTransLoading.cpp

        YouTransLogin.hpp
        YouTransLogin.cpp

        TranscodeTaskThread.hpp
        TranscodeTaskThread.cpp

        YouTranscoderParams.hpp
        YouTranscoderParams.cpp
)

set(Qrc_Files
    you-trans.qrc
    )

set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})

set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})

set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${spectral_VERSION})
set(MACOSX_BUNDLE_BUNDLE_VERSION ${spectral_VERSION})

set(ICON_NAME "YouTransIcon.icns")
set(${PROJECT_NAME}_MAC_ICON "${PROJECT_SOURCE_DIR}/icons/${ICON_NAME}")
set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
set_property(SOURCE "${${PROJECT_NAME}_MAC_ICON}" PROPERTY
    MACOSX_PACKAGE_LOCATION Resources)

qt_add_resources(QRC_FILES ${Qrc_Files})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YouTranser
        MACOSX_BUNDLE
        ${${PROJECT_NAME}_MAC_ICON}
        ${PROJECT_SOURCES}
        ${QRC_FILES}
    )
else()
    add_executable(YouTranser
        ${${PROJECT_NAME}_MAC_ICON}
        ${PROJECT_SOURCES}
        ${QRC_FILES}
        "win_icon.rc"
    )
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY
      MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/macOS/Info.plist.in")


IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")


IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    target_link_libraries(YouTranser PRIVATE
        YouCommon

        YouPickerSession

        EyerAVTranscoder

        EyerAV

        EyerSQLite

        EyerMath

        EyerCore
        EyerThread

        avformat
        avcodec
        swscale
        swresample
        avutil

        x264
        x265
        vpx
        mp3lame
        fdk-aac

        ssl
        crypto

        Strmiids
        Mfplat
        Bcrypt
        Secur32
        Crypt32
        ws2_32

        iconv
        lzma
        z
        bz2

        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    target_link_libraries(YouTranser PRIVATE
        YouCommon

        YouPickerSession

        EyerAVTranscoder

        EyerAV

        EyerSQLite

        EyerMath

        EyerCore
        EyerThread

        avformat
        avcodec
        swscale
        swresample
        avutil

        x264
        x265
        vpx
        mp3lame
        fdk-aac

        ssl
        crypto

        iconv
        lzma
        z
        bz2

        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
    ADD_DEFINITIONS(-D EYER_PLATFORM_IOS)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")



set_target_properties(YouTranser PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER youtrans.zzsin.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS YouTranser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(YouTranser)
endif()
