#pragma once

#include <vector>

#include <myroomies/bom/User.h>

namespace myroomies {
namespace services {

class UserService
{
public:
    UserService();

    std::vector<myroomies::bom::User> getUsers() const;

};
} /* namespace services */
} /* namespace myroomies */
