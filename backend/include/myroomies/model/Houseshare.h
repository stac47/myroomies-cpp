#pragma once

#include <string>

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
