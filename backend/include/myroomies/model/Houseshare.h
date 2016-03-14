#pragma once

#include <string>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

const std::string kTableHouseshare = "houseshare";

struct Houseshare
{
    static const std::string kColId;
    static const std::string kColName;
    static const std::string kColLanguage;

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
        oHouseshare.id = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::Houseshare::kColId);
        oHouseshare.name = iRow.get<std::string>(myroomies::model::Houseshare::kColName);
        oHouseshare.language = iRow.get<std::string>(myroomies::model::Houseshare::kColLanguage);
    }

    static void to_base(const myroomies::model::Houseshare& iHouseshare, values& oRow, indicator oInd)
    {
        oRow.set(myroomies::model::Houseshare::kColId, iHouseshare.id);
        oRow.set(myroomies::model::Houseshare::kColName, iHouseshare.name);
        oRow.set(myroomies::model::Houseshare::kColLanguage, iHouseshare.language);
        oInd = i_ok;
    }
};

} /* namespace soci */
