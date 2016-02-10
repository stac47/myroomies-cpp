#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <gtest/gtest.h>

#include <myroomies/utils/UriMatcher.h>

using myroomies::utils::UriMatcher;
using myroomies::utils::UriMatcherException;

TEST(UriMatcherTest, SimpleRegex)
{
    UriMatcher m("^\\S*/(\\d+)$");

    ASSERT_TRUE(m.match("/myroomies/money/14"));
    ASSERT_EQ(14, m.get<unsigned int>(1)) << "Should have returned 14";
    ASSERT_EQ(14, m.get<int>(1));
    ASSERT_EQ(14L, m.get<long>(1));
    ASSERT_EQ("14", m.get<std::string>(1));

    ASSERT_FALSE(m.match("/myroomies/money/wrong"));
    ASSERT_FALSE(m.match("/myroomies/money/14 "));
    ASSERT_FALSE(m.match("14"));

    ASSERT_TRUE(m.match("/myroomies/money/19/18"));
    ASSERT_EQ(18, m.get<unsigned int>(1)) << "Should have returned 18";
}

TEST(UriMatcherTest, ComplexRegex)
{
    UriMatcher m("^\\D*?/money(/since/(\\d{8}))?(/to/(\\d{8}))?/?$");

    ASSERT_TRUE(m.match("/myroomies/money/since/20150619/to/20160131"));
    ASSERT_EQ("20150619", m.get<std::string>(2));
    ASSERT_EQ("20160131", m.get<std::string>(4));

    auto sinceDate = m.get<boost::gregorian::date>(2);
    ASSERT_EQ(2015, sinceDate.year());
    ASSERT_EQ(6, sinceDate.month());
    ASSERT_EQ(19, sinceDate.day());

    ASSERT_TRUE(m.match("/myroomies/money/since/20150619/to/20160131/"));
    ASSERT_EQ("20150619", m.get<std::string>(2));
    ASSERT_EQ("20160131", m.get<std::string>(4));

    // Ignore case
    ASSERT_TRUE(m.match("/MYROOMIES/MONEY/SINCE/20150619/TO/20160131"));
    ASSERT_EQ("20150619", m.get<std::string>(2));
    ASSERT_EQ("20160131", m.get<std::string>(4));

    ASSERT_TRUE(m.match("/myroomies/money/since/20150619"));
    ASSERT_EQ("20150619", m.get<std::string>(2));

    ASSERT_TRUE(m.match("/myroomies/money/since/20150619/"));
    ASSERT_EQ("20150619", m.get<std::string>(2));

    ASSERT_TRUE(m.match("/myroomies/money/"));
    ASSERT_TRUE(m.match("/myroomies/money"));

    ASSERT_FALSE(m.match("/myroomies/money/since/2015/to/20160131"));
    ASSERT_FALSE(m.match("/myroomies/money/since/2015/to/2016"));
    ASSERT_FALSE(m.match("/myroomies/money/since/2015/to/"));
    ASSERT_FALSE(m.match("/myroomies/money/since/2015/"));
    ASSERT_FALSE(m.match("/myroomies/money/since/2015"));
    ASSERT_FALSE(m.match("/myroomies/money/since"));
    ASSERT_FALSE(m.match("/myroomies/money/since/"));
}

TEST(UriMatcherTest, BadRegex)
{
    ASSERT_THROW(UriMatcher m("\\"), UriMatcherException);
    ASSERT_THROW(UriMatcher m("[abc][def"), UriMatcherException);
}

TEST(UriMatcherTest, BadLexicalCast)
{
    UriMatcher m("^\\S*/(\\w+)$");
    ASSERT_TRUE(m.match("/money/expense/12abc"));
    ASSERT_THROW(m.get<int>(1), UriMatcherException);
    ASSERT_THROW(m.get<double>(1), UriMatcherException);
    ASSERT_THROW(m.get<boost::gregorian::date>(1), UriMatcherException);
}

TEST(UriMatcherTest, BadGroupAccess)
{
    UriMatcher m("^\\S*/(\\w+)$");
    ASSERT_TRUE(m.match("/money/expense/12abc"));
    ASSERT_EQ("/money/expense/12abc", m.get<std::string>(0));
    ASSERT_EQ("12abc", m.get<std::string>(1));
    ASSERT_THROW(m.get<std::string>(2), UriMatcherException);
    ASSERT_THROW(m.get<std::string>(-1), UriMatcherException);

}

