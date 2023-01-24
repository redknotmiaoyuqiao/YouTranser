INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(../)

ADD_EXECUTABLE(
        EyerAVTranscoderTest
        Main.cpp
)

TARGET_LINK_LIBRARIES (EyerAVTranscoderTest EyerAVTranscoder)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest EyerAV)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest EyerCore)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest EyerThread)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest gtest gtest_main)

TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_core)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_calib3d)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_dnn)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_features2d)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_flann)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_gapi)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_highgui)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_imgcodecs)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_imgproc)
TARGET_LINK_LIBRARIES (EyerAVTranscoderTest opencv_ml)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    TARGET_LINK_LIBRARIES (EyerAVTranscoderTest lzma)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "iOS")
    MESSAGE(STATUS "current platform: iOS")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    MESSAGE(STATUS "current platform: Emscripten")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


IF (${IS_THIRD_PART_DIST_DIR} MATCHES "YES")
    IF (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/panasonic_s5_h264_yuv422_10bit_test.MOV)
        FILE(DOWNLOAD
            ${DOWNLOAD_BASE_URL}/panasonic_s5_h264_yuv422_10bit_test.MOV
            ${CMAKE_CURRENT_BINARY_DIR}/panasonic_s5_h264_yuv422_10bit_test.MOV
            SHOW_PROGRESS
            )
    ENDIF ()

    IF (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV)
        FILE(DOWNLOAD
                ${DOWNLOAD_BASE_URL}/panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV
                ${CMAKE_CURRENT_BINARY_DIR}/panasonic_S5_h264_1920x1080_yuv420p_30fps_wedding2.MOV
                SHOW_PROGRESS
                )
    ENDIF ()
ENDIF (${IS_THIRD_PART_DIST_DIR} MATCHES "YES")

INSTALL(
        TARGETS EyerAVTranscoderTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)