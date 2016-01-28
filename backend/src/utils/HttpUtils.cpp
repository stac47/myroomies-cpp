#include <string>

#include <boost/filesystem.hpp>

#include <myroomies/utils/LoggingMacros.h>
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
    MYROOMIES_LOG_WARN("Unknown filename extension: " << extension);
    return "text/plain";
}

} /* namespace utils */
} /* namespace myroomies */
