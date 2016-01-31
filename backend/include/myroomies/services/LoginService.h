#pragma once

#include <string>
#include <memory>

#include <myroomies/utils/Configuration.h>

#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

class UserService;

class LoginService : public ServiceInterface
{
public:
    static std::shared_ptr<LoginService> BuildFromConfig(
        const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
        const myroomies::utils::Configuration&);

    std::unique_ptr<const myroomies::bom::User> login(
        const std::string& iUser,
        const std::string& iPassword);
private:
    LoginService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry);

    std::shared_ptr<UserService> userService_;
};

} /* namespace services */
} /* namespace myroomies */
