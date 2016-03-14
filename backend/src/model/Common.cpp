#include <string>
#include <exception>

#include <boost/filesystem.hpp>

#include <soci/soci.h>

#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/Expense.h>
#include <myroomies/model/User.h>
#include <myroomies/utils/LoggingMacros.h>

using soci::session;

using myroomies::model::kTableHouseshare;
using myroomies::model::kTableUser;
using myroomies::model::kTableExpense;
using myroomies::model::kColRowId;

using myroomies::model::Houseshare;
using myroomies::model::User;
using myroomies::model::Expense;

namespace {

void CreateTablesImpl(const std::string& iPath)
{
    session sql("sqlite3", iPath);
    sql << "CREATE TABLE IF NOT EXISTS language ("
        << "lang TEXT PRIMARY KEY,"
        << "description TEXT NOT NULL)";

    sql << "INSERT INTO language VALUES (\"FR\", \"french\")";
    sql << "INSERT INTO language VALUES (\"EN\", \"english\")";

    sql << "CREATE TABLE IF NOT EXISTS " << kTableHouseshare << " ("
        << Houseshare::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << Houseshare::kColName << " TEXT NOT NULL,"
        << Houseshare::kColLanguage << " TEXT,"
        << "FOREIGN KEY (" << Houseshare::kColLanguage << ") REFERENCES language (lang)"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << kTableUser << " ("
        << Houseshare::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << User::kColLogin << " TEXT NOT NULL UNIQUE,"
        << User::kColPasswordHash << " TEXT NOT NULL,"
        << User::kColFirstname << " TEXT NOT NULL,"
        << User::kColLastname << " TEXT NOT NULL,"
        << User::kColDateOfBirth << " TEXT NOT NULL,"
        << User::kColEmail << " TEXT NOT NULL,"
        << User::kColHouseshareId << " INTEGER,"
        << "FOREIGN KEY (" << User::kColHouseshareId << ") "
            << "REFERENCES " << kTableHouseshare << " (" << kColRowId << ")"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS " << kTableExpense << " ("
        << Houseshare::kColId << " INTEGER PRIMARY KEY AUTOINCREMENT,"
        << Expense::kColUserId << " INTEGER,"
        << Expense::kColHouseshareId << " INTEGER,"
        << Expense::kColDate << " TEXT NOT NULL,"
        << Expense::kColAmount << " REAL NOT NULL,"
        << Expense::kColTitle << " TEXT NOT NULL,"
        << Expense::kColComment << " TEXT,"
        << "FOREIGN KEY (" << Expense::kColUserId << ") "
            << "REFERENCES " << kTableUser << "(" << kColRowId << "),"
        << "FOREIGN KEY (" << Expense::kColHouseshareId << ") "
            << "REFERENCES " << kTableHouseshare << "(" << kColRowId << ")"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS tag ("
        << "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        << "name TEXT NOT NULL,"
        << "lang TEXT NOt NULL,"
        << "FOREIGN KEY (lang) REFERENCES language(lang)"
        << ")";

    sql << "CREATE TABLE IF NOT EXISTS expense_tag ("
        << "expense_id INTEGER,"
        << "tag_id INTEGER,"
        << "FOREIGN KEY (expense_id) REFERENCES " << kTableExpense << "(" << Expense::kColId << "),"
        << "FOREIGN KEY (tag_id) REFERENCES tag(id)"
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
