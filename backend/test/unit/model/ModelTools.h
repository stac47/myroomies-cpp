#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/utils/StringUtils.h>

namespace myroomies {
namespace model {

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber);

std::vector<User> BuildUsers(
    unsigned int iNumber, myroomies::utils::db::Key_t iHouseshareId);

} /* namespace model */
} /* namespace myroomies */
