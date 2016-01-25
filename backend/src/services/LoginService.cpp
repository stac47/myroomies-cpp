#include <string>
#include <memory>

#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/UserService.h>
#include <myroomies/services/LoginService.h>
#include <myroomies/services/ServiceRegistry.h>

namespace myroomies {
namespace services {

std::shared_ptr<LoginService> LoginService::BuildFromConfig(
    const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
    const myroomies::utils::Configuration&)
{
    return std::shared_ptr<LoginService>(new LoginService(iServiceRegistry));
}

LoginService::LoginService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry)
  : ServiceInterface(),
    userService_(iServiceRegistry->get<UserService>())
{}

bool LoginService::login(const std::string& iUser,
                         const std::string& iPassword)
{
    return true;
}

} /* namespace services */
} /* namespace myroomies */
