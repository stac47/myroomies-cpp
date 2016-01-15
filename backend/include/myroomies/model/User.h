#pragma once

#include <string>
#include <chrono>

namespace myroomies {
namespace model {

struct User
{
    uint32_t id;
    std::string email;
    std::string firstname;
    std::string lastname;
    std::chrono::time_point<std::chrono::system_clock> dateOfBirth;
};

} /* namespace model */
} /* namespace myroomies */
