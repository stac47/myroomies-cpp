#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <soci/soci.h>

#include <myroomies/model/User.h>
#include <myroomies/model/UserDataAccess.h>

#include "ModelTools.h"

using myroomies::model::User;
using myroomies::model::UserDataAccess;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(UserDataAccessTest)
{
    boost::filesystem::path dbFile = "myroomies-test.db3";
    boost::filesystem::remove(dbFile);
    myroomies::model::CreateTables(dbFile.c_str(), true);

    auto users = myroomies::model::BuildUsers(2u, 1);

    UserDataAccess dao(dbFile.c_str());

    int count = 0;
    for (auto u : users)
    {
        ++count;
        auto createdUser = dao.createUser(u);
        BOOST_CHECK_EQUAL(createdUser.id, count);
    }

    BOOST_CHECK_EQUAL(2, count);

    // Retrieve by login
    auto user = dao.getUserFromLogin(users[0].login);
    BOOST_CHECK_EQUAL(user->login, users[0].login);

    // Retrieve all the users from the same houseshare
    auto retUsers = dao.getUsersFromHouseshare(1);
    BOOST_CHECK_EQUAL(2u, retUsers.size());

}

BOOST_AUTO_TEST_SUITE_END()


