#pragma once

#include <string>
#include <ctime>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/TableDesc.h>

namespace myroomies {
namespace model {


struct User
{
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
        oUser.id = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::UserTable::kColId);
        oUser.login = iRow.get<std::string>(myroomies::model::UserTable::kColLogin);
        oUser.passwordHash = iRow.get<std::string>(myroomies::model::UserTable::kColPasswordHash);
        oUser.firstname = iRow.get<std::string>(myroomies::model::UserTable::kColFirstname);
        oUser.lastname = iRow.get<std::string>(myroomies::model::UserTable::kColLastname);
        std::string dob = iRow.get<std::string>(myroomies::model::UserTable::kColDateOfBirth);
        oUser.dateOfBirth = boost::gregorian::from_string(dob);
        oUser.email = iRow.get<std::string>(myroomies::model::UserTable::kColEmail);
        oUser.houseshareId = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::UserTable::kColHouseshareId);
    }

    static void to_base(const myroomies::model::User& iUser, values& oRow, indicator oInd)
    {
        oRow.set(myroomies::model::UserTable::kColId, iUser.id);
        oRow.set(myroomies::model::UserTable::kColLogin, iUser.login);
        oRow.set(myroomies::model::UserTable::kColPasswordHash, iUser.passwordHash);
        oRow.set(myroomies::model::UserTable::kColFirstname, iUser.firstname);
        oRow.set(myroomies::model::UserTable::kColLastname, iUser.lastname);
        oRow.set(myroomies::model::UserTable::kColDateOfBirth,
                 boost::gregorian::to_iso_extended_string(iUser.dateOfBirth));
        oRow.set(myroomies::model::UserTable::kColEmail, iUser.email);
        oRow.set(myroomies::model::UserTable::kColHouseshareId, iUser.houseshareId);
        oInd = i_ok;
    }
};
} /* namespace soci */
