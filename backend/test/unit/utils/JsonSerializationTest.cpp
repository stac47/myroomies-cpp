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
#include <boost/test/unit_test.hpp>

#include <myroomies/bom/User.h>
#include <myroomies/utils/json/JsonOutputArchive.h>
#include <myroomies/utils/json/JsonInputArchive.h>

using myroomies::bom::User;
using myroomies::utils::json::JsonOutputArchive;
using myroomies::utils::json::JsonInputArchive;

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
    BOOST_CHECK_EQUAL(p.second, os.str());
}

} /* namespace  */

BOOST_AUTO_TEST_SUITE(JsonSerializationTest)

BOOST_AUTO_TEST_CASE(MarshallingEmptyObject)
{
    TestSerialization(CreateEmptyObject);
}

BOOST_AUTO_TEST_CASE(MarshallingEmptyArray)
{
    TestSerialization(CreateEmptyArray);
}

BOOST_AUTO_TEST_CASE(MarshallingSimbleObjectSuccess)
{
    TestSerialization(CreateUserExpectationPair);
}

BOOST_AUTO_TEST_CASE(MarshallingNestedObjectSuccess)
{
    TestSerialization(CreateUserConsolidatedExpectationPair);
}

BOOST_AUTO_TEST_CASE(MarshallingArraySuccess)
{
    TestSerialization(CreateUserArrayExpectationPair);
}

BOOST_AUTO_TEST_CASE(UnmarshallingSimpleObjectSuccess)
{
    auto p = CreateUserExpectationPair();
    JsonInputArchive ia{p.second};
    User u;
    ia >> u;
    BOOST_CHECK_EQUAL(p.first.id, u.id);
    BOOST_CHECK_EQUAL(p.first.login, u.login);
    BOOST_CHECK_EQUAL(p.first.firstname, u.firstname);
    BOOST_CHECK_EQUAL(p.first.lastname, u.lastname);
    BOOST_CHECK_EQUAL(p.first.dateOfBirth, u.dateOfBirth);
    BOOST_CHECK_EQUAL(p.first.email, u.email);
    BOOST_CHECK_EQUAL(p.first.houseshareId, u.houseshareId);
}

BOOST_AUTO_TEST_CASE(UnmarshallingComplexObjectSuccess)
{
    auto p = CreateUserConsolidatedExpectationPair();
    JsonInputArchive ia{p.second};
    UserConsolidatedData ucd;
    ia >> ucd;
    BOOST_CHECK_EQUAL(p.first.user.id, ucd.user.id);
    BOOST_CHECK_EQUAL(p.first.user.login, ucd.user.login);
    BOOST_CHECK_EQUAL(p.first.user.firstname, ucd.user.firstname);
    BOOST_CHECK_EQUAL(p.first.user.lastname, ucd.user.lastname);
    BOOST_CHECK_EQUAL(p.first.user.dateOfBirth, ucd.user.dateOfBirth);
    BOOST_CHECK_EQUAL(p.first.user.email, ucd.user.email);
    BOOST_CHECK_EQUAL(p.first.user.houseshareId, ucd.user.houseshareId);
    BOOST_CHECK_EQUAL(p.first.age, ucd.age);
    BOOST_CHECK_EQUAL_COLLECTIONS(p.first.hobbies.begin(),
                                  p.first.hobbies.end(),
                                  ucd.hobbies.begin(),
                                  ucd.hobbies.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(p.first.preferedNumbers.begin(),
                                  p.first.preferedNumbers.end(),
                                  ucd.preferedNumbers.begin(),
                                  ucd.preferedNumbers.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(p.first.misc,
                                  p.first.misc + 3,
                                  ucd.misc,
                                  ucd.misc + 3);
    BOOST_CHECK_EQUAL_COLLECTIONS(p.first.stdArray.begin(),
                                  p.first.stdArray.end(),
                                  ucd.stdArray.begin(),
                                  ucd.stdArray.end());
}

BOOST_AUTO_TEST_CASE(UnmarshallingEmptyVectorSuccess)
{
    std::string jsonStr = "[]";
    JsonInputArchive ia{jsonStr};
    std::vector<int> v;
    ia >> v;
    BOOST_CHECK_EQUAL(0, v.size());
}

BOOST_AUTO_TEST_CASE(UnmarshallingSimpleVectorSuccess)
{
    std::string jsonStr = "[1, 2, 3]";
    JsonInputArchive ia{jsonStr};
    std::vector<int> v;
    ia >> v;
    BOOST_CHECK_EQUAL(3, v.size());
    BOOST_CHECK_EQUAL(1, v[0]);
    BOOST_CHECK_EQUAL(2, v[1]);
    BOOST_CHECK_EQUAL(3, v[2]);
}

BOOST_AUTO_TEST_CASE(UnmarshallingSimpleStdArraySuccess)
{
    std::string jsonStr = "[1, 2, 3]";
    JsonInputArchive ia{jsonStr};
    std::array<int, 3> a;
    ia >> a;
    BOOST_CHECK_EQUAL(3, a.size());
    BOOST_CHECK_EQUAL(1, a[0]);
    BOOST_CHECK_EQUAL(2, a[1]);
    BOOST_CHECK_EQUAL(3, a[2]);
}

BOOST_AUTO_TEST_CASE(UnmarshallingSimpleArraySuccess)
{
    std::string jsonStr = "[1, 2, 3]";
    JsonInputArchive ia{jsonStr};
    int a[3];
    ia >> a;
    BOOST_CHECK_EQUAL(1, a[0]);
    BOOST_CHECK_EQUAL(2, a[1]);
    BOOST_CHECK_EQUAL(3, a[2]);
}

BOOST_AUTO_TEST_SUITE_END()
