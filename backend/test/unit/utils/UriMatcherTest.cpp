#include <string>

#include <boost/test/unit_test.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/UriMatcher.h>

using myroomies::utils::UriMatcher;
using myroomies::utils::UriMatcherException;

BOOST_AUTO_TEST_SUITE(UriMatcherTest)

BOOST_AUTO_TEST_CASE(SimpleRegex)
{
    UriMatcher m("^\\S*/(\\d+)$");

    BOOST_CHECK(m.match("/myroomies/money/14"));
    BOOST_CHECK_EQUAL(14u, m.get<unsigned int>(1));
    BOOST_CHECK_EQUAL(14, m.get<int>(1));
    BOOST_CHECK_EQUAL(14L, m.get<long>(1));
    BOOST_CHECK_EQUAL("14", m.get<std::string>(1));

    BOOST_CHECK(!m.match("/myroomies/money/wrong"));
    BOOST_CHECK(!m.match("/myroomies/money/14 "));
    BOOST_CHECK(!m.match("14"));

    BOOST_CHECK(m.match("/myroomies/money/19/18"));
    BOOST_CHECK_EQUAL(18u, m.get<unsigned int>(1));
}

BOOST_AUTO_TEST_CASE(ComplexRegex)
{
    UriMatcher m("^\\D*?/money(/since/(\\d{8}))?(/to/(\\d{8}))?/?$");

    BOOST_CHECK(m.match("/myroomies/money/since/20150619/to/20160131"));
    BOOST_CHECK_EQUAL("20150619", m.get<std::string>(2));
    BOOST_CHECK_EQUAL("20160131", m.get<std::string>(4));

    auto sinceDate = m.get<boost::gregorian::date>(2);
    BOOST_CHECK_EQUAL(2015, sinceDate.year());
    BOOST_CHECK_EQUAL(6, sinceDate.month());
    BOOST_CHECK_EQUAL(19, sinceDate.day());

    BOOST_CHECK(m.match("/myroomies/money/since/20150619/to/20160131/"));
    BOOST_CHECK_EQUAL("20150619", m.get<std::string>(2));
    BOOST_CHECK_EQUAL("20160131", m.get<std::string>(4));

    // Ignore case
    BOOST_CHECK(m.match("/MYROOMIES/MONEY/SINCE/20150619/TO/20160131"));
    BOOST_CHECK_EQUAL("20150619", m.get<std::string>(2));
    BOOST_CHECK_EQUAL("20160131", m.get<std::string>(4));

    BOOST_CHECK(m.match("/myroomies/money/since/20150619"));
    BOOST_CHECK_EQUAL("20150619", m.get<std::string>(2));

    BOOST_CHECK(m.match("/myroomies/money/since/20150619/"));
    BOOST_CHECK_EQUAL("20150619", m.get<std::string>(2));

    BOOST_CHECK(m.match("/myroomies/money/"));
    BOOST_CHECK(m.match("/myroomies/money"));

    BOOST_CHECK(!m.match("/myroomies/money/since/2015/to/20160131"));
    BOOST_CHECK(!m.match("/myroomies/money/since/2015/to/2016"));
    BOOST_CHECK(!m.match("/myroomies/money/since/2015/to/"));
    BOOST_CHECK(!m.match("/myroomies/money/since/2015/"));
    BOOST_CHECK(!m.match("/myroomies/money/since/2015"));
    BOOST_CHECK(!m.match("/myroomies/money/since"));
    BOOST_CHECK(!m.match("/myroomies/money/since/"));
}

BOOST_AUTO_TEST_CASE(BadRegex)
{
    BOOST_CHECK_THROW(UriMatcher m("\\"), UriMatcherException);
    BOOST_CHECK_THROW(UriMatcher m("[abc][def"), UriMatcherException);
}

BOOST_AUTO_TEST_CASE(BadLexicalCast)
{
    UriMatcher m("^\\S*/(\\w+)$");
    BOOST_CHECK(m.match("/money/expense/12abc"));
    BOOST_CHECK_THROW(m.get<int>(1), UriMatcherException);
    BOOST_CHECK_THROW(m.get<double>(1), UriMatcherException);
    BOOST_CHECK_THROW(m.get<boost::gregorian::date>(1), UriMatcherException);
}

BOOST_AUTO_TEST_CASE(BadGroupAccess)
{
    UriMatcher m("^\\S*/(\\w+)$");
    BOOST_CHECK(m.match("/money/expense/12abc"));
    BOOST_CHECK_EQUAL("/money/expense/12abc", m.get<std::string>(0));
    BOOST_CHECK_EQUAL("12abc", m.get<std::string>(1));
    BOOST_CHECK_THROW(m.get<std::string>(2), UriMatcherException);
    BOOST_CHECK_THROW(m.get<std::string>(-1), UriMatcherException);
}

BOOST_AUTO_TEST_SUITE_END()
