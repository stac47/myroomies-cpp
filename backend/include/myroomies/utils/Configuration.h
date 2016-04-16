#pragma once

#include <string>

namespace myroomies {
namespace utils {

struct Configuration {
    std::string address;
    uint16_t port;
    std::string loggingPath;
    std::string staticsPath;
    std::string dbPath;
    bool dbCreate;
    std::string adminPassword;
};

} /* namespace utils */
} /* namespace myroomies */
