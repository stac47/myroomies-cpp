#pragma once

#include <map>
#include <memory>

#include <spdlog/spdlog.h>

namespace myroomies {
namespace utils {

void InitLoggers(const std::string& iLoggingFolder = "");

} /* namespace utils */
} /* namespace myroomies */

#define MYROOMIES_LOG_INFO(_msg_) \
    spdlog::get("myroomies")->info() << " <"\
        << __FILE__ << ":" << __LINE__<< "> " << _msg_;

#define MYROOMIES_LOG_WARNING(_msg_) \
    spdlog::get("myroomies")->warn() << " <"\
        << __FILE__ << ":" << __LINE__<< "> " << _msg_;

#define MYROOMIES_LOG_ERROR(_msg_) \
    spdlog::get("myroomies")->error() << " <"\
        << __FILE__ << ":" << __LINE__<< "> " << _msg_;
