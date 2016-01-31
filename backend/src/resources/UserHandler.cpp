#include <sstream>
#include <vector>

#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/User.h>
#include <myroomies/bom/NewUserRequest.h>


#include <myroomies/services/UserService.h>

#include <myroomies/resources/UserHandler.h>

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::bom::Marshaller;
using myroomies::bom::Unmarshaller;
using myroomies::bom::User;
using myroomies::bom::NewUserRequest;

using myroomies::services::UserService;

namespace myroomies {
namespace resources {

void UserHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string response;
    Marshaller<User> m;
    uint32_t houseshareId = getLoggedUser()->houseshareId;
    m.marshallCollection(
        getServiceRegistry()->get<UserService>()->getUsersFromHouseshare(houseshareId),
        response);
    oResponse.setPayload(response);
}

void UserHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    Unmarshaller<NewUserRequest> unmarshaller;
    NewUserRequest user;
    unmarshaller.unmarshall(content, user);
    User newUser = getServiceRegistry()->get<UserService>()->createUser(getLoggedUser()->id, user);
    std::string responsePayload;
    Marshaller<User> m;
    m.marshallObject(newUser, responsePayload);
    oResponse.setPayload(responsePayload);
}

} /* namespace resources */
} /* namespace myroomies */