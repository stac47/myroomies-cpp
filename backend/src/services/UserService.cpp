#include <string>
#include <memory>
#include <vector>

#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/UserService.h>

using myroomies::utils::Configuration;

namespace myroomies {
namespace services {

std::shared_ptr<UserService> UserService::BuildFromConfig(
    const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
    const Configuration&)
{
    return std::make_shared<UserService>();
}

UserService::UserService()
  : ServiceInterface("Users")
{}

std::vector<myroomies::bom::User> UserService::getUsers() const
{
    std::vector<myroomies::bom::User> v;
    return v;
}

} /* namespace services */
} /* namespace myroomies */
