#include <map>
#include <memory>

#include <spdlog/spdlog.h>

#include <myroomies/utils/LoggingMacros.h>

namespace myroomies {
namespace utils {

void InitLoggers(const std::string& iLoggingFolder)
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

} /* namespace utils */
} /* namespace myroomies */
