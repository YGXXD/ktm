#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "Util/Config.h"

#define KEG_LOG(LogLevel, ...) keg::Logger::Log((LogLevel), __VA_ARGS__);
#define KEG_DEBUG(...) KEG_LOG(keg::LogLevel::Debug, __VA_ARGS__)
#define KEG_INFO(...) KEG_LOG(keg::LogLevel::Info, __VA_ARGS__)
#define KEG_WARN(...) KEG_LOG(keg::LogLevel::Warn, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KEG_ERROR(...) KEG_LOG(keg::LogLevel::Error, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")
#define KEG_FATAL(...) KEG_LOG(keg::LogLevel::Fatal, __VA_ARGS__, " (file:", __FILE__, " line:", __LINE__, ")")

namespace keg
{
enum class LogLevel : unsigned char
{
    Debug = 0,
    Info,
    Warn,
    Error,
    Fatal
};

class CHTHOLLY_ENGINE_API Logger
{
public:
    Logger();
    ~Logger();
	
	template<typename ...ArgsT>
	static void Log(LogLevel level, ArgsT&&... args);

	static CHTHOLLY_INLINE void SetMinLogLevel(LogLevel level) { minLogLevel = level; }
	static CHTHOLLY_INLINE LogLevel GetMinLogLevel() { return minLogLevel; }
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
	static UTCTimer utimer;

	static constexpr const char* levelString[5] = {"Debug", "Info", "Warn", "Error", "Fatal"};;
	static constexpr const char* levelColor[3] = {"\033[33m", "\033[31m", "\033[41m"};;
};

} 

template<typename ...ArgsT>
void keg::Logger::Log(keg::LogLevel level, ArgsT&&... args)
{
	if(level >= minLogLevel && level <= LogLevel::Fatal)
	{
		if(level >= LogLevel::Warn)
			ConsoleLog(levelColor[static_cast<unsigned char>(level) - static_cast<unsigned char>(LogLevel::Warn)], utimer.GetUTCTime(), " ", levelString[static_cast<unsigned char>(level)], ": ", std::forward<ArgsT>(args)..., "\033[0m");	
		else
			ConsoleLog(utimer.GetUTCTime(), " ", levelString[static_cast<unsigned char>(level)], ": ", std::forward<ArgsT>(args)...);
	}
}

template<typename ...ArgsT>
CHTHOLLY_INLINE void keg::Logger::ConsoleLog(ArgsT&&... args)
{
	(std::cout << ... << args) << "\n";
	std::flush(std::cout);
}

#endif

