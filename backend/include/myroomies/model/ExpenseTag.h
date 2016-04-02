#pragma once

#include <string>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/TableDesc.h>

namespace myroomies {
namespace model {

struct ExpenseTag
{
    myroomies::utils::db::Key_t id;
    std::string tag;
};

} /* namespace model */
} /* namespace myroomies */

namespace soci {

template<>
struct type_conversion<myroomies::model::ExpenseTag>
{
    typedef soci::values base_type;

    static void from_base(const values& iRow,
                           indicator iInd ,
                           myroomies::model::ExpenseTag& oExpenseTag)
    {
        oExpenseTag.id = iRow.get<myroomies::utils::db::Key_t>(myroomies::model::ExpenseTagTable::kColId);
        oExpenseTag.tag = iRow.get<std::string>(myroomies::model::ExpenseTagTable::kColTag);
    }

    static void to_base(const myroomies::model::ExpenseTag& iExpenseTag, values& oRow, indicator oInd)
    {
        oRow.set(myroomies::model::ExpenseTagTable::kColId, iExpenseTag.id);
        oRow.set(myroomies::model::ExpenseTagTable::kColTag, iExpenseTag.tag);
        oInd = i_ok;
    }
};

} /* namespace soci */
