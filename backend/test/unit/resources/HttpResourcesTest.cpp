#include <string>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <myroomies/utils/HttpUtils.h>

BOOST_AUTO_TEST_SUITE(HttpResourcesTest)

BOOST_AUTO_TEST_CASE(ContentType)
{
    boost::filesystem::path aFile = "index.html";
    std::string contentType = myroomies::utils::HttpUtils::getContentType(aFile);
    BOOST_CHECK_EQUAL(contentType, "text/html");
}

BOOST_AUTO_TEST_SUITE_END()
