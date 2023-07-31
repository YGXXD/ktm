#include "Logger.hpp"
#include <cstdarg>
#include <iostream>

const char* xxd::Logger::levelString[5] = {"Debug", "Info", "Warn", "Error", "Fatal"};
const char* xxd::Logger::levelColor[3] = {"\033[33m", "\033[31m", "\033[41m"};
xxd::LogLevel xxd::Logger::minLogLevel = xxd::Debug;
xxd::Logger::UTCTimer xxd::Logger::utimer;

xxd::Logger::Logger()
{
}

xxd::Logger::~Logger()
{
}

