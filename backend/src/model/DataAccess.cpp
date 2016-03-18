#include <string>
#include <memory>

#include <soci/soci.h>

#include <myroomies/model/DataAccess.h>
#include <myroomies/utils/LoggingMacros.h>

namespace {

std::unique_ptr<soci::connection_pool> Pool;

} /* namespace  */

namespace myroomies {
namespace model {

void DataAccess::ConfigureConnectionPool(
    std::size_t iPoolSize,
    const std::string& iDatabase)
{
    if (Pool == nullptr)
    {
        MYROOMIES_LOG_INFO("Configuring database connection pool");
    }
    else
    {
        MYROOMIES_LOG_INFO("Reconfiguring database connection pool " << Pool.get());
    }
    Pool.reset(new soci::connection_pool(iPoolSize));
    for (std::size_t i = 0; i < iPoolSize; ++i)
    {
        soci::session& sql = Pool->at(i);
        sql.open("sqlite3", iDatabase.c_str());
        sql.once << "PRAGMA foreign_keys = ON";
    }
    MYROOMIES_LOG_INFO("Database connection pool ready: " << Pool.get());
}

DataAccess::DataAccess()
  : session_(*Pool)
{}

DataAccess::~DataAccess()
{}

soci::session& DataAccess::getSession()
{
    return session_;
}

} /* namespace model */
} /* namespace myroomies */

