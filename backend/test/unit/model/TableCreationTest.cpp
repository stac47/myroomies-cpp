#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <soci/soci.h>

#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/model/Expense.h>

using myroomies::model::kTableHouseshare;
using myroomies::model::Houseshare;
using myroomies::model::User;
using myroomies::model::Expense;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(TableCreation)
{
    boost::filesystem::path dbFile = "myroomies-test.db3";
    myroomies::model::CreateTables(dbFile.c_str(), true);

    soci::session sql("sqlite3", dbFile.c_str());

    sql << "INSERT INTO " << kTableHouseshare
        << "(" << Houseshare::kColName << "," << Houseshare::kColLanguage << ")"
        << "VALUES (\"Houseshare Name\", \"FR\")";

    Houseshare houseshare;
    sql << "SELECT * FROM " << kTableHouseshare,
        soci::into(houseshare.id),
        soci::into(houseshare.name),
        soci::into(houseshare.language);

    BOOST_CHECK(!houseshare.name.empty());
    BOOST_CHECK_EQUAL("FR", houseshare.language);

    boost::filesystem::remove(dbFile);
}

BOOST_AUTO_TEST_SUITE_END()

