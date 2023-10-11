#include "Logger.h"

keg::LogLevel keg::Logger::minLogLevel = keg::LogLevel::Debug;
keg::Logger::UTCTimer keg::Logger::utimer;

keg::Logger::Logger()
{
}

keg::Logger::~Logger()
{
}

keg::Logger::UTCTimer::UTCTimer()
{
    time_t t;
    time(&t);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H:%M:%S", localtime(&t));
    timeStrLen = strlen(timeStr);
}

const char* keg::Logger::UTCTimer::GetUTCTime()
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