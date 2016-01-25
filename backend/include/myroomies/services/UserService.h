#pragma once

#include <vector>
#include <memory>

#include <myroomies/utils/Configuration.h>

#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

class UserService : public ServiceInterface
{
public:
    static std::shared_ptr<UserService> BuildFromConfig(
        const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
        const myroomies::utils::Configuration&);

    UserService();

    std::vector<myroomies::bom::User> getUsers() const;

};
} /* namespace services */
} /* namespace myroomies */
