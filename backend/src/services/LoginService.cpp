#include <string>
#include <memory>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/LoggingMacros.h>

#include <myroomies/bom/User.h>

#include <myroomies/services/Exception.h>
#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/UserService.h>
#include <myroomies/services/LoginService.h>
#include <myroomies/services/ServiceRegistry.h>

using myroomies::bom::User;

namespace myroomies {
namespace services {

std::shared_ptr<LoginService> LoginService::BuildFromConfig(
    const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
    const myroomies::utils::Configuration&)
{
    return std::shared_ptr<LoginService>(new LoginService(iServiceRegistry));
}

LoginService::LoginService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry)
  : ServiceInterface("Login"),
    userService_(iServiceRegistry->get<UserService>())
{}

std::unique_ptr<const User> LoginService::login(
    const std::string& iLogin,
    const std::string& iPassword)
{
    std::unique_ptr<const User> ret;
    try
    {
        const User user = userService_->getUserByLogin(iLogin);
        if (user.passwordHash == iPassword)
        {
            ret = std::make_unique<const User>(user);
        }
    }
    catch(const ResourceNotFoundException&)
    {
        MYROOMIES_LOG_WARN("User provided wrong credentials ["
                           << iLogin << ":" << iPassword << "]");
    }
    MYROOMIES_LOG_INFO("User [id=" << ret->id << "] logged in  MyRoomies");
    return ret;
}

} /* namespace services */
} /* namespace myroomies */
