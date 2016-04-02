#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/model/Expense.h>

#include "ModelTools.h"

using myroomies::model::Houseshare;
using myroomies::model::User;
using myroomies::model::Expense;
using myroomies::model::HouseshareTable;
using myroomies::model::UserTable;
using myroomies::model::ExpenseTable;
using myroomies::utils::db::Key_t;
using myroomies::model::BuildUsers;
using myroomies::model::BuildHouseshares;

using soci::row;
using soci::statement;
using soci::use;
using soci::into;
using soci::rowset;
using soci::session;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(TableCreation)
{
    boost::filesystem::path dbFile = "myroomies-test.db3";
    boost::filesystem::remove(dbFile);
    myroomies::model::CreateTables(dbFile.c_str(), true);

    session sql("sqlite3", dbFile.c_str());

    auto houseshares = BuildHouseshares(1);

    std::string insertHouseshare =
        boost::str(boost::format("INSERT INTO %1%(%2%, %3%) VALUES(:%2%,:%3%)")
                   % HouseshareTable::kName
                   % HouseshareTable::kColName
                   % HouseshareTable::kColLanguage);
    sql << insertHouseshare, use(houseshares[0]);

    long id = 0;
    sql.get_last_insert_id(HouseshareTable::kName, id);
    BOOST_CHECK_EQUAL(1L, id);

    Houseshare houseshare;
    statement s = (sql.prepare << "SELECT * FROM " << HouseshareTable::kName << " WHERE id=:id",
                    use(1, "id"),
                    into(houseshare));
    s.execute();

    unsigned int count = 0;
    while (s.fetch())
    {
        ++count;
        BOOST_CHECK(!houseshare.name.empty());
        BOOST_CHECK_EQUAL(1, houseshare.id);
        BOOST_CHECK_EQUAL(static_cast<Key_t>(id), houseshare.id);
        BOOST_CHECK_EQUAL(houseshares[0].name, houseshare.name);
        BOOST_CHECK_EQUAL(houseshares[0].language, houseshare.language);
    }
    BOOST_CHECK_EQUAL(count, 1u);

    std::string insertUser =
        boost::str(boost::format(
                    "INSERT INTO %1%(%2%,%3%,%4%,%5%,%6%,%7%,%8%) "
                    "VALUES(:%2%,:%3%,:%4%,:%5%,:%6%,:%7%,:%8%)")
                   % UserTable::kName
                   % UserTable::kColLogin
                   % UserTable::kColPasswordHash
                   % UserTable::kColFirstname
                   % UserTable::kColLastname
                   % UserTable::kColDateOfBirth
                   % UserTable::kColEmail
                   % UserTable::kColHouseshareId);

    auto users = BuildUsers(2u, houseshare.id);
    for (User u : users)
    {
        sql << insertUser, use(u);
    }
    BOOST_TEST_MESSAGE(UserTable::kName << " is populated with "
                                  << users.size() << " users");

    // Retrieve all the users from the current houseshare
    rowset<row> rs = (sql.prepare
        << "SELECT " << UserTable::kColLogin << ","
                     << UserTable::kColDateOfBirth << " "
        << "FROM " << UserTable::kName<< " "
        << "WHERE " << UserTable::kColHouseshareId << "=" << houseshare.id);
    int userCounter = 0;
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        BOOST_CHECK_EQUAL(users[userCounter].login, it->get<std::string>(0));
        boost::gregorian::date dob = boost::gregorian::from_string(it->get<std::string>(1));
        BOOST_CHECK_EQUAL(users[userCounter].dateOfBirth, dob);
        userCounter++;
    }
    BOOST_CHECK_EQUAL(2, userCounter);

    // Retrieve a user by login
    User user;
    s = (sql.prepare << "SELECT * FROM " << UserTable::kName << " WHERE login=:login",
         use(users[0].login, "login"),
         into(user));
    s.execute(true);
    BOOST_CHECK_EQUAL(users[0].login, user.login);
}

BOOST_AUTO_TEST_SUITE_END()

