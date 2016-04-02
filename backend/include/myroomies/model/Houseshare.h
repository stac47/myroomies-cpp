#pragma once

#include <string>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/TableDesc.h>

namespace myroomies {
namespace model {


struct Houseshare
{
    myroomies::utils::db::Key_t id;
    std::string name;
    std::string language;
};

} /* namespace model */
} /* namespace myroomies */

namespace soci {

template<>
struct type_conversion<myroomies::model::Houseshare>
{
    typedef soci::values base_type;

    static void from_base(const values& iRow,
                           indicator iInd ,
                           myroomies::model::Houseshare& oHouseshare)
    {
        oHouseshare.id = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::HouseshareTable::kColId);
        oHouseshare.name = iRow.get<std::string>(myroomies::model::HouseshareTable::kColName);
        oHouseshare.language = iRow.get<std::string>(myroomies::model::HouseshareTable::kColLanguage);
    }

    static void to_base(const myroomies::model::Houseshare& iHouseshare, values& oRow, indicator oInd)
    {
        oRow.set(myroomies::model::HouseshareTable::kColId, iHouseshare.id);
        oRow.set(myroomies::model::HouseshareTable::kColName, iHouseshare.name);
        oRow.set(myroomies::model::HouseshareTable::kColLanguage, iHouseshare.language);
        oInd = i_ok;
    }
};

} /* namespace soci */
