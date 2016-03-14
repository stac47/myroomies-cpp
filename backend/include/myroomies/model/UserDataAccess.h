#pragma once

#include <memory>
#include <string>
#include <vector>

#include <myroomies/model/Common.h>
#include <myroomies/model/User.h>
#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

class UserDataAccess : public DataAccess
{
public:
    UserDataAccess(const std::string& iDatabase);

    // Create
    User createUser(const User& iNewUser);

    // Retrieve
    std::vector<User> getUsersFromHouseshare(
        myroomies::utils::db::Key_t iHouseshareId);
    std::unique_ptr<User> getUserFromLogin(const std::string& iLogin);

    // Update
    // Delete
};

} /* namespace model */
} /* namespace myroomies */
