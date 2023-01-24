INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_EXECUTABLE(
        EyerMathTest
        Main.cpp
)

TARGET_LINK_LIBRARIES (EyerMathTest EyerMath)
TARGET_LINK_LIBRARIES (EyerMathTest EyerCore)
TARGET_LINK_LIBRARIES (EyerMathTest EyerThread)
TARGET_LINK_LIBRARIES (EyerMathTest gtest)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    TARGET_LINK_LIBRARIES (EyerMathTest log)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
    MESSAGE(STATUS "current platform: iOS")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
        TARGETS EyerMathTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)