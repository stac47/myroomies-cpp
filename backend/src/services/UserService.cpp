#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/User.h>
#include <myroomies/model/User.h>

#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/UserService.h>

using myroomies::utils::Configuration;
using myroomies::utils::db::Key_t;

using UserBom = myroomies::bom::User;
using myroomies::model::User;

namespace {

std::vector<User>& GetAllUsers()
{
    static std::vector<User> Users;
    return Users;
}

} /* namespace */

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

UserBom UserService::createUser(const UserBom& iUser)
{
    const User& u = iUser.user;
    GetAllUsers().push_back(u);
    UserBom ub = {u, ""};
    return ub;
}

std::vector<UserBom> UserService::getUsersFromHouseshare(Key_t iHouseshareId) const
{
    std::vector<UserBom> v;
    for (const User& u : GetAllUsers())
    {
        if (u.houseshareId == iHouseshareId)
        {
            UserBom ub = {u, ""};
            v.push_back(ub);
        }
    }
    return v;
}

} /* namespace services */
} /* namespace myroomies */
