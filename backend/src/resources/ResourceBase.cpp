#include <string>

#include <httpserver.hpp>

#include <myroomies/resources/ResourceBase.h>

using httpserver::http_response;
using httpserver::http_response_builder;
using httpserver::http_request;
using httpserver::http::http_utils;

namespace {

bool performCommonCheck(const httpserver::http_request& iRequest)
{
    std::string user;
    std::string password;
    iRequest.get_user(user);
    iRequest.get_pass(password);
    if (!user.empty() && !password.empty())
    {
        return true;
    }
    return true;
}

} // namespace
namespace myroomies {
namespace resources {

ResourceBase::ResourceBase(bool iSecured)
  : secured_(iSecured)
{
    disallow_all();
    set_allowing(http_utils::http_method_get, true);
    set_allowing(http_utils::http_method_post, true);
    set_allowing(http_utils::http_method_put, true);
    set_allowing(http_utils::http_method_delete, true);
}

void ResourceBase::render_GET(const httpserver::http_request& iRequest,
                httpserver::http_response** oResponse)
{
    if (secured_ && performCommonCheck(iRequest))
    {
        onGET(iRequest, oResponse);
    }
    else
    {
        // TODO return security error response
    }
}

void ResourceBase::render_POST(const httpserver::http_request& iRequest,
                 httpserver::http_response** oResponse)
{
}

void ResourceBase::render_PUT(const httpserver::http_request& iRequest,
                httpserver::http_response** oResponse)
{
}

void ResourceBase::render_DELETE(const httpserver::http_request& iRequest,
                   httpserver::http_response** oResponse)
{
}

void ResourceBase::render_HEAD(const httpserver::http_request& iRequest,
                 httpserver::http_response** oResponse)
{
}

void ResourceBase::render_CONNECT(const httpserver::http_request& iRequest,
                    httpserver::http_response** oResponse)
{
}

void ResourceBase::render_TRACE(const httpserver::http_request& iRequest,
                  httpserver::http_response** oResponse)
{
}

void ResourceBase::render_OPTIONS(const httpserver::http_request& iRequest,
                    httpserver::http_response** oResponse)
{
}

void ResourceBase::render(const httpserver::http_request& iRequest,
            httpserver::http_response** oResponse)
{
}

void ResourceBase::onGET(const httpserver::http_request& iRequest,
                   httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Not found", 404, "text/plain").string_response()
    );
}

void ResourceBase::onPOST(const httpserver::http_request& iRequest,
                    httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Not found", 404, "text/plain").string_response()
    );
}

void ResourceBase::onPUT(const httpserver::http_request& iRequest,
                   httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Not found", 404, "text/plain").string_response()
    );
}

void ResourceBase::onDELETE(const httpserver::http_request& iRequest,
                      httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Not found", 404, "text/plain").string_response()
    );
}

} // namespace resources
} // namespace myroomies
