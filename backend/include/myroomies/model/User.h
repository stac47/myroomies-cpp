#pragma once

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

struct User
{
    myroomies::utils::db::Key_t id;
    std::string login;
    std::string firstname;
    std::string lastname;
    boost::gregorian::date dateOfBirth;
    std::string email;
    myroomies::utils::db::ForeignKey_t houseshareId;
};

} /* namespace model */
} /* namespace myroomies */
