#include <string>
#include <cstring>

#include <libscrypt.h>

#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/PasswordHasher.h>

namespace {

constexpr std::size_t kMcfSize = 132;

} /* namespace  */

namespace myroomies {
namespace utils {

bool PasswordHasher::hash(const std::string& iPassword, std::string& oMcf)
{
    char buffer[kMcfSize];
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
    // Do a local copy of the MCF since scrypt modifies it on check.
    char buffer[kMcfSize];
    std::memcpy(buffer, iMcf.data(), kMcfSize);
    int rc = libscrypt_check(buffer, iPassword.c_str());
    if (rc < 0)
    {
        MYROOMIES_LOG_INFO("libscrypt raised an error: " << rc);
    }
    return  rc > 0;
}

} /* namespace utils */
} /* namespace myroomies */
