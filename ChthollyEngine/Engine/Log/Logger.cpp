#include "Logger.h"

const char* xxd::Logger::levelString[5] = {"Debug", "Info", "Warn", "Error", "Fatal"};
const char* xxd::Logger::levelColor[3] = {"\033[33m", "\033[31m", "\033[41m"};
xxd::LogLevel xxd::Logger::minLogLevel = xxd::LogLevelDebug;
xxd::Logger::UTCTimer xxd::Logger::utimer;

xxd::Logger::Logger()
{
}

xxd::Logger::~Logger()
{
}

xxd::Logger::UTCTimer::UTCTimer()
{
    time_t t;
    time(&t);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H:%M:%S", localtime(&t));
    timeStrLen = strlen(timeStr);
}

const char* xxd::Logger::UTCTimer::GetUTCTime()
{
    time_t t;
    time(&t);
    if (sysSec != t)
    {
        int64_t min = t / 60;
        sysSec = t;
        if (min != sysMin)
        {
            sysMin = min;
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H:%M:%S", localtime(&t));
        }
        else
        {
            int32_t sec = sysSec % 60;
            timeStr[timeStrLen - 2] = sec / 10 + 48;
            timeStr[timeStrLen - 1] = sec % 10 + 48;
        }
    }
    return timeStr; 
}