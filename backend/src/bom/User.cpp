#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/User.h>

using rapidjson::Document;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

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

template<>
void Unmarshaller<User>::unmarshall(const std::string& iStr, User& oUser)
{
    parse(iStr);
    extractValue("id", true, oUser.id);
    extractValue("login", false, oUser.login);
    extractValue("firstname", false, oUser.firstname);
    extractValue("lastname", false, oUser.lastname);
    extractValue("dateOfBirth", false, oUser.dateOfBirth);
    extractValue("email", false, oUser.email);
    extractValue("houseshareId", false, oUser.houseshareId);
}
} /* namespace bom */
} /* namespace myroomies */
