#include <string>

#include <libscrypt.h>

#include <myroomies/utils/PasswordHasher.h>

namespace myroomies {
namespace utils {

bool PasswordHasher::hash(const std::string& iPassword, std::string& oMcf)
{
    char buffer[132];
    int rc = libscrypt_hash(buffer ,iPassword.c_str(), SCRYPT_N, SCRYPT_r, SCRYPT_p);
    if (rc > 0)
    {
        oMcf.assign(buffer);
        return true;
    }
    return false;
}

bool PasswordHasher::check(const std::string& iPassword, const std::string& iMcf)
{
    // Do a local copy of the MCF since scrypt modify it on check.
    std::string mcfCopy = iMcf;
    return libscrypt_check(const_cast<char*>(mcfCopy.c_str()), iPassword.c_str()) > 0;
}

} /* namespace utils */
} /* namespace myroomies */
