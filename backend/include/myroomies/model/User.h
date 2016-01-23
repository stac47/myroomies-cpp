#pragma once

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/model/ModelObject.h>

namespace myroomies {
namespace model {

struct User
{
    Key_t id;
    std::string login;
    std::string firstname;
    std::string lastname;
    boost::gregorian::date dateOfBirth;
    std::string email;
    ForeignKey_t houseshareId;
};

} /* namespace model */
} /* namespace myroomies */
