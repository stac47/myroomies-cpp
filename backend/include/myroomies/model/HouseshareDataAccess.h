#pragma once

#include <string>
#include <memory>

#include <myroomies/model/Houseshare.h>
#include <myroomies/model/Common.h>
#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

class HouseshareDataAccess : public DataAccess
{
public:
    HouseshareDataAccess(const std::string& iDatabase);

    // Create
    Houseshare createHouseshare(const std::string& iName,
                                const std::string& iLanguage);

    // Retrieve
    std::unique_ptr<Houseshare> getHouseshareById(
        myroomies::utils::db::Key_t iId);
};

} /* namespace model */
} /* namespace myroomies */
