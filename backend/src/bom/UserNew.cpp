#include <myroomies/bom/Input.h>
#include <myroomies/bom/UserNew.h>

namespace myroomies {
namespace bom {

void UserNew::unmarshall()
{
    extractValue("login", true, login);
    extractValue("firstname", true, firstname);
    extractValue("lastname", true, lastname);
    extractValue("dateOfBirth", true, dateOfBirth);
    extractValue("email", true, email);
    extractValue("houseshareId", true, houseshareId);
    extractValue("password", true, password);
}

void UserNew::validate() const
{
}

} /* namespace bom */
} /* namespace myroomies */
