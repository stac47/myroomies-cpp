#include <string>
#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include <myroomies/utils/HttpUtils.h>

TEST(HttpUtilsTest, ContentType)
{
    boost::filesystem::path aFile = "index.html";
    std::string contentType = myroomies::utils::HttpUtils::getContentType(aFile);
    ASSERT_EQ(contentType, "text/html");
}
