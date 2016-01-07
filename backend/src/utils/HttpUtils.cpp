#include <string>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include <myroomies/utils/HttpUtils.h>

using boost::filesystem::path;

namespace myroomies {
namespace utils {

const std::string HttpUtils::getContentType(const boost::filesystem::path& iFilename)
{
    // TODO: reimplement this terrible code.
    path extension = iFilename.extension();
    if (extension == ".html")
    {
        return "text/html";
    }
    else if (extension == ".js")
    {
        return "application/javascript";
    }
    else if (extension == ".css")
    {
        return "text/css";
    }
    BOOST_LOG_TRIVIAL(warning) << "Unknown filename extension: " << extension;
    return "text/plain";
}

} // namespace utils
} // namespace myroomies
