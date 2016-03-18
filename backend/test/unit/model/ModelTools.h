#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/model/DataAccess.h>
#include <myroomies/utils/StringUtils.h>

namespace myroomies {
namespace model {

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber);

std::vector<User> BuildUsers(
    unsigned int iNumber, myroomies::utils::db::Key_t iHouseshareId);

const std::string kDefaultDatabaseName = "myroomies-test.db3";

class ModelFixture
{
public:
    ModelFixture()
      : dbFile_(kDefaultDatabaseName)
    {
        boost::filesystem::remove(dbFile_);
        myroomies::model::CreateTables(dbFile_.c_str(), true);
        DataAccess::ConfigureConnectionPool(10, dbFile_.c_str());
    }

    ~ModelFixture()
    {
    }

private:
    boost::filesystem::path dbFile_ = kDefaultDatabaseName;

};

} /* namespace model */
} /* namespace myroomies */
