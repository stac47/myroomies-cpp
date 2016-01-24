#include <string>
#include <functional>

#include <httpserver.hpp>

#include <myroomies/model/User.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/LoginService.h>

#include <myroomies/resources/Resource.h>

using httpserver::http_response;
using httpserver::http_response_builder;
using httpserver::http_request;
using httpserver::http::http_utils;

using myroomies::services::LoginService;

namespace myroomies {
namespace resources {

ResourceBase::ResourceBase(
    const std::shared_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry,
    const std::string& iUri,
    bool iSecured)
  : serviceRegistry_(iServiceRegistry),
    secured_(iSecured),
    uri_(iUri)
{
    disallow_all();
    set_allowing(http_utils::http_method_get, true);
    set_allowing(http_utils::http_method_post, true);
    set_allowing(http_utils::http_method_put, true);
    set_allowing(http_utils::http_method_delete, true);
}

ResourceBase::~ResourceBase() {}

const std::string& ResourceBase::getUri() const
{
    return uri_;
}

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
        return getServiceRegistry()->get<LoginService>()->login(user, password);
    }
    return false;
}

} /* namespace resources */
} /* namespace myroomies */
