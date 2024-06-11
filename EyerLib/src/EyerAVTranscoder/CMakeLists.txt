INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY(
        EyerAVTranscoder

        EyerAVTranscoder.hpp
        EyerAVTranscoder.cpp

        EyerAVTranscodeStream.hpp
        EyerAVTranscodeStream.cpp

        EyerAVTranscoderParams.hpp
        EyerAVTranscoderParams.cpp

        EyerAVTranscoderStreamConfig.hpp
        EyerAVTranscoderStreamConfig.cpp

        EyerAVTranscoderSupport.hpp
        EyerAVTranscoderSupport.cpp

        EyerAVTranscoderStatus.hpp
        EyerAVTranscoderStatus.cpp

        EyerAVTranscoderError.cpp
        EyerAVTranscoderError.hpp
)

TARGET_LINK_LIBRARIES (EyerAVTranscoder EyerAV)
TARGET_LINK_LIBRARIES (EyerAVTranscoder EyerMath)
TARGET_LINK_LIBRARIES (EyerAVTranscoder EyerCore)
TARGET_LINK_LIBRARIES (EyerAVTranscoder EyerThread)

TARGET_LINK_LIBRARIES (EyerAVTranscoder gtest)

TARGET_LINK_LIBRARIES (EyerAVTranscoder avformat)
TARGET_LINK_LIBRARIES (EyerAVTranscoder avcodec)
TARGET_LINK_LIBRARIES (EyerAVTranscoder swscale)
TARGET_LINK_LIBRARIES (EyerAVTranscoder swresample)
TARGET_LINK_LIBRARIES (EyerAVTranscoder avutil)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D EYER_PLATFORM_WINDOWS)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    ADD_DEFINITIONS(-D EYER_PLATFORM_ANDROID)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    ADD_DEFINITIONS(-D EYER_PLATFORM_DARWIN)
    SET(CMAKE_EXE_LINKER_FLAGS
            "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
            )
    TARGET_LINK_LIBRARIES (EyerAVTranscoder vpx)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder x264)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder x265)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder iconv)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder lzma)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder mp3lame)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder fdk-aac)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder ssl)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder crypto)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder bz2)
    TARGET_LINK_LIBRARIES (EyerAVTranscoder z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

SET(HEAD_FILES
        EyerAVTranscoderHeader.hpp
        EyerAVTranscoder.hpp
        EyerAVTranscoderParams.hpp
        EyerAVTranscoderStreamConfig.hpp
        EyerAVTranscoderSupport.hpp
        EyerAVTranscodeStream.hpp
        EyerAVTranscoderStatus.hpp
        EyerAVTranscoderError.hpp
        )

INSTALL(FILES ${HEAD_FILES} DESTINATION include/EyerAVTranscoder)
INSTALL(
        TARGETS EyerAVTranscoder
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

