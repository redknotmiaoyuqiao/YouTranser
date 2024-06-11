#include "EyerLog.hpp"

#include "EyerTime.hpp"

#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <stdarg.h>

void eyer_log_log(const char * file, const char * function, int line, int level, const char * format, ...)
{
    if(Eyer::EyerLogStatus::ifPrint == 0){
        return;
    }

    char log_str[4096];
    memset(log_str, 0, 4096);

    va_list args;
    va_start(args, format);
    vsnprintf(log_str, 4096, format, args);
    va_end(args);

    std::string logstr;

    char levelStr[8];
    sprintf(levelStr, "[%2d] ", level);
    logstr += levelStr;

    // logstr += "[" + std::string(Eyer::EyerTime::TimeFormat().c_str()) + "] ";
    logstr += "[" + std::string(file) + "(" + std::to_string(line) + ")" + "] ";
    // logstr += "[" + std::to_string((long)pthread_self()) + "]";

    logstr += log_str;

    fprintf(stdout, "%s", logstr.c_str());
    fflush(stdout);
    fflush(stderr);
}


void eyer_log_log_err(const char * file, const char * function, int line, int level, const char * format, ...)
{
    char log_str[4096];
    memset(log_str, 0, 4096);

    va_list args;
    va_start(args, format);
    vsnprintf(log_str, 4096, format, args);
    va_end(args);

    std::string logstr;

    char levelStr[8];
    sprintf(levelStr, "[%2d] ", level);
    logstr += levelStr;

    // logstr += "[" + std::string(Eyer::EyerTime::TimeFormat().c_str()) + "] ";
    logstr += "[" + std::string(file) + "(" + std::to_string(line) + ")" + "] ";
    // logstr += "[" + std::to_string((long)pthread_self()) + "]";

    logstr += log_str;

    fprintf(stderr, "%s", logstr.c_str());
    fflush(stdout);
    fflush(stderr);
}