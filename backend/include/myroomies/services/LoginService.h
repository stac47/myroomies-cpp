#pragma once

#include <string>

#include <myroomies/services/UserService.h>

namespace myroomies {
namespace services {

class LoginService
{
public:
    bool login(const std::string& iUser,
               const std::string& iPassword);
    void logout(const std::string& iUser);
};

} /* namespace services */
} /* namespace myroomies */
