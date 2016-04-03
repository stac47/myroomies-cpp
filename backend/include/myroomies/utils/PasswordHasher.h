#pragma once

#include <string>

namespace myroomies {
namespace utils {

class PasswordHasher
{
public:
    bool hash(const std::string& iPassword, std::string& oMcf);
    bool check(const std::string& iPassword, const std::string& iMcf);
};

} /* namespace utils */
} /* namespace myroomies */
