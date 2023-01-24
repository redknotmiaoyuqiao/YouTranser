INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_EXECUTABLE (
        EyerAVTest
        Test.cpp
)

TARGET_LINK_LIBRARIES (EyerAVTest EyerAV)
TARGET_LINK_LIBRARIES (EyerAVTest EyerMath)
TARGET_LINK_LIBRARIES (EyerAVTest EyerCore)
TARGET_LINK_LIBRARIES (EyerAVTest EyerThread)

TARGET_LINK_LIBRARIES (EyerAVTest gtest)

TARGET_LINK_LIBRARIES (EyerAVTest avformat)
TARGET_LINK_LIBRARIES (EyerAVTest avcodec)
TARGET_LINK_LIBRARIES (EyerAVTest swscale)
TARGET_LINK_LIBRARIES (EyerAVTest swresample)
TARGET_LINK_LIBRARIES (EyerAVTest avutil)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    TARGET_LINK_LIBRARIES (EyerAVTest vpx)
    TARGET_LINK_LIBRARIES (EyerAVTest lzma)
    TARGET_LINK_LIBRARIES (EyerAVTest opus)
    TARGET_LINK_LIBRARIES (EyerAVTest x264)
    TARGET_LINK_LIBRARIES (EyerAVTest x265)
    TARGET_LINK_LIBRARIES (EyerAVTest mp3lame)
    TARGET_LINK_LIBRARIES (EyerAVTest fdk-aac)
    TARGET_LINK_LIBRARIES (EyerAVTest ssl)
    TARGET_LINK_LIBRARIES (EyerAVTest crypto)
    TARGET_LINK_LIBRARIES (EyerAVTest bz2)
    TARGET_LINK_LIBRARIES (EyerAVTest z)
    TARGET_LINK_LIBRARIES (EyerAVTest dl)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D EYER_PLATFORM_WINDOWS)

    TARGET_LINK_LIBRARIES (EyerAVTest mp3lame)
    TARGET_LINK_LIBRARIES (EyerAVTest vpx)
    TARGET_LINK_LIBRARIES (EyerAVTest x264)
    TARGET_LINK_LIBRARIES (EyerAVTest x265)
    TARGET_LINK_LIBRARIES (EyerAVTest fdk-aac)
    TARGET_LINK_LIBRARIES (EyerAVTest ssl)
    TARGET_LINK_LIBRARIES (EyerAVTest crypto)
    TARGET_LINK_LIBRARIES (EyerAVTest Mfuuid)
    TARGET_LINK_LIBRARIES (EyerAVTest Strmiids)
    TARGET_LINK_LIBRARIES (EyerAVTest Mfplat)
    TARGET_LINK_LIBRARIES (EyerAVTest Bcrypt)
    TARGET_LINK_LIBRARIES (EyerAVTest Secur32)
    TARGET_LINK_LIBRARIES (EyerAVTest Crypt32)
    TARGET_LINK_LIBRARIES (EyerAVTest ws2_32)
    TARGET_LINK_LIBRARIES (EyerAVTest msvcrt)
    TARGET_LINK_LIBRARIES (EyerAVTest iconv)
    TARGET_LINK_LIBRARIES (EyerAVTest z)
    TARGET_LINK_LIBRARIES (EyerAVTest bz2)
    TARGET_LINK_LIBRARIES (EyerAVTest lzma)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    ADD_DEFINITIONS(-D EYER_PLATFORM_ANDROID)
    TARGET_LINK_LIBRARIES (EyerAVTest ssl)
    TARGET_LINK_LIBRARIES (EyerAVTest crypto)
    TARGET_LINK_LIBRARIES (EyerAVTest log)
    TARGET_LINK_LIBRARIES (EyerAVTest z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    ADD_DEFINITIONS(-D EYER_PLATFORM_DARWIN)
    SET(CMAKE_EXE_LINKER_FLAGS
        "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
    TARGET_LINK_LIBRARIES (EyerAVTest vpx)
    TARGET_LINK_LIBRARIES (EyerAVTest x264)
    TARGET_LINK_LIBRARIES (EyerAVTest x265)
    TARGET_LINK_LIBRARIES (EyerAVTest iconv)
    TARGET_LINK_LIBRARIES (EyerAVTest lzma)
    TARGET_LINK_LIBRARIES (EyerAVTest mp3lame)
    TARGET_LINK_LIBRARIES (EyerAVTest fdk-aac)
    TARGET_LINK_LIBRARIES (EyerAVTest ssl)
    TARGET_LINK_LIBRARIES (EyerAVTest crypto)
    TARGET_LINK_LIBRARIES (EyerAVTest bz2)
    TARGET_LINK_LIBRARIES (EyerAVTest z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/1.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/2.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/3.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_sei.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/test_image.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/test_image.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/ZhongLi.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/ZhongLi_44100.mp3
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/wmv_test.wmv
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

IF (${IS_THIRD_PART_DIST_DIR} MATCHES "YES")
    IF (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/panasonic_s5_h264_yuv422_10bit_test.MOV)
        FILE(DOWNLOAD
            ${DOWNLOAD_BASE_URL}/panasonic_s5_h264_yuv422_10bit_test.MOV
            ${CMAKE_CURRENT_BINARY_DIR}/panasonic_s5_h264_yuv422_10bit_test.MOV
            SHOW_PROGRESS
            )

        FILE(DOWNLOAD
            ${DOWNLOAD_BASE_URL}/zhaolei_wojide.flac
            ${CMAKE_CURRENT_BINARY_DIR}/zhaolei_wojide.flac
            SHOW_PROGRESS
            )
    ENDIF ()
ENDIF (${IS_THIRD_PART_DIST_DIR} MATCHES "YES")

INSTALL(
        TARGETS EyerAVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
