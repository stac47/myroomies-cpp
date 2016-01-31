#pragma once

#include <myroomies/model/User.h>

#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>

namespace myroomies {
namespace bom {

using myroomies::model::User;

template class Marshaller<User>;

} /* namespace bom */
} /* namespace myroomies */
