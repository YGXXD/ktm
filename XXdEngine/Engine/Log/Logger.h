#ifndef _LOGGER_H_
#define _LOGGER_H_

#define XXD_LOG(LogLevel, ...) xxd::Logger::Log((LogLevel), __VA_ARGS__)
#define DEBUG_LOG(...) XXD_LOG(xxd::LogLevelDebug, __VA_ARGS__)
#define INFO_LOG(...) XXD_LOG(xxd::LogLevelInfo, __VA_ARGS__)
#define WARN_LOG(...) XXD_LOG(xxd::LogLevelWarn, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define ERROR_LOG(...) XXD_LOG(xxd::LogLevelError, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define FATAL_LOG(...) XXD_LOG(xxd::LogLevelFatal, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")

#include "XXd.h"

namespace xxd
{
enum LogLevel : unsigned char
{
    LogLevelDebug = 0,
    LogLevelInfo,
    LogLevelWarn,
    LogLevelError,
    LogLevelFatal
};

class XXD_API Logger
{
public:
    Logger();
    ~Logger();
	
	template<typename ...ArgsT>
	static void Log(LogLevel level, ArgsT &&... args)
	{
		if(level >= minLogLevel && level <= LogLevelFatal)
		{
			if(level >= LogLevelWarn)
				ConsoleLog(utimer.GetUTCTime(), " ", levelColor[level - LogLevelWarn], levelString[level], ": ", std::forward<ArgsT>(args)..., "\033[0m");	
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
		UTCTimer();
        const char* GetUTCTime();

    private:
        char timeStr[64];
    	size_t timeStrLen;
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
