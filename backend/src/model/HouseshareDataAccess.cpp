#include <string>
#include <memory>

#include <boost/format.hpp>

#include <soci/soci.h>

#include <myroomies/model/Houseshare.h>
#include <myroomies/model/Common.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/model/HouseshareDataAccess.h>

namespace {
    
} /* namespace  */

namespace myroomies {
namespace model {

HouseshareDataAccess::HouseshareDataAccess(const std::string& iDatabase)
  : DataAccess(iDatabase)
{}

Houseshare HouseshareDataAccess::createHouseshare(const std::string& iName,
                            const std::string& iLanguage)
{
    Houseshare ret;
    return ret;
}

std::unique_ptr<Houseshare> HouseshareDataAccess::getHouseshareById(
    myroomies::utils::db::Key_t iId)
{
    return std::make_unique<Houseshare>();
}

} /* namespace model */
} /* namespace myroomies */
