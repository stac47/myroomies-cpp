#include <string>

#include <myroomies/bom/Output.h>
#include <myroomies/bom/User.h>

namespace myroomies {
namespace bom {

void User::marshall(std::string& oOutputStr)
{
    putValue("id", id);
    putValue("login", login);
    putValue("houseshareId", houseshareId);
    putValue("firstname", firstname);
    putValue("lastname", lastname);
    putValue("dateOfBirth", dateOfBirth);
    putValue("email", email);
    marshallObject(oOutputStr);
}

} /* namespace bom */
} /* namespace myroomies */
