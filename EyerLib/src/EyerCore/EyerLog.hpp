#ifndef	EYER_LIB_LOG_H
#define	EYER_LIB_LOG_H


#include <EyerThread/EyerThread.hpp>

#define EYER_LOG_LEVEL_ERROR 1
#define EYER_LOG_LEVEL_INFO 2
#define EYER_LOG_LEVEL_WARNING 3

#ifdef EYER_PLATFORM_ANDROID
// #define BaseEyerLog(format, ...) printf(format, ##__VA_ARGS__)

#include <android/log.h>
#define LOG_TAG "EyerWand"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define EyerLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define BaseEyerLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#else
// #define EyerLog(format, ...) EyerPrintf(__FILE__, __FUNCTION__ ,__LINE__, 2, format, ##__VA_ARGS__)
// #define BaseEyerLog(format, ...) printf(format, ##__VA_ARGS__)

#define EyerLog_1(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 1, format, ##__VA_ARGS__)
#define EyerLog_2(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 2, format, ##__VA_ARGS__)
#define EyerLog_3(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 3, format, ##__VA_ARGS__)
#define EyerLog_4(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 4, format, ##__VA_ARGS__)
#define EyerLog_5(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 5, format, ##__VA_ARGS__)
#define EyerLog_6(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 6, format, ##__VA_ARGS__)
#define EyerLog_7(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 7, format, ##__VA_ARGS__)
#define EyerLog_8(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 8, format, ##__VA_ARGS__)
#define EyerLog_9(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 9, format, ##__VA_ARGS__)
#define EyerLog_10(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 10, format, ##__VA_ARGS__)
#define EyerLog(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 5, format, ##__VA_ARGS__)

#define EyerLogLevel(level, format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, level, format, ##__VA_ARGS__)

#define EyerINFO(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 5, format, ##__VA_ARGS__)
#define EyerWRANING(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 10, format, ##__VA_ARGS__)
#define EyerERROR(format, ...) eyer_log_log(__FILE__, __FUNCTION__, __LINE__, 20, format, ##__VA_ARGS__)

#endif

#ifdef __cplusplus
extern "C" {
#endif

void    eyer_log_log            (const char * file, const char * function, int line, int level, const char * format, ...);

#ifdef __cplusplus
}
#endif

#include "EyerString.hpp"

namespace Eyer
{
    class EyerVersion
    {
    public:
        static EyerString GetEyerLibVersion();
    };
}

#endif