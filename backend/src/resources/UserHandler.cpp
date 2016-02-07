#include <sstream>
#include <vector>

#include <myroomies/bom/Output.h>
#include <myroomies/bom/User.h>
#include <myroomies/bom/UserNew.h>

#include <myroomies/services/UserService.h>

#include <myroomies/resources/UserHandler.h>

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::bom::User;
using myroomies::bom::UserNew;

using myroomies::services::UserService;

namespace myroomies {
namespace resources {

void UserHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    uint32_t houseshareId = getLoggedUser()->houseshareId;
    std::vector<User> users =
        getServiceRegistry()->get<UserService>()->getUsersFromHouseshare(houseshareId);
    std::string response;
    myroomies::bom::MarshallCollection(users, response);
    oResponse.setPayload(response);
}

void UserHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    UserNew newUser;
    newUser.parse(content);
    User createdUser = getServiceRegistry()->get<UserService>()->createUser(getLoggedUser()->id, newUser);
    std::string responsePayload;
    createdUser.marshall(responsePayload);
    oResponse.setPayload(responsePayload);
}

} /* namespace resources */
} /* namespace myroomies */
