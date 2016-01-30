#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/User.h>

namespace myroomies {
namespace bom {

template<>
void Marshaller<User>::marshallObject(const User& iUser, std::string& oStr)
{
    putValue("id", iUser.user.id);
    putValue("houseshareId", iUser.user.houseshareId);
    putValue("firstname", iUser.user.firstname);
    putValue("lastname", iUser.user.lastname);
    putValue("dateOfBirth", iUser.user.dateOfBirth);
    putValue("email", iUser.user.email);
    marshall(oStr);
}

template<>
void Unmarshaller<User>::unmarshall(const std::string& iStr, User& oUser)
{
    parse(iStr);
    extractValue("id", true, oUser.user.id);
    extractValue("login", false, oUser.user.login);
    extractValue("firstname", false, oUser.user.firstname);
    extractValue("lastname", false, oUser.user.lastname);
    extractValue("dateOfBirth", false, oUser.user.dateOfBirth);
    extractValue("email", false, oUser.user.email);
    extractValue("houseshareId", false, oUser.user.houseshareId);
    extractValue("password", true, oUser.password);
}
} /* namespace bom */
} /* namespace myroomies */
