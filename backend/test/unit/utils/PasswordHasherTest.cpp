#include <string>

#include <boost/test/unit_test.hpp>

#include <myroomies/utils/PasswordHasher.h>

BOOST_AUTO_TEST_SUITE(PasswordHasherTest)

BOOST_AUTO_TEST_CASE(HashAndCheck)
{
    myroomies::utils::PasswordHasher hasher;

    const std::string password = "WonderfullPassword";
    std::string mcf;
    BOOST_REQUIRE(hasher.hash(password, mcf));
    BOOST_TEST_MESSAGE("MCF: " << mcf);
    BOOST_CHECK(!hasher.check("WrongPassword", mcf));
    BOOST_CHECK(hasher.check(password, mcf));
}

BOOST_AUTO_TEST_SUITE_END()
