#pragma once

#include <myroomies/model/User.h>

#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>

namespace myroomies {
namespace bom {

struct User
{
    myroomies::model::User user;
    std::string password;
};

template class Marshaller<User>;
template class Unmarshaller<User>;

} /* namespace bom */
} /* namespace myroomies */
