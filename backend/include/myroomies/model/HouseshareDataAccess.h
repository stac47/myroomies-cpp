#pragma once

#include <string>
#include <memory>

#include <myroomies/model/Houseshare.h>
#include <myroomies/model/DataAccess.h>
#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

class HouseshareDataAccess : public DataAccess
{
public:
    // Create
    Houseshare createHouseshare(const Houseshare& iNewHouseshare);

    // Retrieve
    std::unique_ptr<Houseshare> getHouseshareById(
        myroomies::utils::db::Key_t iId);
};

} /* namespace model */
} /* namespace myroomies */
