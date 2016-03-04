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

using myroomies::model::Houseshare;

template<>
struct type_conversion<Houseshare>
{
    typedef values base_type;

    static void from_base(const values& iRow,
                           indicator iInd ,
                           Houseshare& oHouseshare)
    {
        oHouseshare.id = iRow.get<uint64_t>(Houseshare::kColId);
        oHouseshare.name = iRow.get<std::string>(Houseshare::kColName);
        oHouseshare.language = iRow.get<std::string>(Houseshare::kColLanguage);
    }

    static void to_base(const Houseshare& iHouseshare, values& oRow, indicator oInd)
    {
        oRow.set(Houseshare::kColId, iHouseshare.id);
        oRow.set(Houseshare::kColName, iHouseshare.name);
        oRow.set(Houseshare::kColLanguage, iHouseshare.language);
        oInd = i_ok;
    }
};

} /* namespace soci */
