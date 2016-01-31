#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/NewUserRequest.h>

namespace myroomies {
namespace bom {

template<>
void Unmarshaller<NewUserRequest>::unmarshall(const std::string& iStr, NewUserRequest& oUser)
{
    parse(iStr);
    extractValue("id", false, oUser.id);
    extractValue("login", true, oUser.login);
    extractValue("firstname", true, oUser.firstname);
    extractValue("lastname", true, oUser.lastname);
    extractValue("dateOfBirth", true, oUser.dateOfBirth);
    extractValue("email", true, oUser.email);
    extractValue("houseshareId", true, oUser.houseshareId);
    extractValue("password", false, oUser.password);
}

} /* namespace bom */
} /* namespace myroomies */
