#pragma once

#include <string>

#include <boost/serialization/optional.hpp>
#include <boost/serialization/nvp.hpp>

#include <myroomies/model/User.h>

#include <boost/date_time/gregorian/greg_serialize.hpp>

namespace myroomies {
namespace bom {

struct User final : public myroomies::model::User
{
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

struct UserNew final : public myroomies::model::User
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
