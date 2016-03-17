#pragma once

#include <string>
#include <ctime>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

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

namespace soci {

template<>
struct type_conversion<myroomies::model::User>
{
    typedef soci::values base_type;

    static void from_base(const values& iRow,
                           indicator iInd ,
                           myroomies::model::User& oUser)
    {
        oUser.id = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::User::kColId);
        oUser.login = iRow.get<std::string>(myroomies::model::User::kColLogin);
        oUser.passwordHash = iRow.get<std::string>(myroomies::model::User::kColPasswordHash);
        oUser.firstname = iRow.get<std::string>(myroomies::model::User::kColFirstname);
        oUser.lastname = iRow.get<std::string>(myroomies::model::User::kColLastname);
        std::string dob = iRow.get<std::string>(myroomies::model::User::kColDateOfBirth);
        oUser.dateOfBirth = boost::gregorian::from_string(dob);
        oUser.email = iRow.get<std::string>(myroomies::model::User::kColEmail);
        oUser.houseshareId = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::User::kColHouseshareId);
    }

    static void to_base(const myroomies::model::User& iUser, values& oRow, indicator oInd)
    {
        oRow.set(myroomies::model::User::kColId, iUser.id);
        oRow.set(myroomies::model::User::kColLogin, iUser.login);
        oRow.set(myroomies::model::User::kColPasswordHash, iUser.passwordHash);
        oRow.set(myroomies::model::User::kColFirstname, iUser.firstname);
        oRow.set(myroomies::model::User::kColLastname, iUser.lastname);
        oRow.set(myroomies::model::User::kColDateOfBirth,
                 boost::gregorian::to_iso_extended_string(iUser.dateOfBirth));
        oRow.set(myroomies::model::User::kColEmail, iUser.email);
        oRow.set(myroomies::model::User::kColHouseshareId, iUser.houseshareId);
        oInd = i_ok;
    }
};
} /* namespace soci */
