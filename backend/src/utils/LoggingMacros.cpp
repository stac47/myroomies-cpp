#include <map>
#include <memory>

#include <spdlog/spdlog.h>

#include <myroomies/utils/LoggingMacros.h>

namespace myroomies {
namespace utils {

void Logger::Init(const std::string& iLoggingFolder)
{
    if (iLoggingFolder.empty())
    {
        auto myroomiesLogger = spdlog::stdout_logger_mt("myroomies");
        myroomiesLogger->info() << "Console logging activated";
        auto accessLogger = spdlog::stdout_logger_mt("access");
        auto errorLogger = spdlog::stdout_logger_mt("error");
    }
    else
    {
    }
}


void Logger::Debug(const std::string& iLoggerName, const std::string& iMsg)
{
    spdlog::get(iLoggerName)->debug() << iMsg;
}

void Logger::Info(const std::string& iLoggerName, const std::string& iMsg)
{
    spdlog::get(iLoggerName)->info() << iMsg;
}

void Logger::Warn(const std::string& iLoggerName, const std::string& iMsg)
{
    spdlog::get(iLoggerName)->warn() << iMsg;
}

void Logger::Error(const std::string& iLoggerName, const std::string& iMsg)
{
    spdlog::get(iLoggerName)->error() << iMsg;
}

} /* namespace utils */
} /* namespace myroomies */
