#pragma once

#include <map>
#include <memory>
#include <sstream>

namespace myroomies {
namespace utils {

class Logger
{
public:
    static void Init(const std::string& iLoggingFolder = "");

    static void Debug(const std::string& iLoggerName, const std::string& iMsg);
    static void Info(const std::string& iLoggerName, const std::string& iMsg);
    static void Warn(const std::string& iLoggerName, const std::string& iMsg);
    static void Error(const std::string& iLoggerName, const std::string& iMsg);
};

} /* namespace utils */
} /* namespace myroomies */

#define MYROOMIES_LOG(_level_, _msg_)                               \
{                                                                   \
    std::stringstream ss;                                           \
    ss << "<" << __FILE__ << ":" << __LINE__<< "> " << _msg_;      \
    myroomies::utils::Logger::_level_("myroomies", ss.str());       \
}

#define MYROOMIES_LOG_INFO(_msg_)                                   \
    MYROOMIES_LOG(Info, _msg_)

#define MYROOMIES_LOG_DEBUG(_msg_)                                  \
    MYROOMIES_LOG(Debug, _msg_)

#define MYROOMIES_LOG_WARN(_msg_)                                   \
    MYROOMIES_LOG(Warn, _msg_)

#define MYROOMIES_LOG_ERROR(_msg_)                                  \
    MYROOMIES_LOG(Error, _msg_)

#define MYROOMIES_LOG_HTTPSERVER_ACCESS(_msg_)                      \
{                                                                   \
    std::stringstream ss;                                           \
    ss << "<" << __FILE__ << ":" << __LINE__<< "> " << _msg_;      \
    myroomies::utils::Logger::Info("access", ss.str());             \
}

#define MYROOMIES_LOG_HTTPSERVER_ERROR(_msg_)                       \
{                                                                   \
    std::stringstream ss;                                           \
    ss << "<" << __FILE__ << ":" << __LINE__<< "> " << _msg_;      \
    myroomies::utils::Logger::Error("error", ss.str());           \
}
