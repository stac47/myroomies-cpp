#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/nvp.hpp>

#include <gtest/gtest.h>

#include <myroomies/bom/User.h>
#include <myroomies/utils/json/JsonOutputArchive.h>

using myroomies::bom::User;
using myroomies::utils::json::JsonOutputArchive;

struct UserConsoliatedData
{
    User user;
    int age;
    std::vector<int> hobbies;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(user)
           & BOOST_SERIALIZATION_NVP(age)
           & BOOST_SERIALIZATION_NVP(hobbies);
    }
};

TEST(JsonSerializationTest, MarshallingSimbleObjectSuccess)
{
    User user;
    user.id = 12;
    user.login = "user1_login";
    user.firstname = "user1_firstname";
    user.lastname = "user1_lastname";
    user.dateOfBirth = boost::gregorian::date(1981, 6, 19);
    user.email = "user1@host.com";
    user.houseshareId = 1;

    std::ostringstream os;
    JsonOutputArchive ar{os};

    ar & user;

    std::cout << os.str() << std::endl;
}

TEST(JsonSerializationTest, MarshallingNestedObjectSuccess)
{
    User user;
    user.id = 12;
    user.login = "user1_login";
    user.firstname = "user1_firstname";
    user.lastname = "user1_lastname";
    user.dateOfBirth = boost::gregorian::date(1981, 6, 19);
    user.email = "user1@host.com";
    user.houseshareId = 1;

    UserConsoliatedData ucd;
    ucd.user = user;
    ucd.age = 34;
    /* ucd.hobbies = {"cycling", "C++"}; */
    ucd.hobbies = {1, 2, 3};

    std::ostringstream os;
    JsonOutputArchive ar{os};

    ar & ucd;

    std::cout << os.str() << std::endl;
}
