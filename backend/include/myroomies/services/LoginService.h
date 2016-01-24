#pragma once

#include <string>
#include <memory>

#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

class LoginService : public ServiceInterface
{
public:
    static std::shared_ptr<LoginService> BuildFromConfig(
        const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
        const myroomies::utils::Configuration&);

    bool login(const std::string& iUser,
               const std::string& iPassword);
private:
    LoginService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry);
};

} /* namespace services */
} /* namespace myroomies */
