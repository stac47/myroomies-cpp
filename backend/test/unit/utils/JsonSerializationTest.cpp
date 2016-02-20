#include <string>
#include <functional>
#include <utility>
#include <array>
#include <list>
#include <sstream>
#include <iostream>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/algorithm/string/join.hpp>

#include <gtest/gtest.h>

#include <myroomies/bom/User.h>
#include <myroomies/utils/json/JsonOutputArchive.h>

using myroomies::bom::User;
using myroomies::utils::json::JsonOutputArchive;

namespace  {

struct UserConsolidatedData
{
    User user;
    int age;
    std::vector<std::string> hobbies;
    std::list<double> preferedNumbers;
    int misc[3];
    std::array<int, 3> stdArray;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(user)
           & BOOST_SERIALIZATION_NVP(age)
           & BOOST_SERIALIZATION_NVP(hobbies)
           & BOOST_SERIALIZATION_NVP(preferedNumbers)
           & BOOST_SERIALIZATION_NVP(misc)
           & BOOST_SERIALIZATION_NVP(stdArray);
    }
};

User CreateUser()
{
    User user;
    user.id = 12;
    user.login = "user1_login";
    user.firstname = "user1_firstname";
    user.lastname = "user1_lastname";
    user.dateOfBirth = boost::gregorian::date(1981, 6, 19);
    user.email = "user1@host.com";
    user.houseshareId = 1;
    return user;
}

std::pair<User, std::string> CreateUserExpectationPair()
{
    return {CreateUser(), "{\"id\":12,\"login\":\"user1_login\","
                          "\"firstname\":\"user1_firstname\","
                          "\"lastname\":\"user1_lastname\","
                          "\"dateOfBirth\":\"19810619\","
                          "\"email\":\"user1@host.com\","
                          "\"houseshareId\":1}"};
}

std::pair<UserConsolidatedData, std::string> CreateUserConsolidatedExpectationPair()
{
    UserConsolidatedData ucd;
    ucd.user = CreateUser();
    ucd.age = 34;
    ucd.hobbies = {"cycling", "C++"};
    ucd.preferedNumbers = {2.0, 3.14};
    ucd.misc[0] = 1;
    ucd.misc[1] = 2;
    ucd.misc[2] = 3;
    ucd.stdArray[0] = 1;
    ucd.stdArray[1] = 2;
    ucd.stdArray[2] = 3;
    return {ucd, "{\"user\":{\"id\":12,\"login\":\"user1_login\","
                 "\"firstname\":\"user1_firstname\","
                 "\"lastname\":\"user1_lastname\","
                 "\"dateOfBirth\":\"19810619\","
                 "\"email\":\"user1@host.com\","
                 "\"houseshareId\":1},"
                 "\"age\":34,"
                 "\"hobbies\":[\"cycling\",\"C++\"],"
                 "\"preferedNumbers\":[2.0,3.14],"
                 "\"misc\":[1,2,3],\"stdArray\":[1,2,3]}"};
}


std::pair<std::vector<UserConsolidatedData>, std::string> CreateUserArrayExpectationPair()
{
    auto p = CreateUserConsolidatedExpectationPair();
    std::vector<UserConsolidatedData> v;
    v.push_back(p.first);
    v.push_back(p.first);
    std::ostringstream os;
    os << "[" << p.second << "," << p.second << "]";
    return {v, os.str()};
}

struct A
{
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {}
};

std::pair<A, std::string> CreateEmptyObject()
{
    A a;
    return {a, "{}"};
}

std::pair<std::vector<std::string>, std::string> CreateEmptyArray()
{
    std::vector<std::string> v;
    return {v, "[]"};
}

template<typename U>
void TestSerialization(std::pair<U, std::string>(&f)(void))
{
    std::ostringstream os;
    JsonOutputArchive ar{os};
    auto p = f();
    ar & p.first;
    ASSERT_EQ(p.second, os.str());
}

} /* namespace  */

TEST(JsonSerializationTest, MarshallingEmptyObject)
{
    TestSerialization(CreateEmptyObject);
}

TEST(JsonSerializationTest, MarshallingEmptyArray)
{
    TestSerialization(CreateEmptyArray);
}

TEST(JsonSerializationTest, MarshallingSimbleObjectSuccess)
{
    TestSerialization(CreateUserExpectationPair);
}

TEST(JsonSerializationTest, MarshallingNestedObjectSuccess)
{
    TestSerialization(CreateUserConsolidatedExpectationPair);
}

TEST(JsonSerializationTest, MarshallingArraySuccess)
{
    TestSerialization(CreateUserArrayExpectationPair);
}

