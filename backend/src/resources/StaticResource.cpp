#include <boost/filesystem.hpp>

#include <httpserver.hpp>

#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/HttpUtils.h>

#include <myroomies/resources/StaticResource.h>

using httpserver::http_resource;
using httpserver::http_request;
using httpserver::http_response;
using httpserver::http_response_builder;

using myroomies::utils::HttpUtils;

namespace myroomies {
namespace resources {

StaticResource::StaticResource(const boost::filesystem::path& iBackendPath)
  : staticRootPath_(iBackendPath)
{
    staticRootPath_ /= "../web/src";
}

void StaticResource::render(const httpserver::http_request& iRequest,
                            httpserver::http_response** oResponse)
{
    if (iRequest.get_user().empty())
    {
        *oResponse = new http_response(
            http_response_builder("Authenticate").basic_auth_fail_response()
        );
        return;
    }
    auto requestPath = iRequest.get_path_pieces();
    boost::filesystem::path staticResourcePath = staticRootPath_;
    if (requestPath.size() > 1)
    {
        // Remove the "static" part of the path
        for (unsigned int i = 1; i < requestPath.size(); ++i)
        {
            staticResourcePath /= requestPath[i];
        }
    }
    if (boost::filesystem::exists(staticResourcePath))
    {
        std::string contentType = HttpUtils::getContentType(staticResourcePath);
        MYROOMIES_LOG_INFO("Serving static file: " << staticResourcePath <<
                           " [Content-Type= " << contentType << "]");
        *oResponse = new http_response(
            http_response_builder(staticResourcePath.native(), 200, contentType).file_response()
        );
    }
    else
    {
        MYROOMIES_LOG_ERROR("Static file [" << staticResourcePath << "] " << "does not exists");
        *oResponse = new http_response(
            http_response_builder("Not found", 404, "text/plain").string_response()
        );
    }
}

} /* namespace resources */
} /* namespace myroomies */
