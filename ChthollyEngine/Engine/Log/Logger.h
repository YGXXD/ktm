#ifndef _LOGGER_H_
#define _LOGGER_H_

#define KEG_LOG(LogLevel, ...) keg::Logger::Log((LogLevel), __VA_ARGS__);
#define KEG_DEBUG(...) KEG_LOG(keg::LogLevelDebug, __VA_ARGS__)
#define KEG_INFO(...) KEG_LOG(keg::LogLevelInfo, __VA_ARGS__)
#define KEG_WARN(...) KEG_LOG(keg::LogLevelWarn, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KEG_ERROR(...) KEG_LOG(keg::LogLevelError, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KEG_FATAL(...) KEG_LOG(keg::LogLevelFatal, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")

#include "Util/Config.h"

namespace keg
{
enum LogLevel : unsigned char
{
    LogLevelDebug = 0,
    LogLevelInfo,
    LogLevelWarn,
    LogLevelError,
    LogLevelFatal
};

class CHTHOLLY_ENGINE_API Logger
{
public:
    Logger();
    ~Logger();
	
	template<typename ...ArgsT>
	static void Log(LogLevel level, ArgsT&&... args);

private:
	template<typename ...ArgsT>
	static CHTHOLLY_INLINE void ConsoleLog(ArgsT&&... args);
	
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
void keg::Logger::Log(keg::LogLevel level, ArgsT&&... args)
{
	if(level >= minLogLevel && level <= LogLevelFatal)
	{
		if(level >= LogLevelWarn)
			ConsoleLog(levelColor[level - LogLevelWarn], utimer.GetUTCTime(), " ", levelString[level], ": ", std::forward<ArgsT>(args)..., "\033[0m");	
		else
			ConsoleLog(utimer.GetUTCTime(), " ", levelString[level], ": ", std::forward<ArgsT>(args)...);
	}
}

template<typename ...ArgsT>
CHTHOLLY_INLINE void keg::Logger::ConsoleLog(ArgsT&&... args)
{
	(std::cout << ... << args) << "\n";
	std::flush(std::cout);
}

#endif

