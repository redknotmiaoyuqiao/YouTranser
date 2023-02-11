CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(YouTranser VERSION 0.1 LANGUAGES CXX)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network core)
FIND_PACKAGE(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network core)

INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

SET(PROJECT_SOURCES
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

SET(Qrc_Files
    you-trans.qrc
    )

SET(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
SET(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})

SET(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})

SET(MACOSX_BUNDLE_SHORT_VERSION_STRING ${spectral_VERSION})
SET(MACOSX_BUNDLE_BUNDLE_VERSION ${spectral_VERSION})

SET(ICON_NAME "YouTransIcon.icns")
SET(${PROJECT_NAME}_MAC_ICON "${PROJECT_SOURCE_DIR}/icons/${ICON_NAME}")
SET(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
SET_PROPERTY(SOURCE "${${PROJECT_NAME}_MAC_ICON}" PROPERTY
    MACOSX_PACKAGE_LOCATION Resources)

QT_ADD_RESOURCES(QRC_FILES ${Qrc_Files})

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_EXECUTABLE(YouTranser
        ${${PROJECT_NAME}_MAC_ICON}
        ${PROJECT_SOURCES}
        ${QRC_FILES}
        "win_icon.rc"
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    QT_ADD_EXECUTABLE(YouTranser
        MACOSX_BUNDLE
        ${${PROJECT_NAME}_MAC_ICON}
        ${PROJECT_SOURCES}
        ${QRC_FILES}
    )
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY
      MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/macOS/Info.plist.in")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    TARGET_LINK_LIBRARIES(YouTranser PRIVATE
        YouCommon

        EyerAVTranscoder

        EyerAV

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
    TARGET_LINK_LIBRARIES(YouTranser PRIVATE
        YouCommon

        EyerAVTranscoder

        EyerAV

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

SET_TARGET_PROPERTIES(YouTranser PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER youtrans.zzsin.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

INSTALL(TARGETS YouTranser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

IF(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(YouTranser)
ENDIF()

# $CMAKE_HOME/bin/cmake ../YouPicker/ -DCMAKE_PREFIX_PATH=C:/Qt/6.2.4/mingw_64/ -G "MinGW Makefiles"