#pragma once

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

const std::string kTableUser = "user";

struct User
{
    static const std::string kColId;
    static const std::string kColLogin;
    static const std::string kColPasswordHash;
    static const std::string kColFirstname;
    static const std::string kColLastname;
    static const std::string kColDateOfBirth;
    static const std::string kColEmail;
    static const std::string kColHouseshareId;

    myroomies::utils::db::Key_t id;
    std::string login;
    std::string passwordHash;
    std::string firstname;
    std::string lastname;
    boost::gregorian::date dateOfBirth;
    std::string email;
    myroomies::utils::db::ForeignKey_t houseshareId;
};

} /* namespace model */
} /* namespace myroomies */
