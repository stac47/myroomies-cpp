#include <string>

#include <boost/test/unit_test.hpp>

#include <soci/soci.h>

#include <myroomies/model/User.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/DataAccess.h>
#include <myroomies/model/UserDataAccess.h>
#include <myroomies/model/HouseshareDataAccess.h>
#include <myroomies/utils/db/Def.h>

#include "ModelTools.h"

using myroomies::model::User;
using myroomies::model::Houseshare;
using myroomies::model::DataAccess;
using myroomies::model::UserDataAccess;
using myroomies::model::HouseshareDataAccess;
using myroomies::model::ModelFixture;
using myroomies::utils::db::Key_t;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_FIXTURE_TEST_CASE(UserDataAccessTest, ModelFixture)
{
    Houseshare houseshare = myroomies::model::BuildHouseshares(1)[0];
    HouseshareDataAccess houseshareDao;
    Key_t houseshareId = houseshareDao.createHouseshare(houseshare).id;

    auto users = myroomies::model::BuildUsers(2u, houseshareId);

    UserDataAccess dao;

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
    BOOST_CHECK_EQUAL(retUsers[0].login, users[0].login);
    BOOST_CHECK_EQUAL(retUsers[1].login, users[1].login);
}

BOOST_AUTO_TEST_SUITE_END()


