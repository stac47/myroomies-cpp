#include <sstream>
#include <vector>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <myroomies/bom/User.h>

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
    std::ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << users;
    oResponse.setPayload(os.str());
}

void UserHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    std::istringstream is(content);
    boost::archive::text_iarchive ia(is);
    UserNew newUser;
    ia >> newUser;
    User createdUser = getServiceRegistry()->get<UserService>()->createUser(getLoggedUser()->id, newUser);
    std::ostringstream os;
    boost::archive::text_oarchive oa(os);
    oa << createdUser;
    oResponse.setPayload(os.str());
}

} /* namespace resources */
} /* namespace myroomies */
