#ifndef LOGGER_HPP
#define LOGGER_HPP

#define XXD_LOG(LogLevel, ...) xxd::Logger::Log((LogLevel), __VA_ARGS__)
#define DEBUG_LOG(...) XXD_LOG(xxd::LogLevel::Debug, __VA_ARGS__)
#define INFO_LOG(...) XXD_LOG(xxd::LogLevel::Info, __VA_ARGS__)
#define WARN_LOG(...) XXD_LOG(xxd::LogLevel::Warn, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define ERROR_LOG(...) XXD_LOG(xxd::LogLevel::Error, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define FATAL_LOG(...) XXD_LOG(xxd::LogLevel::Fatal, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")

#include "XXd.hpp"
#include <memory>
#include <stdint.h>
#include <iostream>
#include <sstream>

namespace xxd
{
enum LogLevel : unsigned char
{
    Debug = 0,
    Info,
    Warn,
    Error,
    Fatal,
    Max
};

class XXD_API Logger
{
public:
    Logger();
    ~Logger();
	
	template<typename ...ArgsT>
	static void Log(LogLevel level, ArgsT &&... args)
	{
		if(level >= minLogLevel && level < LogLevel::Max)
		{
			if(level >= LogLevel::Warn)
				ConsoleLog(utimer.GetUTCTime(), " ", levelColor[level - LogLevel::Warn], levelString[level], ": ", std::forward<ArgsT>(args)..., "\033[0m");	
			else
				ConsoleLog(utimer.GetUTCTime(), " ", levelString[level], ": ", std::forward<ArgsT>(args)...);
		}
	}

private:
	template<typename ArgT, typename ...ArgsT>
	static void ConsoleLog(ArgT && arg, ArgsT &&... args)
	{
		std::cout << arg;
		ConsoleLog(std::forward<ArgsT>(args)...);
	}

	template<typename ArgT>
	static void ConsoleLog(ArgT && arg)
	{
		std::cout << arg << "\n";
		std::flush(std::cout);
	}
	
	struct UTCTimer
	{
		UTCTimer() 
		{
			time_t t;
    		time(&t);
			strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H:%M:%S", localtime(&t));
    	    timeStrLen = strlen(timeStr);
		}

        const char* GetUTCTime()
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

    private:
    	uint32_t timeStrLen;
    	char timeStr[32];
    	int64_t sysSec;
    	int64_t sysMin;
	};
	
	// 变量
    static LogLevel minLogLevel;
	static const char* levelString[];
	static const char* levelColor[];
	static UTCTimer utimer;
};

} 
#endif

