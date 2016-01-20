#pragma once

#include <string>
#include <chrono>

#include <myroomies/model/ModelObject.h>

namespace myroomies {
namespace model {

struct User
{
    Key_t id;
    std::string login;
    std::string firstname;
    std::string lastname;
    std::chrono::time_point<std::chrono::system_clock> dateOfBirth;
    std::string email;
    ForeignKey_t houseshareId;
};

} /* namespace model */
} /* namespace myroomies */
