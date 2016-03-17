#include <string>

#include <boost/test/unit_test.hpp>

#include <myroomies/utils/StringUtils.h>

using myroomies::utils::BuildCompositeStringHelper;

BOOST_AUTO_TEST_SUITE(StringUtilsTest)

BOOST_AUTO_TEST_CASE(GenerateEmptyCompositeString)
{
    BuildCompositeStringHelper h("(", ")", ",");
    BOOST_CHECK_EQUAL("()", h());
}

BOOST_AUTO_TEST_CASE(GenerateOneArgumentString)
{
    {
        BuildCompositeStringHelper h("(", ")", ",");
        BOOST_CHECK_EQUAL("(A)", h('A'));
    }
    {
        BuildCompositeStringHelper h("(", ")", ",");
        BOOST_CHECK_EQUAL("(A)", h("A"));
    }
    {
        BuildCompositeStringHelper h("(", ")", ",");
        BOOST_CHECK_EQUAL("(1)", h(1));
    }
}

BOOST_AUTO_TEST_CASE(GenerateSeveralArgumentString)
{
    {
        BuildCompositeStringHelper h("(", ")", ",");
        BOOST_CHECK_EQUAL("(A,B)", h("A", "B"));
    }
    {
        BuildCompositeStringHelper h("(", ")", ",");
        BOOST_CHECK_EQUAL("(A,1,3.14,true)", h("A", 1, 3.14, true));
    }
    {
        BuildCompositeStringHelper h;
        BOOST_CHECK_EQUAL("A13.14true", h("A", 1, 3.14, true));
    }
}

BOOST_AUTO_TEST_SUITE_END()
