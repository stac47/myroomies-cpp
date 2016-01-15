#include <string>
#include <functional>

#include <httpserver.hpp>

#include <myroomies/services/LoginService.h>
#include <myroomies/resources/ResourceBase.h>

using std::placeholders::_1;
using std::placeholders::_2;

using httpserver::http_response;
using httpserver::http_response_builder;
using httpserver::http_request;
using httpserver::http::http_utils;

using myroomies::services::LoginService;

namespace {

bool PerformSecurity(const httpserver::http_request& iRequest)
{
    std::string user;
    std::string password;
    iRequest.get_user(user);
    iRequest.get_pass(password);
    if (!user.empty() && !password.empty())
    {
        LoginService service;
        return service.login(user, password);
    }
    return false;
}

typedef std::function<void(const httpserver::http_request& iRequest,
                           httpserver::http_response** oResponse)> MethodCallback;

void RenderCommon(bool iSecured,
                  const httpserver::http_request& iRequest,
                  httpserver::http_response** oResponse,
                  const MethodCallback& f)
{
    if (!iSecured || (iSecured && PerformSecurity(iRequest)))
    {
        f(iRequest, oResponse);
    }
    else
    {
        *oResponse = new http_response(
            http_response_builder("").basic_auth_fail_response()
        );
    }
}

void NotImplementedResponse(httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Not implemented", 500, "text/plain").string_response()
    );
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
    RenderCommon(secured_, iRequest, oResponse, std::bind(&ResourceBase::onGET, this, _1, _2));
}

void ResourceBase::render_POST(const httpserver::http_request& iRequest,
                 httpserver::http_response** oResponse)
{
    RenderCommon(secured_, iRequest, oResponse, std::bind(&ResourceBase::onPOST, this, _1, _2));
}

void ResourceBase::render_PUT(const httpserver::http_request& iRequest,
                httpserver::http_response** oResponse)
{
    RenderCommon(secured_, iRequest, oResponse, std::bind(&ResourceBase::onPUT, this, _1, _2));
}

void ResourceBase::render_DELETE(const httpserver::http_request& iRequest,
                   httpserver::http_response** oResponse)
{
    RenderCommon(secured_, iRequest, oResponse, std::bind(&ResourceBase::onDELETE, this, _1, _2));
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
    NotImplementedResponse(oResponse);
}

void ResourceBase::onPOST(const httpserver::http_request& iRequest,
                          httpserver::http_response** oResponse)
{
    NotImplementedResponse(oResponse);
}

void ResourceBase::onPUT(const httpserver::http_request& iRequest,
                         httpserver::http_response** oResponse)
{
    NotImplementedResponse(oResponse);
}

void ResourceBase::onDELETE(const httpserver::http_request& iRequest,
                            httpserver::http_response** oResponse)
{
    NotImplementedResponse(oResponse);
}

} /* namespace resources */
} /* namespace myroomies */
