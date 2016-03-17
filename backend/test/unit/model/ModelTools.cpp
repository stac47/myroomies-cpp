#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>

#include "ModelTools.h"

using myroomies::utils::db::Key_t;
using myroomies::utils::BuildSimpleCompositeString;

namespace myroomies {
namespace model {

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::vector<Houseshare> ret;
    for (unsigned int i=0; i<iNumber; ++i)
    {
        Houseshare h;
        h.name = BuildSimpleCompositeString("Houseshare name", i);
        h.language = i % 2 == 0 ? "FR" : "EN";
        ret.push_back(h);
    }
    return ret;
}

std::vector<User> BuildUsers(unsigned int iNumber, Key_t iHouseshareId)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::vector<User> ret;
    auto compositeString =
        [iHouseshareId] (const std::string& s, unsigned int i)
        {return BuildSimpleCompositeString(s, iHouseshareId, i);};
    for (unsigned int i=0; i<iNumber; ++i)
    {
        User u;
        u.login = compositeString("login", i);
        u.passwordHash = compositeString("pass", i);
        u.firstname = compositeString("firstname", i);
        u.lastname = compositeString("lastname", i);
        u.dateOfBirth = boost::gregorian::date(2002 + i, 1, 12);
        u.email = compositeString("email", i);
        u.houseshareId = iHouseshareId;
        ret.push_back(u);
    }
    return ret;
}

} /* namespace model */
} /* namespace myroomies */
