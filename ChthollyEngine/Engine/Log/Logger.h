#ifndef _LOGGER_H_
#define _LOGGER_H_

#define KTL_LOG(LogLevel, ...) ktl::Logger::Log((LogLevel), __VA_ARGS__);
#define KTL_DEBUG(...) KTL_LOG(ktl::LogLevelDebug, __VA_ARGS__)
#define KTL_INFO(...) KTL_LOG(ktl::LogLevelInfo, __VA_ARGS__)
#define KTL_WARN(...) KTL_LOG(ktl::LogLevelWarn, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KTL_ERROR(...) KTL_LOG(ktl::LogLevelError, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KTL_FATAL(...) KTL_LOG(ktl::LogLevelFatal, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")

#include "Chtholly.h"

namespace ktl
{
enum LogLevel : unsigned char
{
    LogLevelDebug = 0,
    LogLevelInfo,
    LogLevelWarn,
    LogLevelError,
    LogLevelFatal
};

class CHTHOLLY_API Logger
{
public:
    Logger();
    ~Logger();
	
	template<typename ...ArgsT>
	static void Log(LogLevel level, ArgsT&&... args);

private:
	template<typename ArgT, typename ...ArgsT>
	static CHTHOLLY_INLINE void ConsoleLog(ArgT && arg, ArgsT&&... args);

	template<typename ArgT>
	static CHTHOLLY_INLINE void ConsoleLog(ArgT&& arg);
	
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

template<typename ...ArgsT>
void ktl::Logger::Log(ktl::LogLevel level, ArgsT&&... args)
{
	if(level >= minLogLevel && level <= LogLevelFatal)
	{
		if(level >= LogLevelWarn)
			ConsoleLog(levelColor[level - LogLevelWarn], utimer.GetUTCTime(), " ", levelString[level], ": ", std::forward<ArgsT>(args)..., "\033[0m");	
		else
			ConsoleLog(utimer.GetUTCTime(), " ", levelString[level], ": ", std::forward<ArgsT>(args)...);
	}
}

template<typename ArgT, typename ...ArgsT>
CHTHOLLY_INLINE void ktl::Logger::ConsoleLog(ArgT && arg, ArgsT&&... args)
{
	std::cout << arg;
	ConsoleLog(std::forward<ArgsT>(args)...);
}

template<typename ArgT>
CHTHOLLY_INLINE void ktl::Logger::ConsoleLog(ArgT&& arg)
{
	std::cout << arg << "\n";
	std::flush(std::cout);
}
#endif

