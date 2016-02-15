#pragma once

#include <vector>
#include <memory>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/db/Def.h>

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

    std::vector<myroomies::bom::User> getUsersFromHouseshare(
        myroomies::utils::db::Key_t iHouseshareId) const;

    myroomies::bom::User getUserByLogin(const std::string& iLogin);

    myroomies::bom::User createUser(
        myroomies::utils::db::Key_t iLoggedUserId,
        const myroomies::bom::UserNew& iUser);

};

} /* namespace services */
} /* namespace myroomies */
