#include <sstream>
#include <vector>

#include <boost/serialization/vector.hpp>

#include <myroomies/utils/json/JsonOutputArchive.h>
#include <myroomies/utils/json/JsonInputArchive.h>

#include <myroomies/bom/User.h>

#include <myroomies/services/UserService.h>

#include <myroomies/resources/UserHandler.h>

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::utils::json::JsonInputArchive;
using myroomies::utils::json::JsonOutputArchive;

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
    std::ostringstream os;
    JsonOutputArchive oa(os);
    oa << users;
    oResponse.setPayload(os.str());
}

void UserHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    JsonInputArchive ia(content);
    UserNew newUser;
    ia >> newUser;
    User createdUser = getServiceRegistry()->get<UserService>()->createUser(getLoggedUser()->id, newUser);
    std::ostringstream os;
    JsonOutputArchive oa(os);
    oa << createdUser;
    oResponse.setPayload(os.str());
}

} /* namespace resources */
} /* namespace myroomies */
