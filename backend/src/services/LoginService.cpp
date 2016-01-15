#include <string>

#include <myroomies/services/LoginService.h>

namespace myroomies {
namespace services {

bool LoginService::login(const std::string& iUser,
                         const std::string& iPassword)
{
    return true;
}

void LoginService::logout(const std::string& iUser)
{
}

} /* namespace services */
} /* namespace myroomies */
