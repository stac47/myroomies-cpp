#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace myroomies {
namespace utils {

class HttpUtils final
{
public:
    static const std::string getContentType(const boost::filesystem::path&);
};

} /* namespace utils */
} /* namespace myroomies */
