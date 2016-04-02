#include <string>
#include <memory>

#include <soci/soci.h>

#include <myroomies/model/Houseshare.h>
#include <myroomies/model/TableDesc.h>
#include <myroomies/model/Common.h>
#include <myroomies/utils/db/Def.h>
#include <myroomies/utils/db/SqlTools.h>

#include <myroomies/model/HouseshareDataAccess.h>

using soci::session;
using soci::statement;
using soci::use;
using soci::into;

using myroomies::model::Houseshare;
using myroomies::model::HouseshareTable;

namespace {

namespace db = myroomies::utils::db;

const std::string kHouseshareInsert =
    db::GenerateInsertTemplate(HouseshareTable::kName,
                               HouseshareTable::kColName,
                               HouseshareTable::kColLanguage);

const std::string kHouseshareRetrieveById =
    db::GenerateSimpleSelectTemplate(HouseshareTable::kName,
                                     HouseshareTable::kColId);

} /* namespace  */

namespace myroomies {
namespace model {

Houseshare HouseshareDataAccess::createHouseshare(const Houseshare& iNewHouseshare)
{
    getSession() << kHouseshareInsert, use(iNewHouseshare);
    Houseshare houseshare = iNewHouseshare;
    long id;
    getSession().get_last_insert_id(HouseshareTable::kName, id);
    houseshare.id = static_cast<int>(id);
    return houseshare;
}

std::unique_ptr<Houseshare> HouseshareDataAccess::getHouseshareById(
    myroomies::utils::db::Key_t iId)
{
    Houseshare houseshare;
    getSession() << kHouseshareRetrieveById, into(houseshare), use(iId);
    return std::move(std::make_unique<Houseshare>(houseshare));
}

} /* namespace model */
} /* namespace myroomies */
