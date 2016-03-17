#include <string>

#include <boost/test/unit_test.hpp>

#include <myroomies/utils/db/SqlTools.h>

using myroomies::utils::db::GenerateInsertTemplate;
using myroomies::utils::db::GenerateSimpleSelectTemplate;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(InsertGeneration)
{
    std::string expected = "INSERT INTO table(c1,c2) VALUES(:c1,:c2)";
    BOOST_CHECK_EQUAL(expected,
                      GenerateInsertTemplate("table", "c1", "c2"));
}

BOOST_AUTO_TEST_CASE(SimpleSelectGeneration)
{
    std::string expected = "SELECT * FROM table WHERE c1=:c1";
    BOOST_CHECK_EQUAL(expected,
                      GenerateSimpleSelectTemplate("table", "c1"));
}

BOOST_AUTO_TEST_SUITE_END()
