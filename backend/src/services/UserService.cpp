#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/Exception.h>
#include <myroomies/services/UserService.h>

using myroomies::utils::Configuration;
using myroomies::utils::db::Key_t;

using myroomies::bom::User;
using myroomies::bom::UserNew;

namespace {

std::vector<User>& GetAllUsers()
{
    static std::vector<User> Users;
    if (Users.empty())
    {
        User admin;
        admin.id = 0;
        admin.login = "admin";
        admin.passwordHash = "PASSWORDHASH"; // TODO calculate a hashcode
        admin.houseshareId = 0;
        Users.push_back(admin);
    }
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

User UserService::createUser(Key_t iLoggedUser, const UserNew& iUser)
{
    if (iLoggedUser != 0)
    {
        MYROOMIES_LOG_WARN("User [id=" << iLoggedUser << "] "
                           << "tried to create a new user "
                           << "[login=" << iUser.login << "]");
        throw myroomies::services::ForbiddenResourceException();
    }
    User u;
    u.id = GetAllUsers().size() + 1;
    u.login = iUser.login;
    u.passwordHash = iUser.password; // TODO calculate a hashcode
    u.firstname = iUser.firstname;
    u.lastname = iUser.lastname;
    u.dateOfBirth = iUser.dateOfBirth;
    u.email = iUser.email;
    u.houseshareId = iUser.houseshareId;
    GetAllUsers().push_back(u);

    return u;
}

std::vector<User> UserService::getUsersFromHouseshare(Key_t iHouseshareId) const
{
    std::vector<User> v;
    for (const User& u : GetAllUsers())
    {
        if (u.houseshareId == iHouseshareId)
        {
            v.push_back(u);
        }
    }
    return v;
}

User UserService::getUserByLogin(const std::string& iLogin)
{
    auto it = std::find_if(GetAllUsers().begin(), GetAllUsers().end(),
            [&iLogin] (const User& u) {return u.login == iLogin;});
    if (it == std::end(GetAllUsers()))
    {
        throw ResourceNotFoundException();
    }
    return *it;
}

} /* namespace services */
} /* namespace myroomies */
