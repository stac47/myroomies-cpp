#include <string>
#include <functional>

#include <httpserver.hpp>

#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/UserService.h>

#include <myroomies/resources/Resource.h>

using httpserver::http_response;
using httpserver::http_response_builder;
using httpserver::http_request;
using httpserver::http::http_utils;

using myroomies::services::UserService;

namespace myroomies {
namespace resources {

ResourceBase::ResourceBase(
    const std::shared_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry,
    bool iSecured)
  : serviceRegistry_(iServiceRegistry),
    secured_(iSecured)
{
    disallow_all();
    set_allowing(http_utils::http_method_get, true);
    set_allowing(http_utils::http_method_post, true);
    set_allowing(http_utils::http_method_put, true);
    set_allowing(http_utils::http_method_delete, true);
}

ResourceBase::~ResourceBase() {}

bool ResourceBase::performSecurity(const httpserver::http_request& iRequest,
                                   myroomies::bom::User& oLoggedUser)
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
        auto userPtr = getServiceRegistry()->get<UserService>()->login(user, password);
        if (userPtr)
        {
            oLoggedUser = *userPtr;
            return true;
        }
    }
    return false;
}

} /* namespace resources */
} /* namespace myroomies */
