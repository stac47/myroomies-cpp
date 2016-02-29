#include <string>
#include <vector>
#include <sstream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/model/Expense.h>

using myroomies::model::kTableHouseshare;
using myroomies::model::kTableUser;
using myroomies::model::kTableExpense;
using myroomies::model::kColRowId;
using myroomies::model::Houseshare;
using myroomies::model::User;
using myroomies::model::Expense;
using myroomies::utils::db::Key_t;

namespace {

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::ostringstream os;
    std::vector<Houseshare> ret;
    for (unsigned int i=0; i<iNumber; ++i)
    {
        Houseshare h;
        os << "Houseshare name " << i;
        h.name = os.str();
        h.language = i % 2 == 0 ? "FR" : "EN";
        ret.push_back(h);
    }
    return ret;
}

std::vector<User> BuildUsers(unsigned int iNumber, Key_t iHouseshareId)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::ostringstream os;
    std::vector<User> ret;
    for (unsigned int i=0; i<iNumber; ++i)
    {
        User u;
        os << "login" << i;
        u.login = os.str();
        os << "pass" << i;
        u.passwordHash = os.str();
        os << "firstname" << i;
        u.firstname = os.str();
        os << "lastname" << i;
        u.lastname = os.str();
        u.dateOfBirth = boost::gregorian::date(2002 + i, 1, 12);
        os << "email" << i;
        u.email = os.str();
        u.houseshareId = iHouseshareId;
        ret.push_back(u);
    }
    return ret;
}


} /* namespace  */

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(TableCreation)
{
    boost::filesystem::path dbFile = "myroomies-test.db3";
    /* boost::filesystem::remove(dbFile); */
    myroomies::model::CreateTables(dbFile.c_str(), true);

    soci::session sql("sqlite3", dbFile.c_str());

    auto houseshares = BuildHouseshares(1);

    sql << "INSERT INTO " << kTableHouseshare
        << "(" << Houseshare::kColName << "," << Houseshare::kColLanguage << ")"
        << "VALUES (:name, :lang)",
        soci::use(houseshares[0].name, "name"),
        soci::use(houseshares[0].language, "lang");

    Houseshare houseshare;
    sql << "SELECT rowid, name, language FROM " << kTableHouseshare,
        soci::into(houseshare.id),
        soci::into(houseshare.name),
        soci::into(houseshare.language);

    BOOST_CHECK(!houseshare.name.empty());
    BOOST_CHECK_EQUAL(houseshares[0].name, houseshare.name);
    BOOST_CHECK_EQUAL(houseshares[0].language, houseshare.language);

    auto users = BuildUsers(2, houseshare.id);
    for (User u : users)
    {
        sql << "INSERT INTO " << kTableUser << " VALUES ("
            << ":login, :pass, :fn, :ln, :dob, :email, :hid)",
            soci::use(u.login, "login"),
            soci::use(u.passwordHash, "pass"),
            soci::use(u.firstname, "fn"),
            soci::use(u.lastname, "ln"),
            soci::use(boost::gregorian::to_simple_string(u.dateOfBirth), "dob"),
            soci::use(u.email, "email"),
            soci::use(u.houseshareId, "hid");
    }
}

BOOST_AUTO_TEST_SUITE_END()

