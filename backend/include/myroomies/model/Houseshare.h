#pragma once

#include <string>

#include <myroomies/utils/db/Def.h>

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
