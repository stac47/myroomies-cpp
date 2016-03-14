#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>

namespace myroomies {
namespace model {

class BuildCompositeStringHelper
{
public:
    std::string operator()()
    {
        return "";
    }

    template<typename T, typename ... Args>
    std::string operator()(T&& s, Args&&... args)
    {
        os_ << std::forward<T>(s);
        (*this)(std::forward<Args>(args)...);
        return os_.str();
    }

private:
    std::ostringstream os_;
};

template<typename T, typename ... Args>
std::string BuildCompositeString(T&& s, Args&&... args)
{
    return BuildCompositeStringHelper()(std::forward<T>(s), std::forward<Args>(args)...);
}

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber);

std::vector<User> BuildUsers(
    unsigned int iNumber, myroomies::utils::db::Key_t iHouseshareId);

} /* namespace model */
} /* namespace myroomies */
