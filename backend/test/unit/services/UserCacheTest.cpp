#include <chrono>
#include <thread>

#include <boost/test/unit_test.hpp>

#include <myroomies/model/User.h>

#include "../../../src/services/UserCache.h"

BOOST_AUTO_TEST_SUITE(UserCacheTest)

using myroomies::services::UserCache;
using myroomies::model::User;

BOOST_AUTO_TEST_CASE(UserCaching)
{
    UserCache cache(std::chrono::seconds(2));
    User user1;
    user1.id = 1;
    user1.login = "login1";
    BOOST_CHECK(!cache.check("toto"));
    cache.push(user1);
    BOOST_CHECK(cache.check(user1.login));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    BOOST_CHECK(!cache.check(user1.login));
}

BOOST_AUTO_TEST_SUITE_END()
