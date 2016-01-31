#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/User.h>

namespace myroomies {
namespace bom {

template<>
void Marshaller<User>::marshallObject(const User& iUser, std::string& oStr)
{
    putValue("id", iUser.id);
    putValue("houseshareId", iUser.houseshareId);
    putValue("firstname", iUser.firstname);
    putValue("lastname", iUser.lastname);
    putValue("dateOfBirth", iUser.dateOfBirth);
    putValue("email", iUser.email);
    marshall(oStr);
}

} /* namespace bom */
} /* namespace myroomies */
