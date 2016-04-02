#include <string>
#include <exception>

#include <boost/filesystem.hpp>

#include <soci/soci.h>

#include <myroomies/model/Common.h>
#include <myroomies/model/TableDesc.h>
#include <myroomies/utils/LoggingMacros.h>

using soci::session;

using myroomies::model::HouseshareTable;
using myroomies::model::UserTable;
using myroomies::model::ExpenseTable;
using myroomies::model::ExpenseTagTable;
using myroomies::model::ExpenseTagJoinTable;

namespace {

void CreateTablesImpl(const std::string& iPath)
{
    session sql("sqlite3", iPath);

    sql << "CREATE TABLE IF NOT EXISTS language ("
        << "lang TEXT PRIMARY KEY,"
        << "description TEXT NOT NULL)";

    sql << "INSERT INTO language VALUES (\"FR\", \"french\")";
    sql << "INSERT INTO language VALUES (\"EN\", \"english\")";

    sql << "CREATE TABLE IF NOT EXISTS " << HouseshareTable::kName << " ("
        << HouseshareTable::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << HouseshareTable::kColName << " TEXT NOT NULL,"
        << HouseshareTable::kColLanguage << " TEXT,"
        << "FOREIGN KEY (" << HouseshareTable::kColLanguage << ") REFERENCES language (lang)"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << UserTable::kName << " ("
        << UserTable::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << UserTable::kColLogin << " TEXT NOT NULL UNIQUE,"
        << UserTable::kColPasswordHash << " TEXT NOT NULL,"
        << UserTable::kColFirstname << " TEXT NOT NULL,"
        << UserTable::kColLastname << " TEXT NOT NULL,"
        << UserTable::kColDateOfBirth << " TEXT NOT NULL,"
        << UserTable::kColEmail << " TEXT NOT NULL,"
        << UserTable::kColHouseshareId << " INTEGER,"
        << "FOREIGN KEY (" << UserTable::kColHouseshareId << ") "
            << "REFERENCES " << HouseshareTable::kName << " (" << HouseshareTable::kColId << ")"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << ExpenseTable::kName << " ("
        << ExpenseTable::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << ExpenseTable::kColUserId << " INTEGER,"
        << ExpenseTable::kColDate << " TEXT NOT NULL,"
        << ExpenseTable::kColAmount << " REAL NOT NULL,"
        << ExpenseTable::kColTitle << " TEXT NOT NULL,"
        << ExpenseTable::kColComment << " TEXT,"
        << "FOREIGN KEY (" << ExpenseTable::kColUserId << ") "
            << "REFERENCES " << UserTable::kName << "(" << UserTable::kColId << ")"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << ExpenseTagTable::kName << " ("
        << ExpenseTagTable::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << ExpenseTagTable::kColTag << " TEXT NOT NULL UNIQUE"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << ExpenseTagJoinTable::kName << " ("
        << ExpenseTagJoinTable::kColExpenseId << " INTEGER,"
        << ExpenseTagJoinTable::kColExpenseTagId << " INTEGER,"
        << "FOREIGN KEY (" << ExpenseTagJoinTable::kColExpenseId << ") "
            << "REFERENCES " << ExpenseTable::kName << "(" << ExpenseTable::kColId << ") ON DELETE CASCADE,"
        << "FOREIGN KEY (" << ExpenseTagJoinTable::kColExpenseTagId << ") "
            << "REFERENCES " << ExpenseTagTable::kName << "(" << ExpenseTagTable::kColId << ")"
        << ")";
}

} /* namespace  */

namespace myroomies {
namespace model {

bool CreateTables(const std::string& iPath, bool iCreateIfNotExsits)
{
    bool ret = true;
    try
    {
        if (iPath == ":memory:")
        {
            MYROOMIES_LOG_INFO("Creating in-memory database");
            CreateTablesImpl(iPath);
            MYROOMIES_LOG_INFO("In-memory database created");
        }
        else
        {
            boost::filesystem::path dbPath = iPath;
            if (!boost::filesystem::exists(dbPath))
            {
                if (iCreateIfNotExsits)
                {
                    MYROOMIES_LOG_INFO("Creating database into: " << iPath);
                    CreateTablesImpl(iPath);
                    MYROOMIES_LOG_INFO("File database created");
                }
                else
                {
                    MYROOMIES_LOG_ERROR("The database ["
                        << iPath << "] does not exist. To force the creation"
                        << " use the --db-create option.");
                    ret = false;
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        MYROOMIES_LOG_ERROR("Error during table creation: " << e.what());
        ret = false;
    }
    return ret;
}

} /* namespace model */
} /* namespace myroomies */
