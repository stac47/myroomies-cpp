#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/PasswordHasher.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/User.h>

#include <myroomies/model/User.h>
#include <myroomies/model/UserDataAccess.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/HouseshareDataAccess.h>

#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/Exception.h>
#include <myroomies/services/UserService.h>

using myroomies::utils::Configuration;
using myroomies::utils::db::Key_t;
using myroomies::bom::UserNew;
using myroomies::bom::User;
using myroomies::model::UserDataAccess;
using myroomies::model::Houseshare;
using myroomies::model::HouseshareDataAccess;

namespace {

myroomies::model::User ToModel(const myroomies::bom::User& iUser)
{
    myroomies::model::User user;
    user.id = iUser.id;
    user.login = iUser.login;
    user.firstname = iUser.firstname;
    user.lastname = iUser.lastname;
    user.dateOfBirth = iUser.dateOfBirth;
    user.email = iUser.email;
    user.houseshareId = iUser.houseshareId;
    return user;
}

User FromModel(const myroomies::model::User& iUser)
{
    User user;
    user.id = iUser.id;
    user.login = iUser.login;
    user.firstname = iUser.firstname;
    user.lastname = iUser.lastname;
    user.dateOfBirth = iUser.dateOfBirth;
    user.email = iUser.email;
    user.houseshareId = iUser.houseshareId;
    return user;
}

} /* namespace  */
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

User UserService::createAdmin(const std::string& iPassword)
{
    // A user must be part of a houseshare. Let us create a fake houseshare for
    // the admin
    Houseshare houseshare;
    houseshare.name = "admin-houseshare";
    houseshare.language = "EN";
    HouseshareDataAccess houseshareDao;
    Key_t id = houseshareDao.createHouseshare(houseshare).id;

    // Create the admin user
    myroomies::model::User admin;
    admin.login = "admin";
    admin.houseshareId = id;
    admin.dateOfBirth = boost::gregorian::date(1981, 6, 19);
    myroomies::utils::PasswordHasher hasher;
    hasher.hash(iPassword, admin.passwordHash);
    UserDataAccess userDao;
    return FromModel(userDao.createUser(admin));
}

User UserService::createUser(Key_t iLoggedUser, const UserNew& iUser)
{
    if (iLoggedUser != 1)
    {
        MYROOMIES_LOG_WARN("User [id=" << iLoggedUser << "] "
                           << "tried to create a new user "
                           << "[login=" << iUser.login << "]");
        throw myroomies::services::ForbiddenResourceException();
    }
    myroomies::model::User u = ToModel(iUser);

    myroomies::utils::PasswordHasher hasher;
    hasher.hash(iUser.password, u.passwordHash);

    UserDataAccess dao;
    auto createdUser = dao.createUser(u);
    User result = FromModel(createdUser);
    MYROOMIES_LOG_INFO("User " << result.login << "[id=" << result.id << "]"
                       << " has been created.");
    return result;
}

std::vector<User> UserService::getUsersFromHouseshare(Key_t iHouseshareId) const
{
    std::vector<User> v;
    UserDataAccess dao;
    for (auto user : dao.getUsersFromHouseshare(iHouseshareId))
    {
        const User u = FromModel(user);
        v.push_back(u);
    }

    return v;
}

User UserService::getUserByLogin(const std::string& iLogin)
{
    UserDataAccess dao;
    auto userPtr = dao.getUserFromLogin(iLogin);
    User u;
    if (userPtr)
    {
        u = FromModel(*userPtr);
    }
    else
    {
        throw ResourceNotFoundException();
    }
    return u;
}

std::unique_ptr<const User> UserService::login(
    const std::string& iLogin,
    const std::string& iPassword)
{
    UserDataAccess dao;
    auto userPtr = dao.getUserFromLogin(iLogin);
    std::unique_ptr<const User> ret;
    if (userPtr)
    {
        myroomies::utils::PasswordHasher hasher;
        if (hasher.check(iPassword, userPtr->passwordHash))
        {
            ret = std::make_unique<const User>(FromModel(*userPtr));
        }
    }
    else
    {
        MYROOMIES_LOG_WARN("User provided wrong credentials ["
                           << iLogin << ":" << iPassword << "]");
    }
    MYROOMIES_LOG_INFO("User [id=" << ret->id << "] logged in  MyRoomies");
    return ret;
}

} /* namespace services */
} /* namespace myroomies */
