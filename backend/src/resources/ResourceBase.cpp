#include <string>
#include <functional>

#include <httpserver.hpp>

#include <myroomies/model/User.h>
#include <myroomies/services/LoginService.h>
#include <myroomies/resources/ResourceBase.h>

using httpserver::http_response;
using httpserver::http_response_builder;
using httpserver::http_request;
using httpserver::http::http_utils;

using myroomies::services::LoginService;

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

ResourceBase::~ResourceBase() {}

bool ResourceBase::performSecurity(const httpserver::http_request& iRequest,
                                   myroomies::model::User& oLoggedUser)
{
    if (!secured_)
    {
        return true;
    }
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

} /* namespace resources */
} /* namespace myroomies */
