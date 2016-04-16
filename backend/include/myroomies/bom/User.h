#pragma once

#include <string>

#include <boost/serialization/nvp.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace bom {

struct User
{
    myroomies::utils::db::Key_t id;
    std::string login;
    std::string firstname;
    std::string lastname;
    boost::gregorian::date dateOfBirth;
    std::string email;
    myroomies::utils::db::ForeignKey_t houseshareId;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(id)
           & BOOST_SERIALIZATION_NVP(login)
           & BOOST_SERIALIZATION_NVP(firstname)
           & BOOST_SERIALIZATION_NVP(lastname)
           & BOOST_SERIALIZATION_NVP(dateOfBirth)
           & BOOST_SERIALIZATION_NVP(email)
           & BOOST_SERIALIZATION_NVP(houseshareId);
    }
};

struct UserNew final : public User
{
    std::string password;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(login)
           & BOOST_SERIALIZATION_NVP(password)
           & BOOST_SERIALIZATION_NVP(firstname)
           & BOOST_SERIALIZATION_NVP(lastname)
           & BOOST_SERIALIZATION_NVP(dateOfBirth)
           & BOOST_SERIALIZATION_NVP(email)
           & BOOST_SERIALIZATION_NVP(houseshareId);
    }
};

} /* namespace bom */
} /* namespace myroomies */
